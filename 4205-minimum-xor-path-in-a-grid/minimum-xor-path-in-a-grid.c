static unsigned char cur[1000][1024];
static unsigned char nxt[1000][1024];

int minCost(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];

    memset(cur, 0, sizeof(cur));
    cur[0][grid[0][0]] = 1;
    for (int j = 1; j < n; j++) {
        int v = grid[0][j];
        for (int x = 0; x < 1024; x++)
            if (cur[j - 1][x]) 
                cur[j][x ^ v] = 1;
    }

    for (int i = 1; i < m; i++) {
        memset(nxt, 0, sizeof(nxt));
        for (int j = 0; j < n; j++) {
            int v = grid[i][j];
            for (int x = 0; x < 1024; x++) {
                int ok = cur[j][x];
                if (j > 0 && nxt[j - 1][x]) 
                    ok = 1;
                if (ok) 
                    nxt[j][x ^ v] = 1;
            }
        }
        memcpy(cur, nxt, sizeof(cur));
    }

    for (int x = 0; x < 1024; x++)
        if (cur[n - 1][x]) 
            return x;
    return -1;
}