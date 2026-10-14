char* maxSumOfSquares(int num, int sum) {
    if (sum > num * 9) {
        char* empty = (char*)malloc(1);
        empty[0] = '\0';
        return empty;
    }

    char* result = (char*)malloc(num + 1);
    result[num] = '\0';

    for (int i = 0; i < num; i++) {
        int val = sum > 9 ? 9 : sum;
        result[i] = '0' + val;
        sum -= val;
    }
    return result;
}