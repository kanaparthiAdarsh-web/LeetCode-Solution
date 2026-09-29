bool hasValidPath(char** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(' || (m + n) % 2 == 0)
        return false;
    
    
    int max_open = (m + n) / 2;
    bool*** dp = malloc(m * sizeof(bool**));
    for (int i = 0; i < m; i++) {
        dp[i] = malloc(n * sizeof(bool*));
        for (int j = 0; j < n; dp[i][j] = calloc(max_open + 1, sizeof(bool)),j++);
    }
    
    dp[0][0][1] = true;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) 
                continue;
            int add = (grid[i][j] == '(') ? 1 : -1;
            
            for (int k = 0; k <= max_open; k++) {
                int prev = k - add;
                if (prev >= 0 && prev <= max_open) {
                    bool from_top = (i > 0 && dp[i - 1][j][prev]);
                    bool from_left = (j > 0 && dp[i][j - 1][prev]);
                    if (from_top || from_left)
                        dp[i][j][k] = true;
                }
            }
        }
    }
    
    bool ans = dp[m - 1][n - 1][0];
    
    for (int i = 0; i < m; free(dp[i]),i++)
        for (int j = 0; j < n; free(dp[i][j]),j++);
        
    free(dp);
    
    return ans;
}