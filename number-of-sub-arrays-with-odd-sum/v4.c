/*
 * AnyPush — AI explanation
 * This solution efficiently counts subarrays with odd sums in a single pass by leveraging prefix sum parities. The core idea is that a subarray `arr[i...j]` has an odd sum if and only if its cumulative sum up to `j` (`prefixSum[j]`) and its cumulative sum up to `i-1` (`prefixSum[i-1]`) have different parities. We iterate through the array, maintaining `oddCount` and `evenCount` of prefix sums encountered so far. At each step, we determine the current prefix sum's parity and add the count of previously seen prefix sums with the *opposite* parity to our `totalOdds`.
 *
 * This specific version is a continuous refinement of previous attempts (v1, v2, v3). While earlier versions placed the update logic directly within the loop body, this iteration further optimizes for conciseness by moving the entire parity check and counter updates into the `for` loop's increment section. This makes the loop body exceptionally clean, containing only the `currentSum` update.
 *
 * Time complexity is O(N) as we process each element exactly once. Space complexity is O(1) since we only use a fixed number of variables. This approach is highly efficient, avoiding the O(N^2) or O(N^3) time complexity of naive solutions that would easily TLE.
 *
 * While extremely concise, placing complex logic in the `for` loop's increment section, as done here, can reduce immediate readability for those unfamiliar with such competitive programming idioms. For general software engineering, a more explicit update within the loop body (like v1 or v2) might be preferred for clarity.
 */

#include <stdio.h>

int numOfSubarrays(int* arr, int arrSize) {
    long long oddCount = 0, evenCount = 1;
    long long currentSum = 0,totalOdds = 0,mod = 1000000007;

    for (int i = 0; i < arrSize; (currentSum % 2 != 0)? (totalOdds = (totalOdds + evenCount) % mod,oddCount++):(totalOdds = (totalOdds + oddCount) % mod,evenCount++),i++) {
        currentSum += arr[i];   
    }

    return (int)totalOdds;
}
