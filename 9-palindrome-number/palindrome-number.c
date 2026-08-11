bool isPalindrome(int x) {
    long int temp,d,pal=0;
    temp=x;
    while(temp>0)
    {
        d=temp%10;
        pal=pal*10+d;
        temp/=10;
    }
    if(pal==x)
        return true;
    else
        return false;    
}