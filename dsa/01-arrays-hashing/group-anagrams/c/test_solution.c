#include "solution.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static int checks = 0;

/* An independent definition of the answer, used to check the partition.
 * Deliberately not the solution's method: it counts, the test sorts nothing. */
static int is_anagram(const char *a, const char *b) {
    int ca[26] = {0}, cb[26] = {0};
    for (; *a; a++) if (*a >= 'a' && *a <= 'z') ca[*a - 'a']++;
    for (; *b; b++) if (*b >= 'a' && *b <= 'z') cb[*b - 'a']++;
    return memcmp(ca, cb, sizeof ca) == 0;
}

/* Invariant 2, both directions: same group if and only if anagrams. */
static void check_partition(const char *name, const char **strs, size_t n, size_t want_groups) {
    size_t group_of[64];
    size_t groups = group_anagrams(strs, n, group_of);
    if (groups != want_groups) {
        printf("  FAIL %-26s got %zu groups, want %zu\n", name, groups, want_groups);
        assert(0);
    }
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            int same = group_of[i] == group_of[j];
            int anag = is_anagram(strs[i], strs[j]);
            if (same != anag) {
                printf("  FAIL %-26s \"%s\" and \"%s\": same=%d anagram=%d\n",
                       name, strs[i], strs[j], same, anag);
                assert(0);
            }
        }
    }
    printf("  PASS %-26s %zu strings, %zu groups\n", name, n, groups);
    checks++;
}

int main(void) {
    const char *single[]   = {"a"};
    const char *empty[]    = {""};
    const char *allempty[] = {"", ""};
    const char *none[]     = {"abc", "def"};
    const char *classic[]  = {"eat", "tea", "tan", "ate", "nat", "bat"};
    const char *counts[]   = {"aab", "abb"};
    const char *dupes[]    = {"ab", "ab"};
    const char *mixed[]    = {"eat", "tea", "tan", "ate", "nat", "bat", "", "aab"};

    check_partition("single string", single, 1, 1);
    check_partition("empty string", empty, 1, 1);
    check_partition("all empty", allempty, 2, 1);
    check_partition("no anagrams", none, 2, 2);
    check_partition("classic", classic, 6, 3);
    check_partition("same letters diff counts", counts, 2, 2);
    check_partition("repeated string", dupes, 2, 1);
    check_partition("empty mixed in", mixed, 8, 5);

    /* Invariant 1: every index gets a group below the group count. */
    size_t group_of[8];
    size_t groups = group_anagrams(mixed, 8, group_of);
    for (size_t i = 0; i < 8; i++) assert(group_of[i] < groups);
    printf("  PASS %-26s every index assigned\n", "no string dropped");
    checks++;

    printf("\n  %d checks passed\n", checks);
    return 0;
}
