int* nodesBetweenCriticalPoints(struct ListNode* head, int* returnSize) {
    *returnSize = 2;
    int* result = (int*)malloc(sizeof(int) * 2);
    result[0] = result[1] = -1;

    if (!head || !head->next || !head->next->next)
        return result;

    int firstIdx = -1;
    int prevIdx = -1;
    int minDistance = 1000000;

    struct ListNode* prev = head;
    struct ListNode* curr = head->next;
    int currIdx = 2;

    while (curr && curr->next) {
        if ((curr->val > prev->val && curr->val > curr->next->val) ||
            (curr->val < prev->val && curr->val < curr->next->val)) {
            
            if (firstIdx == -1)
                firstIdx = currIdx;
            else
                if (currIdx - prevIdx < minDistance)
                    minDistance = currIdx - prevIdx;

            prevIdx = currIdx;
        }

        prev = curr;
        curr = curr->next;
        currIdx++;
    }

    if (firstIdx != -1 && prevIdx != firstIdx) {
        result[0] = minDistance;
        result[1] = prevIdx - firstIdx;
    }

    return result;
}