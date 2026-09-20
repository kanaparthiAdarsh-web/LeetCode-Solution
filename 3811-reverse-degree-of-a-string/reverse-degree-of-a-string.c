int reverseDegree(char* s) {
    int total = 0;
    for (int i = 0; s[i] != '\0'; total += ('z' - s[i] + 1) * (i + 1), i++);
    return total;
}