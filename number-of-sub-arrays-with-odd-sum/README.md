# Number of Sub-arrays With Odd Sum
> LeetCode · Medium · [problem](https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/)

## 📝 Problem

> Given an array of integers arr, return the number of subarrays with an odd sum.
>
> Since the answer can be very large, return it modulo 109 + 7.
>
>
> Example 1:
>
> Input: arr = [1,3,5]
> Output: 4
> Explanation: All subarrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
> All sub-arrays sum are [1,4,9,3,8,5].
> Odd sums are [1,9,3,5] so the answer is 4.
>
> Example 2:
>
> Input: arr = [2,4,6]
> Output: 0
> Explanation: All subarrays are [[2],[2,4],[2,4,6],[4],[4,6],[6]]
> All sub-arrays sum are [2,6,12,4,10,6].
> All sub-arrays have even sum and the answer is 0.
>
> Example 3:
>
> Input: arr = [1,2,3,4,5,6,7]
> Output: 16
>
>
> Constraints:
>
> 1 <= arr.length <= 105
> 1 <= arr[i] <= 100

AnyPush tracked this solution across **4 steps**.

## Journey
1. **Step 1 · first solve** _(2026-11-15)_ — `v1.c`  
   This solution efficiently counts subarrays with odd sums in a single pass using prefix sum parities.
2. **Step 2 · improved** _(2026-11-15)_ — `v2.c`  
   This solution efficiently counts subarrays with odd sums in a single pass using prefix sum parities. The core idea is that a subarray `arr[i...j]` has an odd su
3. **Step 3 · improved** _(2026-11-15)_ — `v3.c`  
   This solution efficiently counts subarrays with odd sums in a single pass using prefix sum parities. The core idea is that a subarray `arr[i...j]` has an odd su
4. **Step 4 · improved** _(2026-11-15)_ — `v4.c`  
   This solution efficiently counts subarrays with odd sums in a single pass by leveraging prefix sum parities. The core idea is that a subarray `arr[i...j]` has a

## Current solution
See [`solution.c`](./solution.c).
