int stoneGameVIII(int* stones, int stonesSize) {
    for (int i = 1; i < stonesSize;stones[i] += stones[i - 1],i++);
    int dp = stones[stonesSize - 1];
    for (int i = stonesSize - 2,diff=stones[i]-dp; i >= 1;diff=stones[i]-dp, i--)
        if (diff > dp)
            dp = diff;
    return dp;
}