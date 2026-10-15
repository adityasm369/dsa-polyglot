import unittest
from solution import group_anagrams, group_anagrams_sorted


def normal(groups):
    """Order-independent form: a sorted list of sorted groups."""
    return sorted(sorted(g) for g in groups)


CASES = [
    (["a"], [["a"]]),
    ([""], [[""]]),
    (["", ""], [["", ""]]),
    (["abc", "def"], [["abc"], ["def"]]),
    (["eat", "tea", "tan", "ate", "nat", "bat"],
     [["eat", "tea", "ate"], ["tan", "nat"], ["bat"]]),
    (["aab", "abb"], [["aab"], ["abb"]]),
    (["ab", "ab"], [["ab", "ab"]]),
]


class GroupAnagrams(unittest.TestCase):
    def test_spec_cases(self):
        for strs, want in CASES:
            with self.subTest(strs=strs):
                self.assertEqual(normal(group_anagrams(list(strs))), normal(want))

    def test_every_string_in_exactly_one_group(self):
        # Invariant 1.
        strs = ["eat", "tea", "tan", "ate", "nat", "bat", "", "aab"]
        out = group_anagrams(list(strs))
        self.assertEqual(sorted(s for g in out for s in g), sorted(strs))

    def test_sorted_and_count_keys_agree(self):
        strs = ["listen", "silent", "enlist", "google", "gogole", "cat", "act"]
        self.assertEqual(normal(group_anagrams(list(strs))),
                         normal(group_anagrams_sorted(list(strs))))

    def test_input_not_modified(self):
        strs = ["eat", "tea"]
        group_anagrams(strs)
        self.assertEqual(strs, ["eat", "tea"])


if __name__ == "__main__":
    unittest.main(verbosity=2)
