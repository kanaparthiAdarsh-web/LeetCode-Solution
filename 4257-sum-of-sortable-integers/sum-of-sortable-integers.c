bool check(int* nums, int n, int k) {
    int chunks = n / k;
    int* min_vals = (int*)malloc(chunks * sizeof(int));
    int* max_vals = (int*)malloc(chunks * sizeof(int));
    
    for (int i = 0; i < chunks; i++) {
        int start = i * k;
        int min_v = nums[start], max_v = nums[start];
        bool is_sorted = true;
        int rot_idx = -1;
        int rot_count = 0;
        
        for (int j = 1; j < k; j++)
            if (nums[start + j] < nums[start + j - 1])
                rot_count++,rot_idx = start + j;
        
        if (rot_count > 1) {
            free(min_vals);
            free(max_vals);
            return false;
        }
        
        if (rot_count == 1) {
            if (nums[start + k - 1] > nums[start]) {
                free(min_vals);
                free(max_vals);
                return false;
            }
            min_vals[i] = nums[rot_idx];
            max_vals[i] = nums[rot_idx - 1];
        } else
            min_vals[i] = nums[start],max_vals[i] = nums[start + k - 1];
    }
    
    for (int i = 0; i < chunks - 1; i++) {
        if (max_vals[i] > min_vals[i + 1]) {
            free(min_vals);
            free(max_vals);
            return false;
        }
    }
    
    free(min_vals);
    free(max_vals);
    return true;
}

int sortableIntegers(int* nums, int numsSize) {
    int total_sum = 0;
    for (int k = 1; k <= numsSize; k++)
        if (numsSize % k == 0)
            if (check(nums, numsSize, k))
                total_sum += k;
    return total_sum;
}