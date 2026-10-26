int countIslands(int** grid, int gridSize, int* gridColSize, int k) {
    int m = gridSize;
    int n = gridColSize[0];
    int* stack = (int*)malloc(sizeof(int) * m * n);
    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};
    int count = 0;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (grid[i][j] <= 0) 
                continue;

            long long sum = 0;
            int top = 0;
            stack[top++] = i * n + j;
            sum += grid[i][j];
            grid[i][j] = 0;

            while (top > 0) {
                int cur = stack[--top];
                int r = cur / n;
                int c = cur % n;
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] > 0) {
                        sum += grid[nr][nc];
                        grid[nr][nc] = 0;
                        stack[top++] = nr * n + nc;
                    }
                }
            }

            if (sum % k == 0) 
                count++;
        }

    free(stack);
    return count;
}