
typedef struct {
    int val;
    int idx;
} Pair;

int cmpPair(const void* a, const void* b) {
    return ((Pair*)a)->val - ((Pair*)b)->val;
}

int cmpInt(const void* a, const void* b) {
    return (*(int*)a) - (*(int*)b);
}

int* lexicographicallySmallestArray(int* nums, int numsSize, int limit, int* returnSize) {
    Pair* pairs = (Pair*)malloc(sizeof(Pair) * numsSize);
    for (int i = 0; i < numsSize; i++) {
        pairs[i].val = nums[i];
        pairs[i].idx = i;
    }

    qsort(pairs, numsSize, sizeof(Pair), cmpPair);

    int* result = (int*)malloc(sizeof(int) * numsSize);
    int* groupIndices = (int*)malloc(sizeof(int) * numsSize);

    int left = 0;
    while (left < numsSize) {
        int right = left;
        while (right + 1 < numsSize && pairs[right + 1].val - pairs[right].val <= limit)
            right++;

        int groupSize = right - left + 1;
        for (int i = 0; i < groupSize; i++)
            groupIndices[i] = pairs[left + i].idx;

        qsort(groupIndices, groupSize, sizeof(int), cmpInt);

        for (int i = 0; i < groupSize; i++)
            result[groupIndices[i]] = pairs[left + i].val;

        left = right + 1;
    }

    free(pairs);
    free(groupIndices);

    *returnSize = numsSize;
    return result;
}