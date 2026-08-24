
int stoneGameVIII(int* stones, int stonesSize) {
    int* prefix = (int*)malloc(sizeof(int) * stonesSize);
    prefix[0] = stones[0];
    for (int i = 1; i < stonesSize;prefix[i] = prefix[i - 1] + stones[i],i++);
    int dp = prefix[stonesSize - 1];

    for (int i = stonesSize - 2,take_current=prefix[i]-dp; i >= 1;take_current=prefix[i]-dp, i--)
        if (take_current > dp)
            dp = take_current;

    free(prefix);
    return dp;
}