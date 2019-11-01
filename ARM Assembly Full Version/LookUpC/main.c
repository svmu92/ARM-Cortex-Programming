#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
    int i;
    int index=0;
    float j[92];
    float sin_value;
    FILE *FP;

    if((FP=fopen("sindata.txt","w"))== NULL)
    {
        printf("File could not be opened for writing\n");
        exit(1);
    }

    for(i=0;i<=90;i++)
    {
        sin_value = sin(i*M_PI/180.0);
        j[i]=sin_value;
    }

    for(i=1;i<23;i++)
    {
        fprintf(FP,"DCD\t");
        fprintf(FP,"%f,",j[index]);
        fprintf(FP,"%f,",j[index+1]);
        fprintf(FP,"%f,",j[index+2]);
        fprintf(FP,"%f",j[index+3]);
        fprintf(FP,"\n");
        index+=4;
    }
    fclose(FP);
    return 0;
}
