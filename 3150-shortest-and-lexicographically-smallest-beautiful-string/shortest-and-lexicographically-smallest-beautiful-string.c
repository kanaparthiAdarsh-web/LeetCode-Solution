static char res[105];

char* shortestBeautifulSubstring(char* s, int k) {
    int n = strlen(s), min_len = 105, best = -1, cnt = 0, l = 0;

    for (int r = 0; r < n; r++) {
        cnt += (s[r] == '1');

        while (cnt == k) {
            while (s[l] == '0') l++;

            int len = r - l + 1;
            if (len < min_len || (len == min_len && strncmp(s + l, s + best, len) < 0)) {
                min_len = len;
                best = l;
            }
            cnt -= (s[l++] == '1');
        }
    }

    if (best == -1) return "";

    strncpy(res, s + best, min_len);
    res[min_len] = '\0';
    return res;
}