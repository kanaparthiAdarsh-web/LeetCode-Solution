int minOperations(int* nums, int numsSize, int x) {
    int totalSum = 0;
    for (int i = 0; i < numsSize; i++)
        totalSum += nums[i];
    int target = totalSum - x;
    if (target < 0) return -1;
    if (target == 0) return numsSize;

    int currentSum = 0;
    int maxLen = -1;
    int left = 0;

    for (int right = 0; right < numsSize; right++) {
        currentSum += nums[right];
        while (currentSum > target && left <= right) {
            currentSum -= nums[left];
            left++;
        }
        if (currentSum == target)
            if (right - left + 1 > maxLen)
                maxLen = right - left + 1;
    }

    return maxLen == -1 ? -1 : numsSize - maxLen;
}