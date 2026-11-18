/*
 * AnyPush — AI explanation
 * The core idea is a greedy approach. We iterate through the string, considering non-overlapping pairs of characters (s[0], s[1]), (s[2], s[3]), and so on. For each pair (s[i], s[i+1]), if the characters are different, it means one flip is required to make them identical. We simply count these instances. Each such problematic pair needs exactly one change, and these changes are independent across non-overlapping pairs, making this count globally optimal.
 *
 * Time complexity: O(N), as we iterate through the string linearly, performing constant work per pair.
 * Space complexity: O(1), using only a single integer variable for the count.
 *
 * This approach is highly efficient because the problem decomposes perfectly into independent subproblems for each pair. A greedy count is therefore globally optimal, avoiding the overhead of more complex algorithms like dynamic programming that would be unnecessary here.
 *
 * A potential improvement or note: The current solution implicitly assumes an even-length string. If the string could have an odd length, the last character (s[N-1]) would be ignored; handling this edge case explicitly might be needed depending on precise problem constraints.
 */

int minChanges(char* s) {
    int changes = 0;
    
    for (int i = 0; s[i] != '\0'; (s[i] != s[i + 1])?changes++:0,i += 2);
    
    return changes;
}
