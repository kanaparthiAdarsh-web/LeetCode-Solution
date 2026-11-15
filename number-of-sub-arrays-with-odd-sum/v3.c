/*
 * AnyPush — AI explanation
 * This solution efficiently counts subarrays with odd sums in a single pass using prefix sum parities. The core idea is that a subarray `arr[i...j]` has an odd sum if `prefixSum[j]` and `prefixSum[i-1]` have different parities. We track counts of odd and even prefix sums encountered, updating our total based on current prefix sum parity and previous counts.
 *
 * This approach yields O(N) time by a single array scan and O(1) space complexity by using only a few variables. It vastly outperforms a naive O(N^2) brute-force, which would check every subarray explicitly. Our journey started with v1, establishing the core logic with standard `if/else`. v2 condensed this to single-line `if/else`. This current version further refines the assignment logic using a ternary operator, showcasing compact C while retaining readability for experienced eyes.
 */

#include <stdio.h>

int numOfSubarrays(int* arr, int arrSize) {
    long long oddCount = 0, evenCount = 1;
    long long currentSum = 0,totalOdds = 0,mod = 1000000007;

    for (int i = 0; i < arrSize; i++) {
        currentSum += arr[i];
        (currentSum % 2 != 0)? (totalOdds = (totalOdds + evenCount) % mod,oddCount++):(totalOdds = (totalOdds + oddCount) % mod,evenCount++);
    }

    return (int)totalOdds;
}
