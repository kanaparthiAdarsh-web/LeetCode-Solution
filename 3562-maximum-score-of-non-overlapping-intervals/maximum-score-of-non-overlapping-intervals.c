typedef struct {
    long long l;
    long long r;
    long long weight;
    int id;
} Interval;

typedef struct {
    long long weight;
    int count;
    int idx[4];
} DPState;

static int cmpIntervals(const void* a, const void* b) {
    const Interval* ia = (const Interval*)a;
    const Interval* ib = (const Interval*)b;
    if (ia->l != ib->l) return (ia->l < ib->l) ? -1 : 1;
    if (ia->r != ib->r) return (ia->r < ib->r) ? -1 : 1;
    return (ia->id < ib->id) ? -1 : 1;
}

static int compareStates(const DPState* a, const DPState* b) {
    if (a->weight != b->weight) 
        return (a->weight > b->weight) ? 1 : -1;
    int minLen = a->count < b->count ? a->count : b->count;
    for (int i = 0; i < minLen; i++) 
        if (a->idx[i] != b->idx[i]) 
            return (a->idx[i] < b->idx[i]) ? 1 : -1;
    if (a->count != b->count)
        return (a->count < b->count) ? 1 : -1;
    return 0;
}

int* maximumWeight(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize) {
    int n = intervalsSize;
    Interval* arr = (Interval*)malloc(n * sizeof(Interval));
    for (int i = 0; i < n; i++) {
        arr[i].l = intervals[i][0];
        arr[i].r = intervals[i][1];
        arr[i].weight = intervals[i][2];
        arr[i].id = i;
    }

    qsort(arr, n, sizeof(Interval), cmpIntervals);

    int* nxt = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int low = i + 1, high = n - 1;
        int ans = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid].l > arr[i].r) {
                ans = mid;
                high = mid - 1;
            } else
                low = mid + 1;
        }
        nxt[i] = ans;
    }

    DPState (*dp)[5] = (DPState (*)[5])calloc((n + 1), sizeof(*dp));

    for (int i = n - 1; i >= 0; i--) {
        for (int c = 1; c <= 4; c++) {
            DPState best = dp[i + 1][c];

            DPState take;
            take.weight = arr[i].weight + dp[nxt[i]][c - 1].weight;
            take.count = 1 + dp[nxt[i]][c - 1].count;
            int insertVal = arr[i].id;
            int p = 0;
            int placed = 0;
            for (int k = 0; k < dp[nxt[i]][c - 1].count; k++) {
                int existing = dp[nxt[i]][c - 1].idx[k];
                if (!placed && insertVal < existing) {
                    take.idx[p++] = insertVal;
                    placed = 1;
                }
                take.idx[p++] = existing;
            }
            if (!placed)
                take.idx[p++] = insertVal;

           dp[i][c] = (compareStates(&take, &best) > 0)? take : best;
        }
    }

    DPState res = dp[0][4];
    *returnSize = res.count;
    int* result = (int*)malloc(res.count * sizeof(int));
    for (int i = 0; i < res.count; i++)
        result[i] = res.idx[i];

    free(arr);
    free(nxt);
    free(dp);

    return result;
}