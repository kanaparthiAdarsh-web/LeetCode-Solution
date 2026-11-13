/*
 * AnyPush — AI explanation
 * This solution employs a two-pointer sliding window approach, with the right endpoint `r` iterating backwards from `n-1`. For each `r`, the left endpoint `l` is expanded leftwards as much as possible while keeping the subarray `nums[r...l]`'s transformation cost within `k`. The optimal cost to make a subarray `nums[r...l]` non-decreasing is `sum(max(nums[r], ..., nums[i]) - nums[i])` over `i` from `r` to `l`. A monotonic deque efficiently maintains the `sum(max(nums[r], ..., nums[i]))` term, allowing amortized O(1) updates as the window slides.
 *
 * Time Complexity: O(N), Space Complexity: O(N). Both pointers traverse the array once, and each element enters/leaves the deque at most once.
 * This approach is essential for `N=10^5` as a naive `O(N^2)` solution (checking all subarrays) would time out. The monotonic deque specifically optimizes calculating the sum of transformed elements within the sliding window to `O(1)` amortized time per window adjustment.
 * A naive `O(N^2)` or `O(N^3)` approach without the deque would repeatedly calculate prefix maximums or sums, which is prohibitively slow.
 */

long long countNonDecreasingSubarrays(int* nums, int numsSize, int k) {
    int n = numsSize;
    long long* pre = (long long*)malloc(sizeof(long long) * (n + 1));
    pre[0] = 0;
    for (int i = 0; i < n; i++) 
        pre[i + 1] = pre[i] + nums[i];

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
            if (dq[hi - 1] == l) hi--;
            l--;
        }

        ans += l - r + 1;
    }

    free(pre);
    free(dq);
    return ans;
}
