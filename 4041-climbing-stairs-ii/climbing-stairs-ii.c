long long climbStairs(int n, int* costs, int costsSize) {
    long long* dp = (long long*)malloc((n + 1) * sizeof(long long));
    for (int i = 0; i <= n; dp[i] = LLONG_MAX,i++);
    
    dp[0] = 0;
    
    for (int i = 0; i < n; i++) {
        if (dp[i] == LLONG_MAX) continue;
        
        for (int j = 1; j <= 3; j++) {
            int next_step = i + j;
            if (next_step <= n) {
                long long cost = dp[i] + costs[next_step - 1] + (long long)(next_step - i) * (next_step - i);
                if (cost < dp[next_step])
                    dp[next_step] = cost;
            }
        }
    }
    
    long long ans = dp[n];
    free(dp);
    return ans;
}