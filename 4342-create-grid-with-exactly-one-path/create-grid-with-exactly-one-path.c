char** createGrid(int m, int n, int* returnSize) {
    char** res = (char**)malloc(sizeof(char*) * m);
    for (int i = 0; i < m; i++) {
        res[i] = (char*)malloc(n + 1);
        for (int j = 0; j < n; j++) {
            res[i][j] = (i == 0 || j == n - 1) ? '.' : '#';
        }
        res[i][n] = '\0';
    }
    *returnSize = m;
    return res;
}