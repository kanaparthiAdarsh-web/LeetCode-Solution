/*
 * AnyPush — AI explanation
 * This solution determines the minimum length L such that all substrings of length L in the input array are unique (i.e., appear exactly once).
 * It constructs a Suffix Array (SA) using the doubling algorithm and its corresponding Longest Common Prefix (LCP) array using Kasai's algorithm.
 * The core idea leverages the property that this minimum unique length L is `max(LCP) + 1`. The LCP array efficiently reveals the longest common prefixes between sorted suffixes, which is key to identifying repeated substrings.
 *
 * Time complexity: O(N log N) due to SA construction (doubling with counting sort).
 * Space complexity: O(N) for storing SA, LCP, ranks, and temporary arrays.
 *
 * This approach is highly efficient for string-related problems involving substring comparisons, offering a near-linear solution where a naive O(N^3) hash-set based approach would be prohibitively slow for larger inputs.
 * A simpler but much slower alternative would involve iterating through all possible substring lengths and checking for uniqueness using a hash map, leading to an O(N^3) worst-case time complexity.
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

    for (int i = 0; i < n; i++) 
        cnt[nums[i]]++;
    for (int i = 1; i <= maxVal; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) sa[--cnt[nums[i]]] = i;

    rk[sa[0]] = 1;
    int p = 1;
    for (int i = 1; i < n; i++) {
        if (nums[sa[i]] != nums[sa[i - 1]]) p++;
        rk[sa[i]] = p;
    }

    for (int k = 1; k < n && p < n; k <<= 1) {
        int idx = 0;
        for (int i = n - k; i < n; i++) tmp[idx++] = i;
        for (int i = 0; i < n; i++) {
            if (sa[i] >= k) tmp[idx++] = sa[i] - k;
        }

        memset(cnt, 0, (p + 1) * sizeof(int));
        for (int i = 0; i < n; i++) cnt[rk[tmp[i]]]++;
        for (int i = 1; i <= p; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--cnt[rk[tmp[i]]]] = tmp[i];

        tmp[sa[0]] = 1;
        int newP = 1;
        for (int i = 1; i < n; i++) {
            int a = sa[i], b = sa[i - 1];
            int ra2 = (a + k < n) ? rk[a + k] : 0;
            int rb2 = (b + k < n) ? rk[b + k] : 0;
            if (rk[a] != rk[b] || ra2 != rb2) newP++;
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
