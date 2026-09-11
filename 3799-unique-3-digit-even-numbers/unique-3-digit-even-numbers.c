int totalNumbers(int* digits, int digitsSize) {
    int freq[10] = {0};
    for (int i = 0; i < digitsSize; freq[digits[i]]++, i++);

    int count = 0;
    for (int num = 100; num < 1000; num += 2) {
        int d1 = num / 100;
        int d2 = (num / 10) % 10;
        int d3 = num % 10;

        int req[10] = {0};
        req[d1]++;
        req[d2]++;
        req[d3]++;

        if (freq[d1] >= req[d1] && freq[d2] >= req[d2] && freq[d3] >= req[d3])
            count++;
    }

    return count;
}