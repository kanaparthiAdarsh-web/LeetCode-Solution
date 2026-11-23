/*
 * AnyPush — AI explanation
 * This solution uses a prefix product array to efficiently calculate the product of the last K numbers. Each `prefix[i]` stores the product of all numbers added up to index `i-1`. A key aspect is handling zeros: when a zero is added, the prefix array is effectively reset from that point, as any product including zero becomes zero, preventing issues with division by zero and correctly representing products.
 *
 * Both `add` and `getProduct` operations achieve O(1) average time complexity, thanks to direct array access and basic arithmetic. Space complexity is O(N), storing up to N prefix products.
 *
 * This approach is highly efficient for numerous `getProduct` queries, trading O(N) space for constant-time retrievals. A naive method of storing all numbers and recomputing products would incur O(K) time per query, which would be too slow. While the fixed-size array is typical for competitive programming, a dynamically resizing array would offer better memory efficiency for varying input sizes.
 */

typedef struct {
    int* prefix;
    int size;
} ProductOfNumbers;

ProductOfNumbers* productOfNumbersCreate() {
    ProductOfNumbers* obj = (ProductOfNumbers*)malloc(sizeof(ProductOfNumbers));
    obj->prefix = (int*)malloc(40005 * sizeof(int));
    obj->prefix[0] = 1;
    obj->size = 1;
    return obj;
}

void productOfNumbersAdd(ProductOfNumbers* obj, int num) {
    if (num == 0) {
        obj->size = 1;
    } else {
        obj->prefix[obj->size] = obj->prefix[obj->size - 1] * num;
        obj->size++;
    }
}

int productOfNumbersGetProduct(ProductOfNumbers* obj, int k) {
    if (k >= obj->size) {
        return 0;
    }
    return obj->prefix[obj->size - 1] / obj->prefix[obj->size - 1 - k];
}

void productOfNumbersFree(ProductOfNumbers* obj) {
    free(obj->prefix);
    free(obj);
}
