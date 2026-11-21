/*
 * AnyPush — AI explanation
 * (AnyPush: AI explanation unavailable — Gemini error 503: {
 *   "error": {
 *     "code": 503,
 *     "message": "This model is currently experiencing high demand. Spikes in demand are usually temporary. Please try again later.",
 *     "status": "UNAVAILABLE"
 *   }
 * }
 * )
 */

static int *head, *to, *nxt;
static int *ans;
static int lastSeen[26];
static char *str;

static void dfs(int u, int p) {
    int c = str[u] - 'a';
    int target = (lastSeen[c] != -1) ? lastSeen[c] : p;
    int prev = lastSeen[c];
    lastSeen[c] = u;

    ans[u] = 1;
    for (int e = head[u]; e != -1; dfs(to[e], u),e = nxt[e]);

    lastSeen[c] = prev;
    if (target != -1)
        ans[target] += ans[u];
}

int* findSubtreeSizes(int* parent, int parentSize, char* s, int* returnSize) {
    int n = parentSize;
    *returnSize = n;
    str = s;

    head = (int*)malloc(n * sizeof(int));
    to = (int*)malloc(n * sizeof(int));
    nxt = (int*)malloc(n * sizeof(int));
    ans = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; head[i] = -1,i++);
    for (int i = 0; i < 26; lastSeen[i] = -1,i++);

    int edgeIdx = 0;
    for (int i = 1; i < n; i++) {
        int p = parent[i];
        to[edgeIdx] = i;
        nxt[edgeIdx] = head[p];
        head[p] = edgeIdx++;
    }

    dfs(0, -1);

    free(head);
    free(to);
    free(nxt);

    return ans;
}
