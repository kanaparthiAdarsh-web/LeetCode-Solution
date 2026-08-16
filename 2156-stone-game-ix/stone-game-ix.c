bool stoneGameIX(int* stones, int stonesSize) {
    int remin_0=0,remin_1=0,remin_2=0;
    for(int i=0;i<stonesSize;(stones[i]%3==0) ? remin_0++ : (stones[i]%3==1)? remin_1++ : remin_2++,i++);
    return((remin_0%2) ? ((remin_1 > remin_2 ? remin_1-remin_2 : remin_2-remin_1)>2) : (remin_1 > 0 && remin_2 > 0));
}