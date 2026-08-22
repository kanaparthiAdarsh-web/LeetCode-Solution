bool checkDivisibility(int n) {
    int temp=n,digits,sum=0,product=1;
    while(temp>0)
    {
        digits=temp%10;
        temp/=10;
        sum+=digits;
        product*=digits;
    }
    return((n%(sum+product))? false : true);
}