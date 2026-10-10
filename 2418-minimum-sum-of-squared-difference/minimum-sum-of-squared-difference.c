long long minSumSquareDiff(int* nums1, int nums1Size, int* nums2, int nums2Size, int k1, int k2) {
    long long totalK = (long long)k1 + k2;
    int max_diff = 0;
    
    for (int i = 0; i < nums1Size; i++) {
        int diff = abs(nums1[i] - nums2[i]);
        if (diff > max_diff)
            max_diff = diff;
    }
    
    long long* count = (long long*)calloc(max_diff + 2, sizeof(long long));
    for (int i = 0; i < nums1Size; i++) {
        int diff = abs(nums1[i] - nums2[i]);
        count[diff]++;
    }
    
    for (int d = max_diff; d > 0 && totalK > 0; d--) {
        if (count[d] == 0) 
            continue;
        
        long long take = (totalK < count[d]) ? totalK : count[d];
        count[d] -= take;
        count[d - 1] += take;
        totalK -= take;
    }
    
    long long ans = 0;
    for (int d = 1; d <= max_diff; d++) {
        if (count[d] > 0)
            ans += count[d] * (long long)d * d;
    }
    
    free(count);
    return ans;
}