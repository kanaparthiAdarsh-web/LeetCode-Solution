int minimumDeletions(int* nums, int numsSize) {
    if (numsSize <= 2)
        return numsSize;

    int minIdx = 0;
    int maxIdx = 0;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < nums[minIdx])
            minIdx = i;
        if (nums[i] > nums[maxIdx])
            maxIdx = i;
    }

    int left = minIdx < maxIdx ? minIdx : maxIdx;
    int right = minIdx > maxIdx ? minIdx : maxIdx;
   
    int minMoves = right + 1;
    if ((numsSize - left) < minMoves)
        minMoves = (numsSize - left);
    if (((left+1) + (numsSize-right)) < minMoves)
        minMoves = (left+1) + (numsSize - right);

    return minMoves;
}