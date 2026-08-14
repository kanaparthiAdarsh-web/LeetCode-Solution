#define MAX(a,b) ((a)>(b)?(a):(b))
int maximumLengthSubstring(char* s) {
    int count[26]={0};
    int left=0,maxlength=0,len;
    len=strlen(s);
    for(int i=0;i<len;i++)
    {
        char currentchar=s[i];
        count[currentchar-'a']++;
        while(count[currentchar-'a']>2)
        {
            char leftchar=s[left];
            count[leftchar-'a']--;
            left++;
        }
        maxlength= MAX(maxlength,i-left+1);
    }    
    return maxlength;
}