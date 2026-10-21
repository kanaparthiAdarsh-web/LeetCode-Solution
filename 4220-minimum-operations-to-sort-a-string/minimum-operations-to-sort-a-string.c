int minOperations(char* s) {
    int n = strlen(s);
    int sorted = 1;
    for (int i = 1; i < n; i++) {
        if (s[i] < s[i - 1]) {
            sorted = 0;
            break;
        }
    }
    if (sorted) 
        return 0;
    if (n == 2) 
        return -1;

    char mn = s[0], mx = s[0];
    for (int i = 1; i < n; i++) {
        if (s[i] < mn) 
            mn = s[i];
        if (s[i] > mx) 
            mx = s[i];
    }

    if (s[0] == mn || s[n - 1] == mx) 
        return 1;

    for (int i = 0; i < n - 1; i++)
        if (s[i] == mn) 
            return 2;
    
    for (int i = 1; i < n; i++)
        if (s[i] == mx) 
            return 2;
    return 3;
}