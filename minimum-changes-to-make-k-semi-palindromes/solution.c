/*
 * AnyPush — AI explanation
 * (AnyPush: AI explanation unavailable — Gemini error 503: {
 *   "error": {
 *     "code": 503,
 *     "message": "This model is currently experiencing high demand. Spikes in demand are usually temporary. Please try again later.",
 *     "status": "UNAVAILABLE"
 *   }
 * }
 * )
 */

int minimumChanges(char* s, int k) {
    int n = strlen(s);
    int cost[205][205];
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int len = j - i + 1;
            int min_c = 100000;
            
            for (int d = 1; d < len; d++) {
                if (len % d == 0) {
                    int c = 0;
                    for (int rem = 0; rem < d; rem++) {
                        int l = i + rem;
                        int r = j - (d - 1 - rem);
                        while (l < r) {
                            if (s[l] != s[r]) {
                                c++;
                            }
                            l += d;
                            r -= d;
                        }
                    }
                    if (c < min_c) {
                        min_c = c;
                    }
                }
            }
            cost[i][j] = min_c;
        }
    }
    
    int dp[205][205];
    for (int i = 0; i <= n; i++) {
        for (int p = 0; p <= k; p++) {
            dp[i][p] = 100000;
        }
    }
    dp[0][0] = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int p = 1; p <= k; p++) {
            for (int prev = 0; prev < i; prev++) {
                if (dp[prev][p - 1] != 100000 && cost[prev][i - 1] != 100000) {
                    int val = dp[prev][p - 1] + cost[prev][i - 1];
                    if (val < dp[i][p]) {
                        dp[i][p] = val;
                    }
                }
            }
        }
    }
    
    return dp[n][k];
}
