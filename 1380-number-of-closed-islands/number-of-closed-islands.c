bool dfs(int** grid, int r, int c, int rows, int cols) {
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        return false;
    
    if (grid[r][c] == 1)
        return true;
        
    grid[r][c] = 1;
    
    bool left = dfs(grid, r, c - 1, rows, cols);
    bool right = dfs(grid, r, c + 1, rows, cols);
    bool up = dfs(grid, r - 1, c, rows, cols);
    bool down = dfs(grid, r + 1, c, rows, cols);
    
    return left && right && up && down;
}

int closedIsland(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];
    int count = 0;
    
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (grid[i][j] == 0)
                if (dfs(grid, i, j, rows, cols))
                    count++;
    return count;
}