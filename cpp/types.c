#include <stdio.h>
#include <stdlib.h>

int main(){

    //printf("         bool: %d bits\n", (int)sizeof(bool));
    printf("           char: %d bits\n", (int)sizeof(char));
    printf("          short: %d bits\n", (int)sizeof(short));
    printf("unsigned  short: %d bits\n", (int)sizeof(unsigned short));
    printf("            int: %d bits\n", (int)sizeof(int));
    printf("unsigned    int: %d bits\n", (int)sizeof(unsigned int));
    printf("           long: %d bits\n", (int)sizeof(long));
    printf("unsigned   long: %d bits\n", (int)sizeof(unsigned long));
    printf("          float: %d bits\n", (int)sizeof(float));
    printf("         double: %d bits\n", (int)sizeof(double));

    return 0;
}

