/*
 * AnyPush — AI explanation
 * This solution finds the length of the smallest unique subarray by leveraging suffix arrays and Longest Common Prefix (LCP) array construction. We build a suffix array to sort all suffixes, then compute LCPs to quantify commonality between adjacent suffixes. The shortest unique subarray is identified by finding a suffix whose longest common prefix with both its neighbors is `m`, meaning a substring of length `m+1` from that suffix is guaranteed to be unique within the entire input.
 *
 * Time Complexity: O(N log N) due to suffix array construction using the doubling algorithm and counting sort.
 * Space Complexity: O(N) for storing the suffix array, rank array, LCP array, and temporary auxiliary arrays.
 *
 * This approach is chosen for its efficiency, providing a robust, near-linear time solution that avoids the prohibitively high O(N^3) or O(N^2 * L) costs of naive substring enumeration and hashing that would fail on larger inputs.
 *
 * Our initial `v1` represented a strong step towards this by laying the foundation for suffix array construction. This version builds directly upon that, adding the complete LCP array computation and the critical final step of traversing LCP values to extract the minimum unique subarray length. This demonstrates a natural progression in algorithm refinement. Further optimization could explore O(N) suffix array construction algorithms like SA-IS, though O(N log N) is typically sufficient.
 */

int smallestUniqueSubarray(int* nums, int numsSize) {
    int n = numsSize;
    if (n <= 1) 
        return n;

    int maxVal = 0;
    for (int i = 0; i < n; i++)
        if (nums[i] > maxVal) 
            maxVal = nums[i];
    

    int cntSize = (n > maxVal ? n : maxVal) + 2;
    int* sa = (int*)malloc(n * sizeof(int));
    int* rk = (int*)malloc(n * sizeof(int));
    int* tmp = (int*)malloc(n * sizeof(int));
    int* cnt = (int*)calloc(cntSize, sizeof(int));
    int* lcp = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; cnt[nums[i]]++,i++);
    for (int i = 1; i <= maxVal; cnt[i] += cnt[i - 1],i++);
    for (int i = n - 1; i >= 0; sa[--cnt[nums[i]]] = i,i--);

    rk[sa[0]] = 1;
    int p = 1;
    for (int i = 1; i < n; i++) {
        if (nums[sa[i]] != nums[sa[i - 1]]) 
            p++;
        rk[sa[i]] = p;
    }

    for (int k = 1; k < n && p < n; k <<= 1) {
        int idx = 0;
        for (int i = n - k; i < n; tmp[idx++] = i,i++);
        for (int i = 0; i < n; i++) {
            if (sa[i] >= k) 
                tmp[idx++] = sa[i] - k;
        }

        memset(cnt, 0, (p + 1) * sizeof(int));
        for (int i = 0; i < n; cnt[rk[tmp[i]]]++,i++);
        for (int i = 1; i <= p; cnt[i] += cnt[i - 1],i++);
        for (int i = n - 1; i >= 0; sa[--cnt[rk[tmp[i]]]] = tmp[i],i--);

        tmp[sa[0]] = 1;
        int newP = 1;
        for (int i = 1; i < n; i++) {
            int a = sa[i], b = sa[i - 1];
            int ra2 = (a + k < n) ? rk[a + k] : 0;
            int rb2 = (b + k < n) ? rk[b + k] : 0;
            if (rk[a] != rk[b] || ra2 != rb2) 
                newP++;
            tmp[a] = newP;
        }

        int* swap = rk;
        rk = tmp;
        tmp = swap;
        p = newP;
    }

    int h = 0;
    for (int i = 0; i < n; i++) {
        int r = rk[i] - 1;
        if (r == n - 1) {
            lcp[r] = 0;
            h = 0;
            continue;
        }
        int j = sa[r + 1];
        while (i + h < n && j + h < n && nums[i + h] == nums[j + h]) {
            h++;
        }
        lcp[r] = h;
        if (h > 0) h--;
    }

    int ans = n;
    for (int r = 0; r < n; r++) {
        int left = (r > 0) ? lcp[r - 1] : 0;
        int right = (r < n - 1) ? lcp[r] : 0;
        int m = left > right ? left : right;
        if (sa[r] + m < n && m + 1 < ans) {
            ans = m + 1;
        }
    }

    free(sa);
    free(rk);
    free(tmp);
    free(cnt);
    free(lcp);

    return ans;
}
