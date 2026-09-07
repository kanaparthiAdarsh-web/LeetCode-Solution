int distinctSubseqII(char* s) {
    long long MOD = 1000000007;
    long long endWith[26] = {0};
    
    for (int i = 0; s[i] != '\0'; i++) {
        int idx = s[i] - 'a';
        
        long long total = 0;
        for (int j = 0; j < 26; total = (total + endWith[j]) % MOD, j++);
        
        endWith[idx] = (total + 1) % MOD;
    }
    
    long long ans = 0;
    for (int j = 0; j < 26; ans = (ans + endWith[j]) % MOD, j++);
    
    return (int)ans;
}