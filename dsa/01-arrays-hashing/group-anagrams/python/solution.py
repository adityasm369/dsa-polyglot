"""group-anagrams. Time O(n * k), Space O(n * k), where k is the longest string.

The key is a tuple of 26 letter counts. Tuples hash by value, so two anagrams
produce equal keys and land in the same bucket.
"""
from collections import defaultdict
from typing import List


def group_anagrams(strs: List[str]) -> List[List[str]]:
    groups = defaultdict(list)
    for s in strs:
        counts = [0] * 26
        for ch in s:
            counts[ord(ch) - ord("a")] += 1
        groups[tuple(counts)].append(s)
    return list(groups.values())


def group_anagrams_sorted(strs: List[str]) -> List[List[str]]:
    """The sorted-string key. Correct, and O(k log k) per string. Kept for the
    comparison in the spec's complexity table."""
    groups = defaultdict(list)
    for s in strs:
        groups["".join(sorted(s))].append(s)
    return list(groups.values())
