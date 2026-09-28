char* reverseParentheses(char* s) {
    int len = strlen(s);
    int* pair = malloc(len * sizeof(int));
    int* stack = malloc(len * sizeof(int));
    int top = -1;

    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            stack[++top] = i;
        } else if (s[i] == ')') {
            int j = stack[top--];
            pair[i] = j;
            pair[j] = i;
        }
    }

    char* res = malloc(len + 1);
    int resLen = 0;
    int curr = 0;
    int direction = 1;

    while (curr < len) {
        if (s[curr] == '(' || s[curr] == ')') {
            curr = pair[curr];
            direction = -direction;
        } else {
            res[resLen++] = s[curr];
        }
        curr += direction;
    }
    res[resLen] = '\0';

    free(pair);
    free(stack);
    return res;
}