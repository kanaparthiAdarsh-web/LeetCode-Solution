#include <string.h>

static char ans[305];

char* lexGreaterPermutation(char* s, char* target) {
    int n = strlen(s);
    int count[26] = {0};

    for (int i = 0; i < n;count[s[i] - 'a']++,i++);

    int match_len = 0;
    int temp_count[26];
    memcpy(temp_count, count, sizeof(count));

    while (match_len < n && temp_count[target[match_len] - 'a'] > 0) {
        temp_count[target[match_len] - 'a']--;
        match_len++;
    }

    for (int i = match_len; i >= 0; i--) {
        memcpy(temp_count, count, sizeof(count));
        for (int j = 0; j < i; temp_count[target[j] - 'a']--, j++);

        int next_char = -1;
        if (i < n)
            for (int c = target[i] - 'a' + 1; c < 26; c++)
                if (temp_count[c] > 0) {
                    next_char = c;
                    break;
                }


        if (next_char != -1) {
            for (int j = 0; j < i; ans[j] = target[j],j++);
            ans[i] = (char)('a' + next_char);
            temp_count[next_char]--;

            int idx = i + 1;
            for (int c = 0; c < 26; c++)
                while (temp_count[c] > 0) {
                    ans[idx++] = (char)('a' + c);
                    temp_count[c]--;
                }
            ans[n] = '\0';
            return ans;
        }
    }

    return "";
}