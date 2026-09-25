#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

void parse(char* expr, int* idx, char*** result, int* size) {
    char** cur = NULL;
    int cur_size = 0, cur_cap = 0;
    char** group = NULL;
    int group_size = 0, group_cap = 0;
    
    while (expr[*idx] && expr[*idx] != '}') {
        if (expr[*idx] == '{') {
            (*idx)++;
            char** sub;
            int sub_size;
            parse(expr, idx, &sub, &sub_size);
            
            char** temp = NULL;
            int temp_size = 0, temp_cap = 0;
            if (cur_size == 0) {
                temp = sub;
                temp_size = sub_size;
                temp_cap = sub_size;
            } else {
                temp_cap = cur_size * sub_size + 10;
                temp = malloc(temp_cap * sizeof(char*));
                for (int i = 0; i < cur_size; i++) {
                    for (int j = 0; j < sub_size; j++) {
                        int len = strlen(cur[i]) + strlen(sub[j]) + 1;
                        temp[temp_size] = malloc(len);
                        sprintf(temp[temp_size], "%s%s", cur[i], sub[j]);
                        temp_size++;
                    }
                    free(cur[i]);
                }
                free(cur);
                for (int j = 0; j < sub_size; j++) {
                    free(sub[j]);
                }
                free(sub);
            }
            cur = temp;
            cur_size = temp_size;
            cur_cap = temp_cap;
        } else if (expr[*idx] >= 'a' && expr[*idx] <= 'z') {
            int start = *idx;
            while (expr[*idx] >= 'a' && expr[*idx] <= 'z') {
                (*idx)++;
            }
            int len = *idx - start;
            char* word = malloc(len + 1);
            strncpy(word, expr + start, len);
            word[len] = '\0';
            (*idx)--;
            
            char** temp = NULL;
            int temp_size = 0, temp_cap = 0;
            if (cur_size == 0) {
                temp_cap = 10;
                temp = malloc(temp_cap * sizeof(char*));
                temp[0] = word;
                temp_size = 1;
            } else {
                temp_cap = cur_size + 10;
                temp = malloc(temp_cap * sizeof(char*));
                for (int i = 0; i < cur_size; i++) {
                    int l = strlen(cur[i]) + strlen(word) + 1;
                    temp[i] = malloc(l);
                    sprintf(temp[i], "%s%s", cur[i], word);
                    free(cur[i]);
                }
                free(cur);
                free(word);
                temp_size = cur_size;
            }
            cur = temp;
            cur_size = temp_size;
            cur_cap = temp_cap;
        } else if (expr[*idx] == ',') {
            if (cur_size > 0) {
                if (group_size + cur_size >= group_cap) {
                    group_cap = group_cap == 0 ? cur_size + 10 : group_cap * 2 + cur_size;
                    group = realloc(group, group_cap * sizeof(char*));
                }
                for (int i = 0; i < cur_size; i++) {
                    group[group_size++] = cur[i];
                }
                free(cur);
                cur = NULL;
                cur_size = 0;
                cur_cap = 0;
            }
        }
        (*idx)++;
    }
    
    if (cur_size > 0) {
        if (group_size + cur_size >= group_cap) {
            group_cap = group_cap == 0 ? cur_size + 10 : group_cap * 2 + cur_size;
            group = realloc(group, group_cap * sizeof(char*));
        }
        for (int i = 0; i < cur_size; i++) {
            group[group_size++] = cur[i];
        }
        free(cur);
    }
    
    *result = group;
    *size = group_size;
}

char** braceExpansionII(char* expression, int* returnSize) {
    char* expr = malloc(strlen(expression) + 3);
    sprintf(expr, "{%s}", expression);
    int idx = 0;
    char** res = NULL;
    int size = 0;
    parse(expr, &idx, &res, &size);
    free(expr);
    
    int unique_size = 0;
    if (size > 0) {
        qsort(res, size, sizeof(char*), compare);
        for (int i = 0; i < size; i++) {
            if (unique_size == 0 || strcmp(res[i], res[unique_size - 1]) != 0) {
                res[unique_size++] = res[i];
            } else {
                free(res[i]);
            }
        }
    }
    *returnSize = unique_size;
    return res;
}