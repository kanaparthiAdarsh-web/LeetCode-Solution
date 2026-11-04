int cmp(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

void update(int idx, int val_cnt, long long val_sum, int U, long long* bit_cnt, long long* bit_sum) {
    for (int i = idx; i <= U; bit_cnt[i] += val_cnt, bit_sum[i] += val_sum, i += i & -i);
}

void query(int idx, long long* cnt_out, long long* sum_out, long long* bit_cnt, long long* bit_sum) {
    long long c = 0, s = 0;
    for (int i = idx; i > 0; c += bit_cnt[i], s += bit_sum[i], i -= i & -i);
    *cnt_out = c;
    *sum_out = s;
}

long long minOperations(int* nums, int numsSize, int x, int k) {
    int n = numsSize;
    int* sorted = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; sorted[i] = nums[i],i++);
    qsort(sorted, n, sizeof(int), cmp);

    int U = 1;
    for (int i = 1; i < n; i++)
        if (sorted[i] != sorted[i - 1])
            sorted[U++] = sorted[i];

    long long* bit_cnt = (long long*)calloc(U + 1, sizeof(long long));
    long long* bit_sum = (long long*)calloc(U + 1, sizeof(long long));

    int m = n - x + 1;
    long long* cost = (long long*)malloc(m * sizeof(long long));

    int* temp_sorted = sorted;
    int U_len = U;

    int get_idx(int val) {
        int* ptr = (int*)bsearch(&val, temp_sorted, U_len, sizeof(int), cmp);
        return (int)(ptr - temp_sorted) + 1;
    }

    int target_k = (x + 1) / 2;

    for (int i = 0; i < n; i++) {
        int idx = get_idx(nums[i]);
        update(idx, 1, nums[i], U, bit_cnt, bit_sum);
        if (i >= x) {
            int rem_idx = get_idx(nums[i - x]);
            update(rem_idx, -1, -nums[i - x], U, bit_cnt, bit_sum);
        }
        if (i >= x - 1) {
            int current_idx = 0;
            long long current_cnt = 0;
            int max_bit = 1;
            while (max_bit <= U) max_bit <<= 1;
            max_bit >>= 1;

            for (int mask = max_bit; mask > 0; mask >>= 1) {
                int next_idx = current_idx + mask;
                if (next_idx <= U && current_cnt + bit_cnt[next_idx] < target_k) {
                    current_cnt += bit_cnt[next_idx];
                    current_idx = next_idx;
                }
            }
            int median_idx = current_idx + 1;
            long long median_val = sorted[median_idx - 1];

            long long cnt_le = 0, sum_le = 0;
            query(median_idx, &cnt_le, &sum_le, bit_cnt, bit_sum);

            long long total_cnt = x;
            long long total_sum = 0;
            long long dummy_c = 0;
            query(U, &dummy_c, &total_sum, bit_cnt, bit_sum);

            long long cnt_gt = total_cnt - cnt_le;
            long long sum_gt = total_sum - sum_le;

            long long ops = (median_val * cnt_le - sum_le) + (sum_gt - median_val * cnt_gt);
            cost[i - x + 1] = ops;
        }
    }

    long long* dp_prev = (long long*)malloc((m + 1) * sizeof(long long));
    long long* dp_curr = (long long*)malloc((m + 1) * sizeof(long long));

    for (int i = 0; i <= m; i++) dp_prev[i] = 0;

    long long INF = 1e15;

    for (int j = 1; j <= k; j++) {
        for (int i = 0; i <= m; i++) dp_curr[i] = INF;
        long long min_prev = INF;
        for (int i = 1; i <= m; i++) {
            int prev_idx = i - x;
            if (prev_idx < 0) prev_idx = 0;
            if (dp_prev[prev_idx] < min_prev) {
                min_prev = dp_prev[prev_idx];
            }
            long long option1 = dp_curr[i - 1];
            long long option2 = min_prev + cost[i - 1];
            dp_curr[i] = (option1 < option2) ? option1 : option2;
        }
        long long* temp = dp_prev;
        dp_prev = dp_curr;
        dp_curr = temp;
    }

    long long ans = dp_prev[m];

    free(sorted);
    free(bit_cnt);
    free(bit_sum);
    free(cost);
    free(dp_prev);
    free(dp_curr);

    return ans;
}