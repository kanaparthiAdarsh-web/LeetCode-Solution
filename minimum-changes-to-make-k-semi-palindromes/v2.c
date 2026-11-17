/*
 * AnyPush — AI explanation
 * This solution implements a two-phase dynamic programming strategy.
 * First, it precomputes `cost[i][j]`, the minimum changes to make `s[i...j]` a semi-palindrome. This phase efficiently iterates through all possible periods `d` for each substring, summing mismatches within the `d` induced palindromic sequences. This costs `O(N^3 * tau(N))` time, where `tau(N)` is the number of divisors, and `O(N^2)` space for the `cost` table.
 * Second, a classic partition DP, `dp[i][p]`, calculates the minimum changes to partition `s[0...i-1]` into `p` semi-palindromes. The recurrence `dp[i][p] = min(dp[prev][p-1] + cost[prev][i-1])` iterates through all split points. This phase runs in `O(N^2 * K)` time, using `O(N*K)` space.
 * Overall complexity is `O(N^3 * tau(N) + N^2 * K)` time and `O(N^2)` space (given `N,K <= N`). This phased approach is critical for tractability; avoiding on-the-fly cost recalculation prevents an `O(N^5)` naive solution from TLE.
 * While efficient, further minor constant factor optimization might be possible in `cost` calculation for larger `N` by pre-filtering divisors, but the current performance is well-suited for N=200.
 */

int minimumChanges(char* s, int k) {
    int n = strlen(s);
    int cost[205][205];
    
    for (int i = 0; i < n; i++)
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
                    if (c < min_c)
                        min_c = c;
                    
                }
            }
            cost[i][j] = min_c;
        }
    
    int dp[205][205];
    for (int i = 0; i <= n; i++)
        for (int p = 0; p <= k; dp[i][p] = 100000,p++);
    dp[0][0] = 0;
    
    for (int i = 1; i <= n; i++)
        for (int p = 1; p <= k; p++)
            for (int prev = 0; prev < i; prev++) {
                if (dp[prev][p - 1] != 100000 && cost[prev][i - 1] != 100000) {
                    int val = dp[prev][p - 1] + cost[prev][i - 1];
                    if (val < dp[i][p]) {
                        dp[i][p] = val;
                    }
                }
            }
    
    return dp[n][k];
}
