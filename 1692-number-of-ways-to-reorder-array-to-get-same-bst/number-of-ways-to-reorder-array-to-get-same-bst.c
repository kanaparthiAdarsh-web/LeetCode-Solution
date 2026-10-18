#define MOD 1000000007

long long comb[1005][1005];

void init() {
    for (int i = 0; i <= 1000; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD,j++);
    }
}

long long solve(int* nums, int size) {
    if (size <= 2) 
        return 1;
    
    int* left = (int*)malloc(size * sizeof(int));
    int* right = (int*)malloc(size * sizeof(int));
    int leftSize = 0, rightSize = 0;
    
    int root = nums[0];
    for (int i = 1; i < size; (nums[i] < root)? (left[leftSize++] = nums[i]) : (right[rightSize++] = nums[i]),i++);
    
    long long leftWays = solve(left, leftSize);
    long long rightWays = solve(right, rightSize);
    
    long long ways = comb[leftSize + rightSize][leftSize];
    ways = (ways * leftWays) % MOD;
    ways = (ways * rightWays) % MOD;
    
    free(left);
    free(right);
    return ways;
}

int numOfWays(int* nums, int numsSize) {
    init();
    return (int)((solve(nums, numsSize) - 1 + MOD) % MOD);
}