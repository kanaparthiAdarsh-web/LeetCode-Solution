int minMoves(int* nums, int numsSize) {
    int minVal = nums[0];
    long long sum = 0;
    
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < minVal)
            minVal = nums[i];
        
        sum += nums[i];
    }
    
    return (int)(sum - (long long)minVal * numsSize);
}