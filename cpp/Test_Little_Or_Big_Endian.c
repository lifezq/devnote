#include <stdlib.h>
#include <stdio.h>

union 
{
        int number;
        char s;

}test;

int testBigEndin()
{
        test.number=0x01000002;
        return (test.s==0x01);
}

int main()
{
        if (testBigEndin())     
            printf("big\n");
        else 
            printf("small\n");

    return 0;
}
