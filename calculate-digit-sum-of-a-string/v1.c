/*
 * AnyPush — AI explanation
 * This solution directly simulates the problem's iterative process. In each step, it segments the current string into chunks of length `k`, calculates the sum of digits for each chunk, and concatenates these sums into a new string. This process repeats until the string's length is no longer greater than `k`. Dynamic memory is managed for new strings, ensuring sufficient space.
 *
 * Time Complexity: O(N) where N is the initial string length. Each character is processed a limited number of times across all iterations as the string length rapidly shrinks.
 * Space Complexity: O(N). We maintain two character buffers, each up to the initial string's maximum possible length.
 *
 * This approach is good because it's a straightforward simulation, easy to understand and implement, and efficiently handles the string length reduction without complex data structures. Its directness minimizes potential bugs for this problem type.
 *
 * A minor improvement could involve calculating the exact `next` string buffer size rather than using a heuristic like `currLen + 5`. A more naive approach might have used fixed-size buffers, risking potential overflows.
 */

char* digitSum(char* s, int k) {
    int len = strlen(s);
    char* curr = (char*)malloc((len + 5) * sizeof(char));
    strcpy(curr, s);

    while (strlen(curr) > k) {
        int currLen = strlen(curr);
        char* next = (char*)malloc((currLen + 5) * sizeof(char));
        int pos = 0;

        for (int i = 0; i < currLen; i += k) {
            int sum = 0;
            for (int j = i; j < i + k && j < currLen; j++) {
                sum += curr[j] - '0';
            }
            pos += sprintf(next + pos, "%d", sum);
        }

        free(curr);
        curr = next;
    }

    return curr;
}
