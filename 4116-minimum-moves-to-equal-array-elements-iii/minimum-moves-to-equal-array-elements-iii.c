int minMoves(int* nums, int numsSize) {
    int max_val=*nums;
    int sum=0;
    for(int i=0;i<numsSize;sum+=*(nums+i),i++)
        if(*(nums+i)>max_val)
            max_val=*(nums+i);
    
    return max_val*numsSize-sum;
    
}