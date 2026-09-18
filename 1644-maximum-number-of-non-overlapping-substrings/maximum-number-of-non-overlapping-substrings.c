#include <stdlib.h>
#include <string.h>

typedef struct {
    int l;
    int r;
} Interval;

static int cmp(const void* a, const void* b) {
    return ((const Interval*)a)->r - ((const Interval*)b)->r;
}

char** maxNumOfSubstrings(char* s, int* returnSize) {
    int n = strlen(s);
    int first[26], last[26];
    for (int i = 0; i < 26; first[i] = -1 , last[i] = -1, i++);

    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        if (first[c] == -1)
            first[c] = i;
        last[c] = i;
    }

    Interval candidates[26];
    int candCount = 0;

    for (int i = 0; i < 26; i++) {
        if (first[i] == -1)
            continue;

        int l = first[i];
        int r = last[i];
        int valid = 1;

        for (int j = l; j <= r; j++) {
            int c = s[j] - 'a';
            if (first[c] < l) {
                valid = 0;
                break;
            }
            if (last[c] > r) 
                r = last[c];
        }

        if (valid) {
            candidates[candCount].l = l;
            candidates[candCount].r = r;
            candCount++;
        }
    }

    qsort(candidates, candCount, sizeof(Interval), cmp);

    char** result = (char**)malloc(26 * sizeof(char*));
    int count = 0;
    int prev_r = -1;

    for (int i = 0; i < candCount; i++)
        if (candidates[i].l > prev_r) {
            int len = candidates[i].r - candidates[i].l + 1;
            result[count] = (char*)malloc((len + 1) * sizeof(char));
            strncpy(result[count], s + candidates[i].l, len);
            result[count][len] = '\0';
            count++;
            prev_r = candidates[i].r;
        }

    *returnSize = count;
    return result;
}