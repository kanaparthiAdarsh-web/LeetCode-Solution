/*
 * AnyPush — AI explanation
 * This solution employs a brute-force approach, iterating through all possible subarrays using nested loops (O(N^2)). For each subarray, we incrementally calculate its product, GCD, and LCM. The GCD is updated using the Euclidean algorithm, and LCM is updated using the property `lcm(A, B) = (A / gcd(A, B)) * B`. If the product equals `LCM * GCD`, we update the maximum length found. A crucial optimization is to break early if the subarray product exceeds 25200; given `nums[k] <= 10`, any valid subarray's product will be much smaller, preventing extensive processing of invalid, long subarrays.
 *
 * Time Complexity: O(N^2) due to nested loops. GCD and LCM updates are effectively constant time operations given `nums[k] <= 10`.
 * Space Complexity: O(1) for a few tracking variables.
 *
 * This N^2 approach is a good choice because the extremely small constraint on `nums[k]` (up to 10) makes GCD/LCM calculations very fast and allows for aggressive pruning via the product bound. A more complex approach involving prime factorizations would likely not offer significant performance benefits due to higher constant factors. Without the early product break, this N^2 solution would likely TLE on larger inputs due to extensive unnecessary calculations.
 */

static int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int maxLength(int* nums, int numsSize) {
    int ans = 0;

    for (int i = 0; i < numsSize; i++) {
        long long prod = 1;
        int g = nums[i];
        int l = nums[i];

        for (int j = i; j < numsSize; j++) {
            prod *= nums[j];
            g = gcd(g, nums[j]);
            l = (l / gcd(l, nums[j])) * nums[j];

            if (prod == (long long)l * g) {
                int len = j - i + 1;
                if (len > ans) 
                    ans = len;
            }
            if (prod > 25200)
                break;
        }
    }

    return ans;
}
