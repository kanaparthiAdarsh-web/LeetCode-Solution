bool sumGame(char* num) {
    int n = strlen(num);
    int left_sum = 0, right_sum = 0;
    int left_q = 0, right_q = 0;

    for (int i = 0; i < n/2; i++)
        if (num[i] == '?')
            left_q++;
        else
            left_sum += num[i] - '0';

    for (int i = n/2; i < n; i++)
        if (num[i] == '?')
            right_q++;
        else
            right_sum += num[i] - '0';

    if ((left_q + right_q) % 2 != 0)
        return true;
        
    if ((left_sum-right_sum)* 2 == (right_q - left_q) * 9)
        return false;

    return true;
}