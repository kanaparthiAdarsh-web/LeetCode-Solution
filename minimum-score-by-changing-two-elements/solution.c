/*
 * AnyPush — AI explanation
 * This solution begins by sorting the input array, which is crucial for identifying the smallest and largest elements efficiently. Once sorted, the problem of minimizing the score after changing two elements boils down to considering three key scenarios. These scenarios correspond to effectively "removing" two elements from consideration to minimize the (max - min) range: removing the two smallest, removing the two largest, or removing one smallest and one largest. We then simply calculate the range for each of these three cases and select the minimum.
 *
 * Time complexity is O(N log N) due to the sorting step, which dominates. Space complexity is O(log N) for the quicksort's recursion stack. This approach is a good choice because sorting makes the three optimal scenarios immediately apparent and easy to implement, ensuring correctness. While specialized selection algorithms could achieve an average O(N) time, they are significantly more complex to implement than a standard sort and offer diminishing returns for typical N in C competitive programming.
 */

int cmp(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

int minimizeSum(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), cmp);
    int ans = (nums[numsSize - 1] - nums[2]) < (nums[numsSize - 3] - nums[0]) ? (nums[numsSize - 1] - nums[2]) : (nums[numsSize - 3] - nums[0]);
    return ans < (nums[numsSize - 2] - nums[1]) ? ans : (nums[numsSize - 2] - nums[1]);
}
