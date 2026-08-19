int compare(const void* a, const void* b) {
    int* rowA = *(int**)a;
    int* rowB = *(int**)b;
    if (rowA[0] < rowB[0]) return -1;
    if (rowA[0] > rowB[0]) return 1;
    return rowA[1] - rowB[1];
}

int maxNumberOfFamilies(int n, int** reservedSeats, int reservedSeatsSize, int* reservedSeatsColSize) {
    if (reservedSeatsSize == 0) {
        return n * 2;
    }
    
    qsort(reservedSeats, reservedSeatsSize, sizeof(int*), compare);
    
    int distinct_rows = 0;
    int ans = 0;
    int i = 0;
    
    while (i < reservedSeatsSize) {
        int r = reservedSeats[i][0];
        int mask = 0;
        
        while (i < reservedSeatsSize && reservedSeats[i][0] == r) {
            mask |= (1 << reservedSeats[i][1]);
            i++;
        }
        
        distinct_rows++;
        
        int left = !(mask & 60);
        int right = !(mask & 960);
        int middle = !(mask & 240);
        
        if (left && right) {
            ans += 2;
        } else if (left || right || middle) {
            ans += 1;
        }
    }
    
    ans += (n - distinct_rows) * 2;
    return ans;
}