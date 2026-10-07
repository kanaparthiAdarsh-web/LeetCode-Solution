#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isValid(char* s) {
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') count++;
        else if (s[i] == ')') {
            count--;
            if (count < 0) return false;
        }
    }
    return count == 0;
}

typedef struct Node {
    char* str;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

void enqueue(Queue* q, char* str) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->str = strdup(str);
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

char* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    Node* temp = q->front;
    char* str = temp->str;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    q->size--;
    return str;
}

typedef struct HashNode {
    char* str;
    struct HashNode* next;
} HashNode;

#define HASH_SIZE 10007

unsigned int hash(char* str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_SIZE;
}

bool contains(HashNode* table[], char* str) {
    unsigned int h = hash(str);
    HashNode* curr = table[h];
    while (curr) {
        if (strcmp(curr->str, str) == 0) return true;
        curr = curr->next;
    }
    return false;
}

void insert(HashNode* table[], char* str) {
    if (contains(table, str)) return;
    unsigned int h = hash(str);
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->str = strdup(str);
    newNode->next = table[h];
    table[h] = newNode;
}

char** removeInvalidParentheses(char* s, int* returnSize) {
    *returnSize = 0;
    HashNode* visited[HASH_SIZE] = {NULL};
    HashNode* addedToResult[HASH_SIZE] = {NULL};
    
    Queue* q = createQueue();
    enqueue(q, s);
    insert(visited, s);
    
    char** res = NULL;
    int resCapacity = 10;
    res = (char**)malloc(resCapacity * sizeof(char*));
    
    while (q->size > 0) {
        int levelSize = q->size;
        bool levelFound = false;
        
        for (int i = 0; i < levelSize; i++) {
            char* curr = dequeue(q);
            
            if (isValid(curr)) {
                if (!contains(addedToResult, curr)) {
                    insert(addedToResult, curr);
                    if (*returnSize >= resCapacity) {
                        resCapacity *= 2;
                        res = (char**)realloc(res, resCapacity * sizeof(char*));
                    }
                    res[(*returnSize)++] = strdup(curr);
                }
                levelFound = true;
            }
            
            if (!levelFound) {
                int len = strlen(curr);
                for (int j = 0; j < len; j++) {
                    if (curr[j] != '(' && curr[j] != ')') continue;
                    
                    char* nextStr = (char*)malloc(len);
                    strncpy(nextStr, curr, j);
                    strcpy(nextStr + j, curr + j + 1);
                    
                    if (!contains(visited, nextStr)) {
                        insert(visited, nextStr);
                        enqueue(q, nextStr);
                    }
                    free(nextStr);
                }
            }
            free(curr);
        }
        if (levelFound) break;
    }
    
    return res;
}