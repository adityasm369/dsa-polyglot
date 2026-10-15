#ifndef GROUP_ANAGRAMS_H
#define GROUP_ANAGRAMS_H
#include <stddef.h>
/* Partitions strs into anagram groups.
 *
 * Writes group_of[i] = the group index of strs[i], and returns the number of
 * groups. Group indices are assigned in order of first appearance. Returns
 * (size_t)-1 if the internal table cannot be allocated. */
size_t group_anagrams(const char **strs, size_t n, size_t *group_of);
#endif
