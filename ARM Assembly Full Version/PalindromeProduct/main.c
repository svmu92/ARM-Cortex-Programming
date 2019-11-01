#include <stdio.h>
#include <stdlib.h>


unsigned long long checkPalindrome(unsigned long long);
int main()
{
    int start=999,next=999,found=0;
    unsigned long long product,greatest;
    greatest = start;
    while(start>99)
    {
        next=start;
        while(next>99)
        {
            if((start%11==0)||(next%11==0))
            {
              product = start * next;
                if (checkPalindrome(product)> greatest)
                {
                    greatest = product;
                }
            }
            next--;
        }
        start--;
    }

    printf("Greatest product is %I64u and start= %u and next = %u\n",greatest,start,next);
    return 0;
}

unsigned long long checkPalindrome(unsigned long long value)
{
    unsigned long long sum,ans,temp;
    temp=value;
    sum=0;
    while(value > 0)
    {
        ans=value%10;
        sum=(sum*10)+ans;
        value=value/10;
    }

    if(sum==temp)
        return temp;
    else
        return 0;
}
