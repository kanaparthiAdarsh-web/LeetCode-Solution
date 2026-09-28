int maxDepth(char* s) {
    int max = 0;
    int current = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            current++;
            if (current > max) {
                max = current;
            }
        } else if (s[i] == ')') {
            current--;
        }
    }
    return max;
}
