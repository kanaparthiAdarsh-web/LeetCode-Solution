int* maxDepthAfterSplit(char* seq, int* returnSize) {
    int len = strlen(seq);
    int* ans = malloc(len * sizeof(int));
    *returnSize = len;
    
    for (int depth = 0,i = 0; i < len; ans[i] = (seq[i] == '(')? depth++ % 2 : --depth % 2,i++);
    

    
    return ans;
}