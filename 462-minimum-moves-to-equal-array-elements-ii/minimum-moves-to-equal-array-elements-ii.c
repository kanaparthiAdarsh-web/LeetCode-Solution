int cmp(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

int minMoves2(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), cmp);
    
    int i = 0, j = numsSize - 1;
    int moves = 0;
    
    while (i < j)
        moves += nums[j] - nums[i],i++,j--;
    
    return moves;
}