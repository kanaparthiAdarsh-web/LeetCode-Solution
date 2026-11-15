/*
 * AnyPush — AI explanation
 * This solution efficiently counts subarrays with odd sums in a single pass using prefix sum parities. The core idea is that a subarray `arr[i...j]` has an odd sum if and only if `prefixSum[j]` and `prefixSum[i-1]` have different parities. We track counts of odd and even prefix sums encountered so far, incrementing `totalOdds` based on these counts at each step.
 *
 * Time: O(N) - A single pass through the array.
 * Space: O(1) - Only a few constant variables are maintained.
 *
 * This approach vastly improves upon earlier, less efficient ideas like an O(N^2) brute-force, which would check every possible subarray sum. That brute-force would be too slow for typical constraints (e.g., N=10^5). By leveraging parity properties, we achieve optimal time complexity, making the solution practical. One minor note could be slightly more compact ternary logic for updating `totalOdds` and `oddCount`/`evenCount`, but the current if/else maintains excellent readability.
 */

#include <stdio.h>

int numOfSubarrays(int* arr, int arrSize) {
    long long oddCount = 0, evenCount = 1;
    long long currentSum = 0;
    long long totalOdds = 0;
    long long mod = 1000000007;

    for (int i = 0; i < arrSize; i++) {
        currentSum += arr[i];
        if (currentSum % 2 != 0)
            totalOdds = (totalOdds + evenCount) % mod,oddCount++;
        else
            totalOdds = (totalOdds + oddCount) % mod,evenCount++;
    }

    return (int)totalOdds;
}
