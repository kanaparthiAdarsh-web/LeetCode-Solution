typedef struct {
    int val,digitSum,index;
} Element;

int getDigitSum(int n) {
    int sum = 0;
    while (n > 0){
        sum += n % 10;
        n/=10;
    }
    return sum;
}

int compare(const void* a, const void* b) {
    Element* e1 = (Element*)a;
    Element* e2 = (Element*)b;
    if (e1->digitSum != e2->digitSum)
        return e1->digitSum - e2->digitSum;
    return e1->val - e2->val;
}

int minSwaps(int* nums, int numsSize) {
    Element* arr = (Element*)malloc(numsSize * sizeof(Element));
    for (int i = 0; i < numsSize; i++) {
        arr[i].val = nums[i];
        arr[i].digitSum = getDigitSum(nums[i]);
        arr[i].index = i;
    }
    
    qsort(arr, numsSize, sizeof(Element), compare);
    
    int* visited = (int*)calloc(numsSize, sizeof(int));
    int swaps = 0;
    
    for (int i = 0; i < numsSize; i++) {
        if (visited[i] || arr[i].index == i)
            continue;
        
        int cycle_size = 0;
        int j = i;
        while (!visited[j]) {
            visited[j] = 1;
            j = arr[j].index;
            cycle_size++;
        }
        
        if (cycle_size > 0) 
            swaps += (cycle_size - 1);
    }
    
    free(arr);
    free(visited);
    return swaps;
}