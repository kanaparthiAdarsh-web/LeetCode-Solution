static char ans[305];

char* lexPalindromicPermutation(char* s, char* target) {
    int n = strlen(s);
    int m = n / 2;
    int count[26] = {0};

    for (int i = 0; i < n; i++)
        count[s[i] - 'a']++;

    int odd_cnt = 0;
    int mid_char = -1;
    for (int i = 0; i < 26; i++)
        if (count[i] % 2 != 0) {
            odd_cnt++;
            mid_char = i;
        }

    if (odd_cnt > 1)
        return "";

    int half_count[26];
    for (int i = 0; i < 26;half_count[i] = count[i] / 2,i++);

    int temp_half[26];
    memcpy(temp_half, half_count, sizeof(half_count));
    int can_match = 1;

    for (int i = 0; i < m; i++) {
        int c = target[i] - 'a';
        if (temp_half[c] > 0)
            temp_half[c]--;
        else {
            can_match = 0;
            break;
        }
    }

    if (can_match) {
        for (int i = 0; i < m; i++) {
            ans[i] = target[i];
            ans[n - 1 - i] = target[i];
        }
        if (n % 2 != 0) 
            ans[m] = (char)('a' + mid_char);
        ans[n] = '\0';

        if (strcmp(ans, target) > 0)
            return ans;
    }

    for (int i = m - 1; i >= 0; i--) {
        memcpy(temp_half, half_count, sizeof(half_count));
        int valid_prefix = 1;

        for (int j = 0; j < i; j++) {
            int c = target[j] - 'a';
            if (temp_half[c] > 0)
                temp_half[c]--;
            else {
                valid_prefix = 0;
                break;
            }
        }

        if (!valid_prefix)
            continue;

        int next_c = -1;
        for (int c = target[i] - 'a' + 1; c < 26; c++)
            if (temp_half[c] > 0) {
                next_c = c;
                break;
            }

        if (next_c != -1) {
            for (int j = 0; j < i; j++) {
                ans[j] = target[j];
                ans[n - 1 - j] = target[j];
            }

            ans[i] = (char)('a' + next_c);
            ans[n - 1 - i] = (char)('a' + next_c);
            temp_half[next_c]--;

            int left_idx = i + 1;
            for (int c = 0; c < 26; c++) {
                while (temp_half[c] > 0) {
                    ans[left_idx] = (char)('a' + c);
                    ans[n - 1 - left_idx] = (char)('a' + c);
                    left_idx++;
                    temp_half[c]--;
                }
            }

            if (n % 2 != 0)
                ans[m] = (char)('a' + mid_char);
            ans[n] = '\0';
            return ans;
        }
    }

    return "";
}