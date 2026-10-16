#define MOD 1000000007LL
typedef long long ll;

static ll sm[400005], sq[400005], lz[400005];
static int last[100005];

static void apply(int node, int len, ll d) {
    sq[node] = (sq[node] + 2 * d % MOD * sm[node] + d * d % MOD * len) % MOD;
    sm[node] = (sm[node] + d * len) % MOD;
    lz[node] = (lz[node] + d) % MOD;
}

static void push(int node, int s, int e) {
    if (lz[node]) {
        apply(2 * node, ((s + e) / 2) - s + 1, lz[node]);
        apply(2 * node + 1, e - ((s + e) / 2), lz[node]);
        lz[node] = 0;
    }
}

static void update(int node, int s, int e, int l, int r) {
    if (r < s || e < l) 
        return;
    if (l <= s && e <= r) { 
        apply(node, e - s + 1, 1);
        return; 
    }
    push(node, s, e);
    update(2 * node, s, ((s + e) / 2), l, r);
    update(2 * node + 1, ((s + e) / 2) + 1, e, l, r);
    sm[node] = (sm[2 * node] + sm[2 * node + 1]) % MOD;
    sq[node] = (sq[2 * node] + sq[2 * node + 1]) % MOD;
}

int sumCounts(int* nums, int n) {
    memset(sm, 0, sizeof(ll) * 4 * (n + 1));
    memset(sq, 0, sizeof(ll) * 4 * (n + 1));
    memset(lz, 0, sizeof(ll) * 4 * (n + 1));
    for (int i = 0; i < 100005; last[i] = -1,i++);

   ll ans = 0;
    for (int j = 0; j < n; update(1, 0, n - 1, last[nums[j]] + 1, j),last[nums[j]] = j,ans = (ans + sq[1]) % MOD,j++);
    
    return (int)ans;
}