#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int max_len;
    int prefix_len;
    int suffix_len;
    int len;
    char left_char;
    char right_char;
} Node;

static Node* tree;
static char* str;

Node merge_nodes(Node left, Node right) {
    Node res;
    res.len = left.len + right.len;
    res.left_char = left.left_char;
    res.right_char = right.right_char;
    
    res.max_len = (left.max_len > right.max_len) ? left.max_len : right.max_len;
    
    if (left.right_char == right.left_char) {
        int cross = left.suffix_len + right.prefix_len;
        if (cross > res.max_len) {
            res.max_len = cross;
        }
    }
    
    res.prefix_len = left.prefix_len;
    if (left.prefix_len == left.len && left.left_char == right.left_char) {
        res.prefix_len += right.prefix_len;
    }
    
    res.suffix_len = right.suffix_len;
    if (right.suffix_len == right.len && right.right_char == left.right_char) {
        res.suffix_len += left.suffix_len;
    }
    
    return res;
}

void build(int node, int start, int end) {
    if (start == end) {
        tree[node].max_len = 1;
        tree[node].prefix_len = 1;
        tree[node].suffix_len = 1;
        tree[node].len = 1;
        tree[node].left_char = str[start];
        tree[node].right_char = str[start];
        return;
    }
    int mid = start + (end - start) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = merge_nodes(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int start, int end, int idx, char val) {
    if (start == end) {
        str[idx] = val;
        tree[node].left_char = val;
        tree[node].right_char = val;
        return;
    }
    int mid = start + (end - start) / 2;
    if (idx <= mid) {
        update(2 * node, start, mid, idx, val);
    } else {
        update(2 * node + 1, mid + 1, end, idx, val);
    }
    tree[node] = merge_nodes(tree[2 * node], tree[2 * node + 1]);
}

int* longestRepeating(char* s, char* queryCharacters, int* queryIndices, int queryIndicesSize, int* returnSize) {
    int n = strlen(s);
    str = s;
    
    tree = (Node*)malloc(4 * n * sizeof(Node));
    build(1, 0, n - 1);
    
    int* ans = (int*)malloc(queryIndicesSize * sizeof(int));
    *returnSize = queryIndicesSize;
    
    for (int i = 0; i < queryIndicesSize; i++) {
        int idx = queryIndices[i];
        char val = queryCharacters[i];
        if (s[idx] != val) {
            update(1, 0, n - 1, idx, val);
        }
        ans[i] = tree[1].max_len;
    }
    
    free(tree);
    return ans;
}