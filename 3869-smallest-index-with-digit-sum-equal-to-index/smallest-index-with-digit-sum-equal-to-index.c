int smallestIndex(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        int temp = nums[i];
        int sum = 0;
        while (temp > 0) {
            sum += temp % 10;
            temp /= 10;
        }
        if (nums[i] == 0)
            sum = 0;
        
        if (sum == i)
            return i;
        
    }
    return -1;
}