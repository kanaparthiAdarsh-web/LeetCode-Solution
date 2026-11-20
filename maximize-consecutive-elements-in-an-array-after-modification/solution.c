/*
 * AnyPush — AI explanation
 * This solution uses dynamic programming after sorting the input array. `dp[k]` stores the maximum length of a consecutive sequence that can be formed ending with the value `k`.
 *
 * When iterating through each number `x` in the sorted array, we consider two ways to utilize it: either using `x` as its original value (extending a sequence ending at `x-1`), or modifying `x` to `x+1` (extending a sequence ending at `x`). The updates `dp[x+1] = dp[x] + 1;` and `dp[x] = dp[x-1] + 1;` (in this order) correctly reflect these choices. The `dp[x+1]` value leverages the sequence length for `x` established by previous elements, while `dp[x]` is then updated for the current `x`.
 *
 * Time complexity: O(N log N + MaxNum). Sorting takes O(N log N), and the DP loop is O(N) with O(1) array access for values up to `MaxNum`.
 * Space complexity: O(MaxNum) for the `dp` array.
 *
 * This DP strategy is efficient for its domain, correctly capturing the element modification and extension logic. Sorting allows for sequential processing, and the DP approach avoids redundant computations compared to exponential brute-force methods.
 *
 * Honest note: This solution uses a direct array for DP, making its space and time dependent on `MaxNum` (the maximum value in `nums`). For problem constraints where `nums[i]` can be as large as `10^9`, this approach would lead to Memory Limit Exceeded. A more robust solution for such constraints would use a hash map to store `dp` states, reducing space complexity to O(N) while maintaining O(N log N) time complexity.
 */

int cmp(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

int maxSelectedElements(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), cmp);
    
    int maxVal = nums[numsSize - 1];
    int* dp = (int*)calloc(maxVal + 2, sizeof(int));
    int ans = 0;
    
    for (int i = 0; i < numsSize; i++) {
        int x = nums[i];
        dp[x + 1] = dp[x] + 1;
        dp[x] = dp[x - 1] + 1;
        
        if (dp[x + 1] > ans) 
            ans = dp[x + 1];
        if (dp[x] > ans) 
            ans = dp[x];
    }
    
    free(dp);
    return ans;
}
