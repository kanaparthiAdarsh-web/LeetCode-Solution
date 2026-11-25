# Maximum Subarray With Equal Products
> LeetCode · Easy · [problem](https://leetcode.com/problems/maximum-subarray-with-equal-products/)

## 📝 Problem

> You are given an array of positive integers nums.
>
> An array arr is called product equivalent if prod(arr) == lcm(arr) * gcd(arr), where:
>
> prod(arr) is the product of all elements of arr.
> gcd(arr) is the GCD of all elements of arr.
> lcm(arr) is the LCM of all elements of arr.
>
> Return the length of the longest product equivalent subarray of nums.
>
>
> Example 1:
>
> Input: nums = [1,2,1,2,1,1,1]
>
> Output: 5
>
> Explanation:
>
> The longest product equivalent subarray is [1, 2, 1, 1, 1], where prod([1, 2, 1, 1, 1]) = 2, gcd([1, 2, 1, 1, 1]) = 1, and lcm([1, 2, 1, 1, 1]) = 2.
>
> Example 2:
>
> Input: nums = [2,3,4,5,6]
>
> Output: 3
>
> Explanation:
>
> The longest product equivalent subarray is [3, 4, 5].
>
> Example 3:
>
> Input: nums = [1,2,3,1,4,5,1]
>
> Output: 5
>
>
> Constraints:
>
> 2 <= nums.length <= 100
> 1 <= nums[i] <= 10

AnyPush tracked this solution across **1 step**.

## Journey
1. **Step 1 · first solve** _(2026-11-24)_  
   This solution employs a brute-force approach, iterating through all possible subarrays using nested loops (O(N^2)). For each subarray, we incrementally calculat

> ✅ **Merged** — the per-step files were collapsed into `solution.c`. The journey above is the kept record.

## Current solution
See [`solution.c`](./solution.c).
