long long gcd(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) 
        return 0;
    return (a / gcd(a, b)) * b;
}

long long countMultiples(long long m, int* coins, int coinsSize) {
    long long total = 0;
    int num_subsets = 1 << coinsSize;
    
    for (int mask = 1; mask < num_subsets; mask++) {
        long long current_lcm = 1;
        int bits = 0,overflow = 0;
        for (int i = 0; i < coinsSize; i++)
            if (mask & (1 << i)) {
                bits++;
                current_lcm = lcm(current_lcm, coins[i]);
                if (current_lcm > m) {
                    overflow = 1;
                    break;
                }
            }
        
        if (overflow) 
            continue;
        
        if (bits % 2 == 1)
            total += m / current_lcm;
        else 
            total -= m / current_lcm;
    }
    return total;
}

long long findKthSmallest(int* coins, int coinsSize, int k) {
    long long min_coin = coins[0];
    for (int i = 1; i < coinsSize; i++)
        if (coins[i] < min_coin)
            min_coin = coins[i];
    
    long long low = 1;
    long long high = min_coin * (long long)k;
    long long ans = high;
    
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (countMultiples(mid, coins, coinsSize) >= k) {
            ans = mid;
            high = mid - 1;
        } else 
            low = mid + 1;
    }
    
    return ans;
}