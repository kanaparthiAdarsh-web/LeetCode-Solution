/*
 * AnyPush — AI explanation
 * This solution employs a two-pointer sliding window with 'r' moving backwards from n-1. For each 'r', 'l' expands leftwards to find the largest valid window satisfying the cost constraint 'k'. The transformation cost for nums[r...l] is sum(max(nums[r...i])) - sum(nums[r...l]) over i in [r, l].
 *
 * Earlier ideas might have led to O(N^2) by recomputing range maximums, or O(N log N) with data structures like segment trees. This version significantly improves by leveraging a monotonic deque to compute the sum of max(nums[r...i]) terms in amortized O(1) time. Prefix sums handle the sum(nums[r...l]) component.
 *
 * Time Complexity: O(N) because each pointer ('r', 'l') and deque operation processes elements at most a constant number of times.
 * Space Complexity: O(N) for the prefix sums and the deque.
 *
 * This O(N) approach is optimal and clean, using the deque to efficiently manage maximums within the window. While the deque's logic can be intricate, its amortized constant-time updates are indispensable for achieving this performance.
 */

long long countNonDecreasingSubarrays(int* nums, int numsSize, int k) {
    int n = numsSize;
    long long* pre = (long long*)malloc(sizeof(long long) * (n + 1));
    pre[0] = 0;
    for (int i = 0; i < n; pre[i + 1] = pre[i] + nums[i],i++);

    int* dq = (int*)malloc(sizeof(int) * (n + 1));
    int lo = n, hi = n;
    long long total = 0;
    long long ans = 0;
    int l = n - 1;

    for (int r = n - 1; r >= 0; r--) {
        while (lo < hi && nums[dq[lo]] <= nums[r]) {
            int p = dq[lo];
            int nxt = (lo + 1 < hi) ? dq[lo + 1] : l + 1;
            total -= (long long)nums[p] * (nxt - p);
            lo++;
        }
        int nxt = (lo < hi) ? dq[lo] : l + 1;
        total += (long long)nums[r] * (nxt - r);
        dq[--lo] = r;

        while (total - (pre[l + 1] - pre[r]) > k) {
            total -= nums[dq[hi - 1]];
            if (dq[hi - 1] == l) 
                hi--;
            l--;
        }
        ans += l - r + 1;
    }

    free(pre);
    free(dq);
    return ans;
}
