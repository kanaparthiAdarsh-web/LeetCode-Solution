int sortPermutation(int* nums, int numsSize) {
    int ans = -1;
    for (int i = 0; i < numsSize; i++)
        if (nums[i] != i) 
            ans &= nums[i];
    
    return ans == -1 ? 0 : ans;
}