int compare(const void* a, const void* b) {
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    if (x < y) 
        return -1;
    if (x > y) 
        return 1;
    return 0;
}

long long maxAlternatingSum(int* nums, int numsSize) {
    long long* arr = (long long*)malloc(numsSize * sizeof(long long));
    for (int i = 0; i < numsSize; i++)
        arr[i] = labs(nums[i]);
    
    qsort(arr, numsSize, sizeof(long long), compare);
    
    long long ans = 0;
    int left = 0, right = numsSize - 1;
    int turn = 0;
    
    while (left <= right) {
        if (turn % 2 == 0) {
            ans += arr[right] * arr[right];
            right--;
        } else {
            ans -= arr[left] * arr[left];
            left++;
        }
        turn++;
    }
    
    free(arr);
    return ans;
}