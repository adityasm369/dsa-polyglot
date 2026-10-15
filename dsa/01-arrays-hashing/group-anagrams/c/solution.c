/* group-anagrams. Time O(n*k), Space O(n).
 *
 * C has no hash map, so this file is the one in this folder that shows what the
 * other six standard libraries are doing for you: an open-addressing table with
 * linear probing, keyed on the 26 letter counts.
 *
 * Sizing the table at 2n keeps the load factor at or below 0.5, which is what
 * keeps linear probing's clusters short. There is no resize because the final
 * size is known before the first insert -- a luxury this problem happens to
 * give us.
 */
#include "solution.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    int counts[26];
    size_t group;
    int used;      /* see the comment in group_anagrams: this flag is load-bearing */
} Slot;

static size_t hash_counts(const int *counts) {
    /* FNV-1a over the raw bytes of the count vector. */
    const unsigned char *p = (const unsigned char *)counts;
    size_t h = 1469598103934665603ULL;
    for (size_t i = 0; i < 26 * sizeof(int); i++) {
        h ^= p[i];
        h *= 1099511628211ULL;
    }
    return h;
}

size_t group_anagrams(const char **strs, size_t n, size_t *group_of) {
    if (!strs || !group_of) return (size_t)-1;
    if (n == 0) return 0;

    size_t cap = 1;
    while (cap < n * 2) cap <<= 1;          /* power of two, so & (cap-1) masks */
    Slot *table = calloc(cap, sizeof(Slot));
    if (!table) return (size_t)-1;

    size_t groups = 0;
    for (size_t i = 0; i < n; i++) {
        int counts[26] = {0};
        for (const char *p = strs[i]; *p; p++) {
            if (*p >= 'a' && *p <= 'z') counts[*p - 'a']++;
        }

        /* The empty string's key is 26 zeros -- which is also what calloc left
         * in every unused slot. Without the `used` flag, "" would collide with
         * the whole empty table and every string would land in group 0. */
        size_t h = hash_counts(counts) & (cap - 1);
        while (table[h].used && memcmp(table[h].counts, counts, sizeof counts) != 0) {
            h = (h + 1) & (cap - 1);        /* linear probing */
        }
        if (!table[h].used) {
            table[h].used = 1;
            memcpy(table[h].counts, counts, sizeof counts);
            table[h].group = groups++;
        }
        group_of[i] = table[h].group;
    }

    free(table);
    return groups;
}
