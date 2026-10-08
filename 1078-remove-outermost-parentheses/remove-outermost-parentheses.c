char* removeOuterParentheses(char* s) {
    int n = strlen(s);
    char* res = (char*)malloc(n + 1);
    int depth = 0, j = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            if (depth > 0) 
                res[j++] = '(';
            depth++;
        } else {
            depth--;
            if (depth > 0) 
                res[j++] = ')';
        }
    }
    res[j] = '\0';
    return res;
}