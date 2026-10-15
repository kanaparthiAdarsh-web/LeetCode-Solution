int sumCounts(int* nums, int numsSize) {
    int totalSum = 0;
    
    for (int i = 0; i < numsSize; i++) {
        int freq[101] = {0};
        int distinctCount = 0;
        
        for (int j = i; j < numsSize; j++) {
            if (freq[nums[j]] == 0)
                distinctCount++;
            freq[nums[j]]++;
            totalSum += distinctCount * distinctCount;
        }
    }
    
    return totalSum;
}