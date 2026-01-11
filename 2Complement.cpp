#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#include "Binary.h"


//Main function 
int main(int argc, char** argv) {
    if(argc < 3 || argc > 4) {
        fprintf(stderr, "Error : Must have 4 arguments : main <value1> <value2> [num_bits]\n");
        fprintf(stderr, "Number of bits default to 8 if omitted \n\nExit with code 7");
        exit(7);
    }

    if(argc == 3) num_bits = 8;
    else {
        char* end; 
        num_bits = strtoul(argv[3], &end, 10);
        if(*end != '\0') {
            fprintf(stderr, "Error: num_bits must be an integer.\nExit with code 8");
            exit(8);
        }

        if(num_bits < 2 || num_bits > 32) {
            fprintf(stderr, "Error: Unrealistic number of bits. Must be between 2 and 32 (inclusive) as one bit is reserved for sign\nExit with code 9");
            exit(9);
        }
    }
    
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    printf("Num 1 = %i\n", num1);
    printf("Num 2 = %i\n", num2);

    Bin bin1(num1);
    Bin bin2(num2);

    printf("\nBinary 1 = "); bin1.PrintBinary();
    printf("\nBinary 2 = "); bin2.PrintBinary(); printf("\n\n");

    //Proceed to addition 
    Bin bin = bin1 + bin2;
    printf("\n");
    bin1.PrintBinary(); printf(" + "); bin2.PrintBinary(); printf(" = "); bin.PrintBinary(); printf("\n");
    printf("%d + %d = %d\n", num1, num2, bin.Bin2Dec());
}