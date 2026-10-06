int minAddToMakeValid(char* s) {
    int open = 0;
    int mismatches = 0;
    for (int i = 0; s[i] ; (s[i] == '(')? open++ : ((open > 0)? open-- : mismatches++),i++);

    return open + mismatches;
}