#include <stdio.h>
#include <stdlib.h>

 long long checkprime(long long n);
int main()
{
     long long div=1;
     long long num = 600851475143;
     long long greatest=1;
    while(div<=num)
    {
        if(num%div==0)              //check whether div is a factor of num
        {
            if(checkprime(div)> greatest) //check whether div is prime and whether that is greater than greatest
            {
                greatest=div;
            }
        }
        div++;
    }
    printf("Greatest prime factor is %I64d \n",greatest);
    return 0;
}

 long long checkprime( long long value)
{
     long long i;
    for(i=2;i<=value/2;i++)
    {
        if(value%i==0)
            return 0;
    }
    return value;
}
