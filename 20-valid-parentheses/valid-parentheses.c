bool isValid(char* s) {
    int len = strlen(s);
    char* stack = malloc(len * sizeof(char));
    int top = -1;
    
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[')
            stack[++top] = c;
        else {
            if (top == -1) {
                free(stack);
                return false;
            }
            char topChar = stack[top--];
            if ((c == ')' && topChar != '(') ||
                (c == '}' && topChar != '{') ||
                (c == ']' && topChar != '[')) {
                free(stack);
                return false;
            }
        }
    }
    
    bool res = (top == -1);
    free(stack);
    return res;
}