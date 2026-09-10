struct SubtreeData {
    int sum;
    int count;
};

static struct SubtreeData dfs(struct TreeNode* root, int* matchingNodes) {
    if (root == NULL) {
        struct SubtreeData empty = {0, 0};
        return empty;
    }

    struct SubtreeData left = dfs(root->left, matchingNodes);
    struct SubtreeData right = dfs(root->right, matchingNodes);

    int totalSum = left.sum + right.sum + root->val;
    int totalCount = left.count + right.count + 1;

    if (totalSum / totalCount == root->val)
        (*matchingNodes)++;

    struct SubtreeData res = {totalSum, totalCount};
    return res;
}

int averageOfSubtree(struct TreeNode* root) {
    int matchingNodes = 0;
    dfs(root, &matchingNodes);
    return matchingNodes;
}