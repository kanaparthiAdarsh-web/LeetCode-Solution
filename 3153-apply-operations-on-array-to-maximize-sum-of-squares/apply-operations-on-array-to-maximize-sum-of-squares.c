int maxSum(int* nums, int numsSize, int k) {
    const long long MOD = 1000000007LL;
    int cnt[31] = {0};
    for (int i = 0; i < numsSize; i++)
        for (int b = 0; b < 31; ((nums[i] >> b) & 1) ? cnt[b]++:0, b++);

    long long ans = 0,x=0;
    for (int i = 0; i < k;  ans = (ans + (x % MOD) * (x % MOD)) % MOD,x=0,i++)
        for (int b = 0; b < 31; (cnt[b] > 0)? (x |= (1LL << b),cnt[b]--):0,b++);
        
    return (int)ans;
}