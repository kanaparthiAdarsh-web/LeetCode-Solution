static int isPalindrome(const char* s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right])
            return 0;
        left++;
        right--;
    }
    return 1;
}

int maxPalindromes(char* s, int k) {
    int n = strlen(s);
    if (k > n)
        return 0;

    int* dp = (int*)calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];

        if (i >= k && isPalindrome(s, i - k, i - 1))
            if (dp[i - k] + 1 > dp[i]) 
                dp[i] = dp[i - k] + 1;

        if (i >= k + 1 && isPalindrome(s, i - (k + 1), i - 1))
            if (dp[i - (k + 1)] + 1 > dp[i])
                dp[i] = dp[i - (k + 1)] + 1;
    }

    int palindrome = dp[n];
    free(dp);
    return palindrome;
}