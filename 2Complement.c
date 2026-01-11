#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef unsigned int uint;
typedef unsigned char uchar;    //For 1 byte representation (just need 1 and 0)

uint num_bits;

int Bin2Dec(const uchar* num);
void PrintBinary(uchar* bin);
uchar* Dec2Bin(int num);
uchar* BinAdd(const uchar*, const uchar*);

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

    uchar* bin1 = Dec2Bin(num1);
    uchar* bin2 = Dec2Bin(num2);

    printf("\nBinary 1 = "); PrintBinary(bin1);
    printf("\nBinary 2 = "); PrintBinary(bin2); printf("\n\n");

    //Proceed to addition 
    uchar* bin = BinAdd(bin1, bin2);
    printf("\n");
    PrintBinary(bin1); printf(" + "); PrintBinary(bin2); printf(" = "); PrintBinary(bin); printf("\n");

    int num = Bin2Dec(bin);
    printf("%d + %d = %d", num1, num2, num);


    free(bin1);
    free(bin2);
    free(bin);
}

int Bin2Dec(const uchar num_ptr[]) {
    //Making new one 
    uchar* num = malloc(sizeof(uchar) * num_bits);
    if(!num) {
        fprintf(stderr, "Malloc on num fails with error code 6"); exit(6);
    }
    memcpy(num, num_ptr, sizeof(uchar) * num_bits);

    if(num[0] == 1) {   //Negative
        //Performing conversion using bit flip:
        int first1 = 0; //False
        int index = num_bits - 1;
        
        //Before first1 becoming true, bit flip not happening
        while(!first1 && index > 0) {
            if(num[index] == 1) first1 = 1;
            else if (num[index] != 0) {
                fprintf(stderr, "Error : Binary must always be 0 and 1. \nLocation in Bin2Dec() function with error code 3\n\n");
                exit(3);
            } 
            index--; 
        }

        //Condition where first1 = 1, perform bit flip 
        while(index > 0) {
            if(num[index] == 1 || num[index] == 0) num[index] ^= 1;
            else {
                fprintf(stderr, "Error : Binary must always be 0 and 1. \nLocation in Bin2Dec() function with error code 1\n\n");
                exit(1);
            } 

            index--;
        }

        int sum = 0; 
        int multiplier = 1; 

        for(int i = num_bits - 1; i>0; i--, multiplier *= 2) sum += num[i] * multiplier;

        if(sum == 0) sum += num[0] * multiplier;    //Special case

        return sum*-1;
    }
    else if (num[0] == 0) {
        int sum = 0; 
        int multiplier = 1; 

        for(int i = num_bits - 1; i>0; i--, multiplier *= 2) sum += num[i] * multiplier;

        return sum;
    }
    else {
        fprintf(stderr, "Error : Binary must always be 0 and 1. \nLocation in Bin2Dec() function with error code 2\n\n");
        exit(2);
    } 
}

uchar* Dec2Bin(int num) {
    //Initial memory allocation
    uchar* bin = malloc(sizeof(uchar)*num_bits);
    if(!bin) {
        fprintf(stderr, "Malloc on bin fails with error code 7"); exit(7);
    }

    if(num > 0 && num < (1U << (num_bits-1))) {
        for(int i = num_bits - 1; i > 0; i--, num /= 2) bin[i] = num%2;

        //Handling the sign bit : 
        bin[0] = 0;
    }
    else if (num < 0 && num >= -(1 << (num_bits-1))) {
        int first1 = 0;
        int index = num_bits - 1; 
        int absnum = -num;

        //When first one is not found
        while(!first1 && index > 0) {
            bin[index] = absnum%2;
            if(bin[index]) first1 = 1;
            absnum /= 2;
            index--;
        }

        //Great news, now first one has been found, proceeding to bit flipping 
        for(int i = index; i>0; i--, absnum /= 2) bin[i] = !(absnum%2);

        bin[0] = 1;
    }
    else if (num == 0) {
        for(int i = 0; i<num_bits; i++) bin[i] = 0;
    }
    else {
        fprintf(stderr, "Error : Out of possible bound, will cause overflow. \nLocation in Dec2Bin() function with error code 4 for %d\n\n", num);
        exit(4);
    }

    return bin;
}

void PrintBinary(uchar* bin) {
    for(int i = 0; i<num_bits; i++) {
        if(i%4 == 0 && i != 0) printf(" ");
        printf("%d", bin[i]);
    } 
}

uchar* BinAdd(const uchar* bin1, const uchar* bin2) {
    uchar* bin = malloc(sizeof(uchar)*num_bits);
    if(!bin) {
        fprintf(stderr, "Malloc on bin fails with error code 5"); exit(5);
    }

    const uchar *ptr1 = bin1 + num_bits - 1, *ptr2 = bin2 + num_bits - 1;
    uchar *ptr = bin + num_bits - 1; 
    uchar carry = 0; 

    //Without bin[0]
    for(; ptr != bin; /*Moving pointers*/ ptr1--, ptr2--, ptr--) {
        //Addition
        uchar sum = *ptr1 + *ptr2 + carry;
        *ptr = sum % 2;
        carry = sum / 2;
    }

    //Handling bin[0]
    uchar carry_bef = carry;
    0[bin] = (*ptr1 + *ptr2 + carry) % 2;
    uchar carry_aft = (*ptr1 + *ptr2 + carry) / 2;
    if(carry_bef != carry_aft) fprintf(stderr, "\nWarning : Overflow occurs in BinAdd()");

    return bin;
}