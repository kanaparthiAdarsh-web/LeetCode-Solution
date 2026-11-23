# Check if All A's Appears Before All B's
> LeetCode · Easy · [problem](https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/)

## 📝 Problem

> Given a string s consisting of only the characters 'a' and 'b', return true if every 'a' appears before every 'b' in the string. Otherwise, return false.
>
>
> Example 1:
>
> Input: s = "aaabbb"
> Output: true
> Explanation:
> The 'a's are at indices 0, 1, and 2, while the 'b's are at indices 3, 4, and 5.
> Hence, every 'a' appears before every 'b' and we return true.
>
> Example 2:
>
> Input: s = "abab"
> Output: false
> Explanation:
> There is an 'a' at index 2 and a 'b' at index 1.
> Hence, not every 'a' appears before every 'b' and we return false.
>
> Example 3:
>
> Input: s = "bbb"
> Output: true
> Explanation:
> There are no 'a's, hence, every 'a' appears before every 'b' and we return true.
>
>
> Constraints:
>
> 1 <= s.length <= 100
> s[i] is either 'a' or 'b'.

AnyPush tracked this solution across **1 step**.

## Journey
1. **Step 1 · first solve** _(2026-11-22)_  
   This solution iterates through the string in a single pass, tracking whether a 'b' has been encountered yet. It uses a `seenB` flag; once set to true, any subse

> ✅ **Merged** — the per-step files were collapsed into `solution.c`. The journey above is the kept record.

## Current solution
See [`solution.c`](./solution.c).
