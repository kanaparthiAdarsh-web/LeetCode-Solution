#include<stdio.h>
#include<string.h>
char* longestCommonPrefix(char** strs, int strsSize) {
if(strsSize==0)
    return "";
int *temp,i,j,small_length,small,count=0,match=1;
temp=malloc(sizeof(int)*strsSize);
for(i=0;i<=strsSize-1;i++)
    temp[i]=strlen(strs[i]);
small_length=temp[0];
small=0;
for(i=1;i<strsSize;i++)
    if(temp[i]<small_length)
    {
        small_length=temp[i];
        small=i;
    }
char *temp1=malloc(sizeof(char)*(small_length+1));
temp1[0]='\0';
for(i=0;i<small_length;i++)
{
    match=1;
    for(j=0;j<strsSize;j++)
        if(strs[j][i]!=strs[small][i])
        {
            match=0;
            break;
        }
    if(match)
    {
        temp1[count]=strs[small][i];
        count++;
    }
    else
        break;
}
temp1[count]='\0';
    return temp1;
}