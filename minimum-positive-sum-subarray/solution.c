/*
 * AnyPush — AI explanation
 * This solution systematically iterates through all possible subarray lengths from `l` to `r`. For each length, it employs a sliding window technique to efficiently compute the sum of every subarray of that specific length, continuously tracking the minimum positive sum encountered.
 *
 * Time Complexity: O(N^2) where N is `numsSize`. The outer loop considers up to N lengths, and the inner sliding window pass takes O(N) time.
 * Space Complexity: O(1). Only a constant number of auxiliary variables are used.
 *
 * This approach is efficient for its purpose, avoiding a brute-force O(N^3) solution (which would re-sum each subarray from scratch) by leveraging the sliding window optimization. It's a robust and generally accepted complexity for problems with N up to a few thousand.
 *
 * While adequate, a more optimized approach for extremely large N or specific sum distributions might utilize prefix sums with a data structure like a segment tree or monotonic queue, but that would add significant complexity for this problem's constraints.
 */

int minimumSumSubarray(int* nums, int numsSize, int l, int r) {
    int min_sum = -1;
    
    for (int len = l; len <= r; len++) {
        if (len > numsSize) 
            break;
        
        long long current_sum = 0;
        for (int i = 0; i < len; i++) {
            current_sum += nums[i];
        }
        
        if (current_sum > 0) {
            if (min_sum == -1 || current_sum < min_sum) {
                min_sum = current_sum;
            }
        }
        
        for (int i = len; i < numsSize; i++) {
            current_sum += nums[i] - nums[i - len];
            if (current_sum > 0) {
                if (min_sum == -1 || current_sum < min_sum) {
                    min_sum = current_sum;
                }
            }
        }
    }
    
    return min_sum;
}
