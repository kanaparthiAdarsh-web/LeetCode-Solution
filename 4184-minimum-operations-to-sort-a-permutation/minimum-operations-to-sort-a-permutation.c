int minOperations(int* nums, int numsSize) {
    int n = numsSize;
    int pos0 = 0;
    for (int i = 0; i < n; i++)
        if (nums[i] == 0) {
            pos0 = i;
            break;
        }

    int asc = 1, desc = 1;
    for (int i = 0; i < n; i++) {
        int v = nums[(pos0 + i) % n];
        if (v != i) 
            asc = 0;
        if (v != (n - i) % n) 
            desc = 0;
    }

    if (!asc && !desc) 
        return -1;

    int ans = 1000000000;

    if (asc) {
        if (pos0 == 0) 
            return 0;
        int a = pos0;
        int b = n - pos0 + 2;
        ans = a < b ? a : b;
    }

    if (desc) {
        int a = n - pos0;
        int b = (pos0 + 1) % n + 1;
        int c = a < b ? a : b;
        if (c < ans) 
            ans = c;
    }

    return ans;
}