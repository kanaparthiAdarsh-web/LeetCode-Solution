static long long power(long long base, long long exp) {
    long long res = 1;
    base %= 1000000007;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % 1000000007;
        
        base = (base * base) % 1000000007;
        exp /= 2;
    }
    return res;
}

static long long modInverse(long long n){
    return power(n, 1000000007 - 2);
}

int numberOfSets(int n, int k) {
    int R = 2 * k;

    if (R >  (n + k - 1)) 
        return 0;
    
    if (R >  (n + k - 1) - R)
        R =  (n + k - 1) - R;
    
    long long num = 1;
    long long den = 1;

    for (int i = 0; i < R; num = (num * ( (n + k - 1) - i)) % 1000000007 ,den = (den * (i + 1)) % 1000000007, i++);

    return (int)((num * modInverse(den)) % 1000000007);
}