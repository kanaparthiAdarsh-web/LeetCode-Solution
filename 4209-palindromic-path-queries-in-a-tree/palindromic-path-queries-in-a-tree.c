static int up[16][50005];
static int depth[50005], tin[50005], tout[50005], base[50005], par[50005];
static int bit[50010];
static int bn;

static void add(int i, int v) {
    for (; i <= bn; i += i & -i) 
        bit[i] ^= v;
}

static int pref(int i) {
    int r = 0;
    for (; i > 0; i -= i & -i) 
        r ^= bit[i];
    return r;
}

static int lca(int a, int b) {
    if (depth[a] < depth[b]) { int t = a; a = b; b = t; }
    int diff = depth[a] - depth[b];
    for (int k = 0; k < 16; k++) {
        if (diff >> k & 1) a = up[k][a];
    }
    if (a == b) return a;
    for (int k = 15; k >= 0; k--) {
        if (up[k][a] != up[k][b]) {
            a = up[k][a];
            b = up[k][b];
        }
    }
    return up[0][a];
}

bool* palindromePath(int n, int** edges, int edgesSize, int* edgesColSize, char* s, char** queries, int queriesSize, int* returnSize) {
    int* head = (int*)malloc(sizeof(int) * n);
    int* nxt = (int*)malloc(sizeof(int) * 2 * n);
    int* to = (int*)malloc(sizeof(int) * 2 * n);
    int* it = (int*)malloc(sizeof(int) * n);
    int* stack = (int*)malloc(sizeof(int) * n);
    int cnt = 0;

    for (int i = 0; i < n; i++) head[i] = -1;
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0], v = edges[i][1];
        to[cnt] = v; nxt[cnt] = head[u]; head[u] = cnt++;
        to[cnt] = u; nxt[cnt] = head[v]; head[v] = cnt++;
    }

    int timer = 0, sp = 0;
    par[0] = -1;
    up[0][0] = 0;
    depth[0] = 0;
    base[0] = 1 << (s[0] - 'a');
    tin[0] = ++timer;
    for (int i = 0; i < n; i++) it[i] = head[i];
    stack[sp++] = 0;

    while (sp > 0) {
        int v = stack[sp - 1];
        if (it[v] != -1) {
            int e = it[v];
            it[v] = nxt[e];
            int w = to[e];
            if (w == par[v]) continue;
            par[w] = v;
            up[0][w] = v;
            depth[w] = depth[v] + 1;
            base[w] = base[v] ^ (1 << (s[w] - 'a'));
            tin[w] = ++timer;
            stack[sp++] = w;
        } else {
            tout[v] = timer;
            sp--;
        }
    }

    for (int k = 1; k < 16; k++) {
        for (int v = 0; v < n; v++) {
            up[k][v] = up[k - 1][up[k - 1][v]];
        }
    }

    bn = n + 1;
    memset(bit, 0, sizeof(int) * (n + 5));

    bool* res = (bool*)malloc(sizeof(bool) * queriesSize);
    int rc = 0;

    for (int i = 0; i < queriesSize; i++) {
        char* q = queries[i];
        if (q[0] == 'u') {
            int u;
            char c;
            sscanf(q, "%*s %d %c", &u, &c);
            int oldb = s[u] - 'a';
            int newb = c - 'a';
            if (oldb != newb) {
                int x = (1 << oldb) ^ (1 << newb);
                add(tin[u], x);
                add(tout[u] + 1, x);
                s[u] = c;
            }
        } else {
            int u, v;
            sscanf(q, "%*s %d %d", &u, &v);
            int l = lca(u, v);
            int pu = base[u] ^ pref(tin[u]);
            int pv = base[v] ^ pref(tin[v]);
            int mask = pu ^ pv ^ (1 << (s[l] - 'a'));
            res[rc++] = (mask & (mask - 1)) == 0;
        }
    }

    *returnSize = rc;
    free(head);
    free(nxt);
    free(to);
    free(it);
    free(stack);
    return res;
}