/* two-sum -- and, because this is C, the hash map itself.
 *
 * Time  O(n) average      Space O(n)
 *
 * Every other language in this folder gets the next 60 lines from its standard
 * library. Writing them once is the point of doing this problem in C.
 *
 * Open addressing with linear probing. Chosen over separate chaining because
 * it needs no per-node malloc: one array, cache friendly, and nothing to free
 * but the table.
 */
#include "solution.h"
#include <stdlib.h>
#include <string.h>

/* Load factor is kept under 0.5. Linear probing degrades sharply past that --
 * clusters merge and a lookup walks a long run -- so the table is sized to at
 * least 2n and rounded up to a power of two, which turns the modulo into a
 * mask. */
static size_t table_size_for(size_t n) {
    size_t cap = 16;
    while (cap < n * 2) cap <<= 1;
    return cap;
}

/* Knuth's multiplicative hash. The input keys here are adversarially ordinary
 * -- 0, 1, 2, 3 -- and taking those modulo a power of two would put every key
 * in a different bucket but leave the high bits unused; multiplying first
 * spreads them. */
static size_t hash_key(long long key, size_t cap) {
    unsigned long long k = (unsigned long long)key;
    k *= 11400714819323198485ULL;        /* 2^64 / phi */
    return (size_t)(k >> 32) & (cap - 1);
}

typedef struct { long long key; int idx; int used; } slot;

/* Returns the slot for `key`: either the one holding it, or the first free one
 * on its probe sequence. Never fails, because the caller guarantees the table
 * is under half full. */
static slot *probe(slot *t, size_t cap, long long key) {
    size_t i = hash_key(key, cap);
    while (t[i].used && t[i].key != key)
        i = (i + 1) & (cap - 1);
    return &t[i];
}

int two_sum(const int *nums, size_t n, long long target, int *out_i, int *out_j) {
    if (!nums || n < 2 || !out_i || !out_j) return 0;

    size_t cap = table_size_for(n);
    slot *t = calloc(cap, sizeof *t);     /* calloc: `used` must start zeroed */
    if (!t) return 0;                     /* out of memory is not "no answer" */

    int found = 0;
    for (size_t j = 0; j < n && !found; j++) {
        /* 64-bit, deliberately. nums[i] reaches 1e9, so the sum reaches 2e9
         * and `target - nums[j]` reaches -2e9 -- both outside int32. SPEC.md
         * calls this out as the line that differs across the seven languages. */
        long long want = target - (long long)nums[j];

        slot *s = probe(t, cap, want);
        if (s->used) {                    /* seen the partner already */
            *out_i = s->idx;              /* its index is < j, so i < j holds */
            *out_j = (int)j;
            found = 1;
            break;
        }
        /* Insert nums[j] only if absent, so the FIRST index wins on duplicates
         * and [3,3] gives (0,1). Inserting after the lookup is what stops an
         * element pairing with itself. */
        slot *self = probe(t, cap, (long long)nums[j]);
        if (!self->used) {
            self->key = (long long)nums[j];
            self->idx = (int)j;
            self->used = 1;
        }
    }
    free(t);
    return found;
}
