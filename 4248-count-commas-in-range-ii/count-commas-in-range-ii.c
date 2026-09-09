long long countCommas(long long n) {
    long long ans = 0;
    long long threshold = 1000LL;

    while (n >= threshold) {
        ans += (n - threshold + 1);

        if (threshold > 1000000000000000LL / 1000LL)
            break;
        threshold *= 1000LL;
    }

    return ans;
}