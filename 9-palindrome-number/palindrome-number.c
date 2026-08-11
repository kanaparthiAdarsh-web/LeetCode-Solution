bool isPalindrome(int x) {
    long int pal=0;
    for(long int temp=x;temp>0;pal=pal*10+(temp%10),temp/=10);
    return((pal==x)? true:false);   
}