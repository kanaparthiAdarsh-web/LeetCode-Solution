int longestMonotonicSubarray(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    
    int maxLen = 1;
    int incLen = 1;
    int decLen = 1;
    
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > nums[i - 1]) {
            incLen++;
            decLen = 1;
        } else if (nums[i] < nums[i - 1]) {
            decLen++;
            incLen = 1;
        } else {
            incLen = 1;
            decLen = 1;
        }
        
        if (incLen > maxLen) maxLen = incLen;
        if (decLen > maxLen) maxLen = decLen;
    }
    
    return maxLen;
}