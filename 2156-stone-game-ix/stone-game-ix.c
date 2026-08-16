bool stoneGameIX(int* stones, int stonesSize) {
    int remin_0=0,remin_1=0,remin_2=0;
    for(int i=0;i<stonesSize;i++)
        if(stones[i]%3==0)
            remin_0++;
        else
            if(stones[i]%3==1)
                remin_1++;
        else
            remin_2++;
    if(remin_0%2)
        return(remin_1>remin_2?remin_1-remin_2:remin_2-remin_1)>2;
    else
        return remin_1>0 && remin_2>0;
}