/*
 * AnyPush — AI explanation
 * This solution addresses a unique "buy one, get one free" problem variant. It first precomputes `freq[T]` (count of items of type T) and `multCount[T]` (sum of frequencies for types whose frequencies are multiples of T).
 * For each item `[type, price]`, `multCount[type] - 1` indicates the number of "buy one, get one free" vouchers available at that price. These discounted bundles (costing `price` for 2 items) are collected, filtered if their price is strictly worse than buying two cheapest single items, and sorted by price.
 * A greedy strategy then takes as many of the cheapest bundles as possible within the budget. Finally, any remaining budget is used to buy individual items at the overall minimum price.
 *
 * Time: O(N log N) due to `multCount` precomputation (sum over multiples) and sorting.
 * Space: O(N) for frequency arrays and item storage.
 *
 * This approach efficiently transforms complex discount rules into standard greedy choices, optimal for this problem structure. A naive dynamic programming or combinatorial approach would be too slow. The `2*minPrice` filter is a helpful heuristic to prune clearly suboptimal deals.
 */

#include <stdlib.h>

typedef struct {
    int price;
    int cap;
} Item;

static int cmp(const void* a, const void* b) {
    int p1 = ((const Item*)a)->price;
    int p2 = ((const Item*)b)->price;
    return (p1 > p2) - (p1 < p2);
}

int maximumSaleItems(int** items, int itemsSize, int* itemsColSize, int budget) {
    int n = itemsSize;
    int* freq = (int*)calloc(n + 1, sizeof(int));
    int* multCount = (int*)calloc(n + 1, sizeof(int));
    int minPrice = items[0][1];

    for (int i = 0; i < n; i++) {
        freq[items[i][0]]++;
        if (items[i][1] < minPrice)
            minPrice = items[i][1];
    }

    for (int f = 1; f <= n; f++)
        if (freq[f] > 0) 
            for (int m = f; m <= n; m += f)
                multCount[f] += freq[m];

    Item* arr = (Item*)malloc(n * sizeof(Item));
    int count = 0;
    long long limit = 2LL * minPrice;

    for (int i = 0; i < n; i++) {
        int cap = multCount[items[i][0]] - 1;
        if (cap > 0 && items[i][1] < limit) {
            arr[count].price = items[i][1];
            arr[count].cap = cap;
            count++;
        }
    }

    qsort(arr, count, sizeof(Item), cmp);

    long long rem = budget;
    long long ans = 0;

    for (int i = 0; i < count && rem >= arr[i].price; i++) {
        long long take = rem / arr[i].price;
        if (take > arr[i].cap)
            take = arr[i].cap;
        ans += 2 * take;
        rem -= take * arr[i].price;
    }

    ans += rem / minPrice;

    free(freq);
    free(multCount);
    free(arr);

    return (int)ans;
}
