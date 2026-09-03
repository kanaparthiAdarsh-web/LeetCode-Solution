#include <stdbool.h>

bool uniformArray(int* nums1, int nums1Size) {
    int minVal = nums1[0];
    int hasOdd = 0;

    for (int i = 0; i < nums1Size; i++) {
        if (nums1[i] < minVal)
            minVal = nums1[i];
        if (nums1[i] % 2 != 0)
            hasOdd = 1;
    }

    if (!hasOdd || minVal % 2 != 0)
        return true;

    return false;
}