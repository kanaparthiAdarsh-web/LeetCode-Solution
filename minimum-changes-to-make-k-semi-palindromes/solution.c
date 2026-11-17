/*
 * AnyPush — AI explanation
 * This solution employs a two-phase dynamic programming approach to efficiently solve the problem.
 * First, we precompute `cost[i][j]`: the minimum changes needed to make the substring `s[i...j]` a semi-palindrome. This involves iterating through all possible divisors `d` of the substring length and calculating mismatches for the `d` interleaved palindromic sequences.
 * Second, `dp[i][p]` stores the minimum changes to partition `s[0...i-1]` into `p` semi-palindromes. The transitions are `dp[i][p] = min(dp[prev][p-1] + cost[prev][i-1])` for all valid `prev`.
 *
 * Time complexity is `O(N^3)`: `O(N^3)` for precomputing all `cost[i][j]` (each `O(N)` due to `N * d_max` divisor checks, where `d_max` is the maximum number of divisors for numbers up to `N`) and `O(N^2 K)` for the main DP. Space complexity is `O(N^2)` for the `cost` and `dp` tables.
 *
 * This approach is highly effective because precomputing substring costs (`cost` array) prevents redundant calculations, allowing `O(1)` lookup during the main DP. A naive attempt, like earlier thoughts, that re-calculated `cost[prev][i-1]` on-the-fly would lead to an `O(N^5)` complexity, resulting in a TLE. The `O(N^2)` space is a crucial trade-off for this substantial time saving. The `O(N^3)` overall is robust for `N=200`.
 */

int minimumChanges(char* s, int k) {
    int n = strlen(s);
    int cost[205][205];
    
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            int len = j - i + 1;
            int min_c = 100000;
            
            for (int d = 1; d < len; d++)
                if (len % d == 0) {
                    int c = 0;
                    for (int rem = 0; rem < d; rem++) {
                        int l = i + rem;
                        int r = j - (d - 1 - rem);
                        while (l < r) {
                            if (s[l] != s[r])
                                c++;
                            l += d;
                            r -= d;
                        }
                    }
                    if (c < min_c)
                        min_c = c;
                    
                }
            cost[i][j] = min_c;
        }
    
    int dp[205][205];
    for (int i = 0; i <= n; i++)
        for (int p = 0; p <= k; dp[i][p] = 100000,p++);
    dp[0][0] = 0;
    
    for (int i = 1; i <= n; i++)
        for (int p = 1; p <= k; p++)
            for (int prev = 0; prev < i; prev++)
                if (dp[prev][p - 1] != 100000 && cost[prev][i - 1] != 100000) {
                    int val = dp[prev][p - 1] + cost[prev][i - 1];
                    if (val < dp[i][p])
                        dp[i][p] = val;
                }
    
    return dp[n][k];
}
