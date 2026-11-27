/*
 * AnyPush — AI explanation
 * This solution combines pre-computation and dynamic programming.
 * First, it calculates `multCount[v]`, representing the total items obtained if an item with value `v` is purchased (due to the rule of getting all items whose values are multiples of `v`). The minimum item price `minPrice` is also determined.
 * Next, a 0/1 knapsack DP `dp[c]` tracks the maximum *total items gained via the rule* for a budget `c`. Each original item `(price, value)` is considered, contributing `multCount[value]` if purchased.
 * Finally, the optimal solution is found by iterating through all `dp[c]` states, using the remaining budget `(budget - c)` to buy additional items at `minPrice`.
 *
 * Time complexity: O(itemsSize * budget + MAX_VALUE * log(MAX_VALUE)). Justified by knapsack DP (`itemsSize * budget`) and efficient pre-calculation of multiples (`MAX_VALUE * log(MAX_VALUE)`).
 * Space complexity: O(budget + MAX_VALUE) for DP table and auxiliary arrays.
 *
 * This approach is well-suited because it efficiently handles the "multiples" rule with pre-computation, transforming the problem into a standard knapsack. The given constraints on `itemsSize`, `budget`, and `MAX_VALUE` (1500) allow this complexity.
 *
 * A purely greedy strategy would likely fail due to the complex interaction between item prices, "values", and the freebie rule. An earlier attempt might struggle with how to correctly count items from multiples without this pre-aggregation.
 */

#include <stdlib.h>

int maximumSaleItems(int** items, int itemsSize, int* itemsColSize, int budget) {
    int freq[1501] = {0};
    int multCount[1501] = {0};
    int minPrice = 1501;

    for (int i = 0; i < itemsSize; i++) {
        freq[items[i][0]]++;
        if (items[i][1] < minPrice)
            minPrice = items[i][1];
    }

    for (int f = 1; f <= 1500; f++) {
        if (freq[f] > 0) {
            for (int m = f; m <= 1500; m += f)
                multCount[f] += freq[m];
        }
    }

    int* dp = (int*)calloc(budget + 1, sizeof(int));

    for (int i = 0; i < itemsSize; i++) {
        int price = items[i][1];
        int val = multCount[items[i][0]];
        for (int c = budget; c >= price; c--) {
            if (dp[c - price] + val > dp[c])
                dp[c] = dp[c - price] + val;
        }
    }

    int ans = 0;
    for (int c = 0; c <= budget; c++) {
        int total = dp[c] + (budget - c) / minPrice;
        if (total > ans)
            ans = total;
    }

    free(dp);
    return ans;
}
