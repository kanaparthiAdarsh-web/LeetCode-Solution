void backtrack(int open, int close, int n, char* current, int index, char** res, int* returnSize) {
    if (index == 2 * n) {
        current[index] = '\0';
        res[*returnSize] = malloc((2 * n + 1) * sizeof(char));
        strcpy(res[*returnSize], current);
        (*returnSize)++;
        return;
    }
    
    if (open < n) {
        current[index] = '(';
        backtrack(open + 1, close, n, current, index + 1, res, returnSize);
    }
    if (close < open) {
        current[index] = ')';
        backtrack(open, close + 1, n, current, index + 1, res, returnSize);
    }
}

char** generateParenthesis(int n, int* returnSize) {
    int maxCapacity = 1430;
    char** res = malloc(maxCapacity * sizeof(char*));
    char* current = malloc((2 * n + 1) * sizeof(char));
    *returnSize = 0;
    
    backtrack(0, 0, n, current, 0, res, returnSize);
    
    free(current);
    return res;
}