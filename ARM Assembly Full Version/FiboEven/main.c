#include <stdio.h>
#include <stdlib.h>

int main()
{
    //unsigned int ar[100];
    unsigned int sum=0;
    unsigned int temp,first=0,second=1;

    while(second<4000000)
    {
        temp=second;
        second=second+first;
        first=temp;

        if(second%2==0)
            sum+=second;

    }

    printf("Sum : %d", sum);
    return 0;
}
