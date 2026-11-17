/*
 * AnyPush — AI explanation
 * This solution effectively employs a two-phase dynamic programming strategy. The first crucial step, honed from initial attempts, involves precomputing `cost[i][j]` for all substrings `s[i...j]`. This `cost` is the minimum changes to make `s[i...j]` a semi-palindrome, calculated by iterating through all valid periods `d` and summing character mismatches across the `d` interleaved subsequences. This precomputation prevents redundant calculations, a major bottleneck in earlier, more naive approaches.
 *
 * The second phase uses `dp[i][p]` to find the minimum changes to partition `s[0...i-1]` into `p` semi-palindromes, with transitions `dp[i][p] = min(dp[prev][p-1] + cost[prev][i-1])`. This decoupled approach balances `O(N^2 + NK)` space with an `O(N^3 + N^2*K)` time complexity. For N, K <= 200, this is efficient and well within limits.
 *
 * Earlier iterations focused on correctly establishing this two-phase DP logic. While the current version primarily refines syntax for conciseness using ternary and comma operators, a true future improvement for larger N would involve further optimizing the `cost` calculation (e.g., to `O(N^2)` with number theory) or the DP transition. For the given constraints, this solution is robust.
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
                        while (l < r)
                            (s[l] != s[r])?c++:0,l += d,r -= d;
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
            for (int val,prev = 0; prev < i; prev++)
                if (dp[prev][p - 1] != 100000 && cost[prev][i - 1] != 100000)
                    val = dp[prev][p - 1] + cost[prev][i - 1],(val < dp[i][p])?dp[i][p] = val:0;
    
    return dp[n][k];
}
