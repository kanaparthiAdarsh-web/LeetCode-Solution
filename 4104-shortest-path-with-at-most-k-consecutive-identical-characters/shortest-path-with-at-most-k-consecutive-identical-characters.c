typedef struct {
    int d;
    int u;
    int run;
} Node;

static int head[50005], nxt[50005], to[50005], weight[50005];
static int dist[50005][52];
static int min_run[50005];
static Node heap[2600005];
static int heapSize;

static inline void push(int d, int u, int run) {
    int i = ++heapSize;
    while (i > 1) {
        int p = i >> 1;
        if (heap[p].d <= d) break;
        heap[i] = heap[p];
        i = p;
    }
    heap[i].d = d;
    heap[i].u = u;
    heap[i].run = run;
}

static inline Node pop() {
    Node ret = heap[1];
    Node last = heap[heapSize--];
    int i = 1;
    while ((i << 1) <= heapSize) {
        int child = i << 1;
        if (child < heapSize && heap[child + 1].d < heap[child].d) {
            child++;
        }
        if (last.d <= heap[child].d) break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = last;
    return ret;
}

int shortestPath(int n, int** edges, int edgesSize, int* edgesColSize, char* labels, int k) {
    for (int i = 0; i < n; i++) {
        head[i] = -1;
        min_run[i] = k + 1;
        for (int j = 1; j <= k; j++) {
            dist[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        to[i] = edges[i][1];
        weight[i] = edges[i][2];
        nxt[i] = head[u];
        head[u] = i;
    }

    heapSize = 0;
    dist[0][1] = 0;
    push(0, 0, 1);

    while (heapSize > 0) {
        Node cur = pop();
        int d = cur.d;
        int u = cur.u;
        int run = cur.run;

        if (u == n - 1) return d;
        if (d > dist[u][run] || run >= min_run[u]) continue;
        min_run[u] = run;

        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            int w = weight[e];
            int nr = (labels[v] == labels[u]) ? run + 1 : 1;
            if (nr <= k && nr < min_run[v] && d + w < dist[v][nr]) {
                dist[v][nr] = d + w;
                push(d + w, v, nr);
            }
        }
    }

    return -1;
}