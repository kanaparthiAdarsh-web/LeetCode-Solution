int largestInteger(int* nums, int numsSize, int k) {
    int sub_count[55];
    memset(sub_count, 0, sizeof(sub_count));
    
    for (int i = 0,seen[55]; i <= numsSize - k;memset(seen, 0, sizeof(seen)),i++)
        for (int j = i; j < i + k;j++) 
            if (!seen[nums[j]]) {
                seen[nums[j]] = 1;
                sub_count[nums[j]]++;
            }
    int ans = -1;
    for (int v = 0; v <= 50; v++)
        if (sub_count[v] == 1)
            if (v > ans)
                ans = v;
    
    return ans;
}