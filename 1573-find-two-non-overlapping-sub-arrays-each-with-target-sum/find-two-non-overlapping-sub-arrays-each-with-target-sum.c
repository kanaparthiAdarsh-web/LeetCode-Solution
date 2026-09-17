int minSumOfLengths(int* arr, int arrSize, int target) {
    int* min_len = (int*)malloc(arrSize * sizeof(int));
    int INF = 1e9;

    for (int i = 0; i < arrSize; i++)
        min_len[i] = INF;

    int left = 0;
    int current_sum = 0;
    int ans = INF;

    for (int right = 0; right < arrSize; right++) {
        current_sum += arr[right];

        while (current_sum > target && left <= right) {
            current_sum -= arr[left];
            left++;
        }

        if (current_sum == target) {
            int len = right - left + 1;

            if (left > 0 && min_len[left - 1] != INF)
                if (len + min_len[left - 1] < ans)
                    ans = len + min_len[left - 1];

            int prev_min = (right > 0) ? min_len[right - 1] : INF;
            min_len[right] = (len < prev_min) ? len : prev_min;
        } else
            min_len[right] = (right > 0) ? min_len[right - 1] : INF;
    }

    free(min_len);
    return (ans >= INF) ? -1 : ans;
}