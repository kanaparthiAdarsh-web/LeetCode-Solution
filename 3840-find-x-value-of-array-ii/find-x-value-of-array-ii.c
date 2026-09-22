struct Node {
    int remain[5];
    int prod;
};

struct Node mergeNodes(struct Node left, struct Node right, int k) {
    struct Node node;
    node.prod = (left.prod * right.prod) % k;
    for (int i = 0; i < k; ++i) {
        node.remain[i] = left.remain[i];
    }
    for (int i = 0; i < k; ++i) {
        node.remain[(i * left.prod) % k] += right.remain[i];
    }
    return node;
}

void build(int* nums, int k, int cur, int left, int right, struct Node* tree) {
    for (int i = 0; i < k; ++i) {
        tree[cur].remain[i] = 0;
    }
    if (left == right) {
        tree[cur].remain[nums[left] % k] = 1;
        tree[cur].prod = nums[left] % k;
        return;
    }
    int mid = (left + right) / 2;
    build(nums, k, 2 * cur + 1, left, mid, tree);
    build(nums, k, 2 * cur + 2, mid + 1, right, tree);
    tree[cur] = mergeNodes(tree[2 * cur + 1], tree[2 * cur + 2], k);
}

void updateTree(int treeIndex, int lo, int hi, int i, int val, int k, struct Node* tree) {
    if (lo == hi) {
        for (int j = 0; j < k; ++j) {
            tree[treeIndex].remain[j] = 0;
        }
        tree[treeIndex].remain[val % k] = 1;
        tree[treeIndex].prod = val % k;
        return;
    }
    int mid = (lo + hi) / 2;
    if (i <= mid) {
        updateTree(2 * treeIndex + 1, lo, mid, i, val, k, tree);
    } else {
        updateTree(2 * treeIndex + 2, mid + 1, hi, i, val, k, tree);
    }
    tree[treeIndex] = mergeNodes(tree[2 * treeIndex + 1], tree[2 * treeIndex + 2], k);
}

struct Node queryTree(int treeIndex, int lo, int hi, int i, int j, int k, struct Node* tree) {
    if (i <= lo && hi <= j) {
        return tree[treeIndex];
    }
    if (j < lo || hi < i) {
        struct Node emptyNode;
        emptyNode.prod = 1;
        for (int idx = 0; idx < k; ++idx) {
            emptyNode.remain[idx] = 0;
        }
        return emptyNode;
    }
    int mid = (lo + hi) / 2;
    struct Node leftNode = queryTree(2 * treeIndex + 1, lo, mid, i, j, k, tree);
    struct Node rightNode = queryTree(2 * treeIndex + 2, mid + 1, hi, i, j, k, tree);
    return mergeNodes(leftNode, rightNode, k);
}

int* resultArray(int* nums, int numsSize, int k, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    for (int i = 0; i < numsSize; ++i) {
        nums[i] %= k;
    }
    struct Node* tree = (struct Node*)malloc(4 * numsSize * sizeof(struct Node));
    build(nums, k, 0, 0, numsSize - 1, tree);

    int* ans = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;

    for (int q = 0; q < queriesSize; ++q) {
        int index = queries[q][0];
        int value = queries[q][1] % k;
        int start = queries[q][2];
        int x = queries[q][3];

        updateTree(0, 0, numsSize - 1, index, value, k, tree);
        struct Node resNode = queryTree(0, 0, numsSize - 1, start, numsSize - 1, k, tree);
        ans[q] = resNode.remain[x];
    }

    free(tree);
    return ans;
}