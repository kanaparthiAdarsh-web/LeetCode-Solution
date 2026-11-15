/*
 * AnyPush — AI explanation
 * This solution efficiently counts subarrays with odd sums in a single pass using prefix sum parities.
 * It dynamically tracks how many previous prefix sums have been odd or even.
 * For each new element, if the current prefix sum is odd, it forms an odd-sum subarray with every previously encountered even prefix sum. If the current prefix sum is even, it pairs with previously encountered odd prefix sums.
 * Time Complexity: O(N) due to one iteration.
 * Space Complexity: O(1) as only a few counter variables are used.
 * This approach is highly efficient, directly calculating counts in linear time, avoiding the O(N^2) Time Limit Exceeded (TLE) from a naive brute-force method.
 * A more naive solution would check all O(N^2) subarrays, which is too slow for typical constraints.
 * Minor optimization: bitwise AND (& 1) could replace modulo (%) for parity checks, though compilers often optimize this.
 */

#include <stdio.h>

int numOfSubarrays(int* arr, int arrSize) {
    long long oddCount = 0, evenCount = 1;
    long long currentSum = 0;
    long long totalOdds = 0;
    long long mod = 1000000007;

    for (int i = 0; i < arrSize; i++) {
        currentSum += arr[i];
        if (currentSum % 2 != 0) {
            totalOdds = (totalOdds + evenCount) % mod;
            oddCount++;
        } else {
            totalOdds = (totalOdds + oddCount) % mod;
            evenCount++;
        }
    }

    return (int)totalOdds;
}
