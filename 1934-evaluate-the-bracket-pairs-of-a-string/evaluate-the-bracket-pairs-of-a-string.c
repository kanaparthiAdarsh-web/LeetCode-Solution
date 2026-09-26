#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void* a, const void* b) {
    char** rowA = *(char***)a;
    char** rowB = *(char***)b;
    return strcmp(rowA[0], rowB[0]);
}

int cmpKey(const void* key, const void* element) {
    char* k = (char*)key;
    char** row = *(char***)element;
    return strcmp(k, row[0]);
}

char* evaluate(char* s, char*** knowledge, int knowledgeSize, int* knowledgeColSize) {
    qsort(knowledge, knowledgeSize, sizeof(char**), cmp);
    
    int len = strlen(s);
    int resCap = len + 100;
    char* res = malloc(resCap);
    int resLen = 0;
    
    int i = 0;
    while (i < len) {
        if (s[i] == '(') {
            int start = ++i;
            while (s[i] != ')') {
                i++;
            }
            int keyLen = i - start;
            char* key = malloc(keyLen + 1);
            strncpy(key, s + start, keyLen);
            key[keyLen] = '\0';
            
            char*** found = bsearch(key, knowledge, knowledgeSize, sizeof(char**), cmpKey);
            char* val = "?";
            if (found != NULL) {
                val = (*found)[1];
            }
            
            int valLen = strlen(val);
            if (resLen + valLen >= resCap) {
                resCap = resLen + valLen + 100;
                res = realloc(res, resCap);
            }
            strcpy(res + resLen, val);
            resLen += valLen;
            
            free(key);
            i++;
        } else {
            if (resLen + 1 >= resCap) {
                resCap += 100;
                res = realloc(res, resCap);
            }
            res[resLen++] = s[i++];
        }
    }
    res[resLen] = '\0';
    return res;
}