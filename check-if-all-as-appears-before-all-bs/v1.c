/*
 * AnyPush — AI explanation
 * This solution iterates through the string in a single pass, tracking whether a 'b' has been encountered yet. It uses a `seenB` flag; once set to true, any subsequent 'a' character immediately violates the condition, and we can return false. If the loop completes without an 'a' appearing after a 'b', the string is valid.
 *
 * Time Complexity: O(N), as it processes each character of the input string once.
 * Space Complexity: O(1), using only a single boolean flag for state tracking.
 *
 * This approach is highly efficient and optimal because it determines the validity in a single linear scan with constant extra space, directly implementing the problem's condition without needing to store intermediate results or perform multiple passes.
 *
 * A more naive approach might involve finding the index of the first 'b' and the last 'a' (if they exist) and comparing them, which, while also O(N) in time, could require two passes or slightly more complex logic than this direct state-based check.
 */

bool checkString(char* s) {
    bool seenB = false;
    
    for (int i = 0; s[i]; i++)
        if (s[i] == 'b')
            seenB = true;
        else 
            if (seenB)
                return false;
    
    return true;
}
