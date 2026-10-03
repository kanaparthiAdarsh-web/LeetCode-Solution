int longestValidParentheses(char* s) {
    int len = strlen(s);
    if (len == 0) 
        return 0;
    
    int* dp = calloc(len, sizeof(int));
    int maxLen = 0;
    
    for (int i = 1; i < len; i++) {
        if (s[i] == ')') {
            if (s[i - 1] == '(')
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
             else {
                int prev = i - 1 - dp[i - 1];
                if (prev >= 0 && s[prev] == '(')
                    dp[i] = dp[i - 1] + 2 + (prev >= 1 ? dp[prev - 1] : 0);
            }
            if (dp[i] > maxLen)
                maxLen = dp[i];
        }
    }
    
    free(dp);
    return maxLen;
}