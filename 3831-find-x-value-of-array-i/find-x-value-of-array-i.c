long long* resultArray(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = k;
    long long* ans = (long long*)calloc(k, sizeof(long long));
    long long* dp = (long long*)calloc(k, sizeof(long long));
    
    for (int idx = 0; idx < numsSize; idx++) {
        int num = nums[idx];
        long long* newDp = (long long*)calloc(k, sizeof(long long));
        int numMod = num % k;
        newDp[numMod] = 1;
        
        for (int i = 0; i < k; i++) {
            int newMod = (i * numMod) % k;
            newDp[newMod] += dp[i];
        }
        
        for (int i = 0; i < k; i++)
            ans[i] += newDp[i];
        
        free(dp);
        dp = newDp;
    }
    
    free(dp);
    return ans;
}