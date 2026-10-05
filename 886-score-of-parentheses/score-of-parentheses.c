int scoreOfParentheses(char* s) {
    int* stack = malloc(strlen(s) * sizeof(int));
    int score = 0;
    for (int top = -1,i = 0; i < strlen(s); (s[i] == '(')? (stack[++top] = score,score = 0) :(score = stack[top--] + (score == 0 ? 1 : 2 * score)), i++);
    free(stack);
    return score;
}