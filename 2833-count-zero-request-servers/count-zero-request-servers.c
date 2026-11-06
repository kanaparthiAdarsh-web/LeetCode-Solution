typedef struct {
    int time;
    int index;
} Query;

typedef struct {
    int time;
    int server_id;
} Log;

int cmpQuery(const void* a, const void* b) {
    Query* q1 = (Query*)a;
    Query* q2 = (Query*)b;
    return (q1->time > q2->time) - (q1->time < q2->time);
}

int cmpLog(const void* a, const void* b) {
    Log* l1 = (Log*)a;
    Log* l2 = (Log*)b;
    return (l1->time > l2->time) - (l1->time < l2->time);
}

int* countServers(int n, int** logs, int logsSize, int* logsColSize, int x, int* queries, int queriesSize, int* returnSize) {
    *returnSize = queriesSize;

    Log* lg = (Log*)malloc(sizeof(Log) * logsSize);
    for (int i = 0; i < logsSize; lg[i].server_id = logs[i][0],lg[i].time = logs[i][1],i++);

    qsort(lg, logsSize, sizeof(Log), cmpLog);

    Query* qs = (Query*)malloc(sizeof(Query) * queriesSize);
    for (int i = 0; i < queriesSize; qs[i].time = queries[i],qs[i].index = i,i++);

    qsort(qs, queriesSize, sizeof(Query), cmpQuery);

    int* cnt = (int*)calloc(n + 1, sizeof(int));
    int* res = (int*)malloc(sizeof(int) * queriesSize);

    int left = 0, right = 0;
    int active = 0;

    for (int i = 0; i < queriesSize; i++) {
        int hi = qs[i].time;
        int lo = hi - x;

        while (right < logsSize && lg[right].time <= hi) {
            if (cnt[lg[right].server_id]++ == 0) 
                active++;
            right++;
        }

        while (left < right && lg[left].time < lo) {
            if (--cnt[lg[left].server_id] == 0) 
                active--;
            left++;
        }

        res[qs[i].index] = n - active;
    }

    free(lg);
    free(qs);
    free(cnt);
    return res;
}