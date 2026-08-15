int longestSubsequence(int* nums, int numsSize) {
    int total_xor = 0;
    int has_non_zero = 0;
    for (int i = 0; i < numsSize; i++) {
        total_xor ^= nums[i];
        if (nums[i] != 0) {
            has_non_zero = 1;
        }
    }
    if (!has_non_zero) {
        return 0;
    }
    if (total_xor != 0) {
        return numsSize;
    }
    return numsSize - 1;
}