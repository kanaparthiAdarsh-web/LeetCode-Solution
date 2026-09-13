typedef struct {
    int r;
    int c;
} Point;

int largestOverlap(int** img1, int img1Size, int* img1ColSize, int** img2, int img2Size, int* img2ColSize) {
    int n = img1Size;
    
    Point pts1[900];
    Point pts2[900];
    int count1 = 0;
    int count2 = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (img1[i][j] == 1) {
                pts1[count1].r = i;
                pts1[count1].c = j;
                count1++;
            }
            if (img2[i][j] == 1) {
                pts2[count2].r = i;
                pts2[count2].c = j;
                count2++;
            }
        }
    }

    int shiftCounts[61][61] = {0};
    int maxOverlap = 0;

    for (int i = 0; i < count1; i++) {
        for (int j = 0; j < count2; j++) {
            int dr = pts2[j].r - pts1[i].r + n;
            int dc = pts2[j].c - pts1[i].c + n;

            shiftCounts[dr][dc]++;
            if (shiftCounts[dr][dc] > maxOverlap)
                maxOverlap = shiftCounts[dr][dc];
        }
    }

    return maxOverlap;
}