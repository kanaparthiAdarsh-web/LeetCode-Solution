#include <string.h>
#include <limits.h>

int myAtoi(char* s) {
    int i = 0;
    long long num = 0;
    int sign = 1;
    
    while (s[i] == ' ')
        i++;
    if (s[i] == '-')
    {
        sign = -1;
        i++;
    }
    else 
        if (s[i] == '+')
            i++;
    while (s[i] >= '0' && s[i] <= '9')
    {
        int digit = s[i] - '0';
        
        if (num > (INT_MAX - digit) / 10)
            return (sign == 1) ? INT_MAX : INT_MIN;
        num = num * 10 + digit;
        i++;
    }
    
    return (int)(num * sign);
}