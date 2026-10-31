int uniquePaths(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    const int MOD = 1000000007;
    
    int right[505];
    int down[505];
    memset(right, 0, sizeof(int) * (n + 1));
    memset(down, 0, sizeof(int) * (n + 1));
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                right[0] = 1;
                down[0] = 1;
                continue;
            }
            
            int from_left = (j > 0) ? right[j - 1] : 0;
            int from_up = down[j];
            
            if (grid[i][j] == 0) {
                int ways = (from_left + from_up) % MOD;
                right[j] = ways;
                down[j] = ways;
            } else {
                right[j] = from_up;
                down[j] = from_left;
            }
        }
    }
    
    return right[n - 1];
}