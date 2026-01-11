#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "Binary.h"

//Member function definition : 
Bin::Bin() {
    binary = (uchar*) malloc(sizeof(uchar)*num_bits);
    memset(binary, 0, sizeof(uchar)*num_bits);
}

Bin::Bin(int num) {
    binary = Dec2Bin(num);
}

Bin::Bin(const uchar* bin) {
    binary = (uchar*) malloc(sizeof(uchar)*num_bits);
    memcpy(binary, bin, sizeof(uchar)*num_bits);
}

Bin::Bin(const Bin& other) {
    binary = (uchar*)malloc(sizeof(uchar)*num_bits);
    memcpy(binary, other.binary, sizeof(uchar)*num_bits);
}

int Bin::Bin2Dec() {
    //Making new one 
    uchar* num = (uchar*)malloc(sizeof(uchar) * num_bits);
    if(!num) {
        fprintf(stderr, "Malloc on num fails with error code 6"); exit(6);
    }
    memcpy(num, binary, sizeof(uchar) * num_bits);

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

uchar* Bin::Dec2Bin(int num) {
    //Initial memory allocation
    uchar* bin = (uchar*)malloc(sizeof(uchar)*num_bits);
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

void Bin::PrintBinary() const {
    for(int i = 0; i<num_bits; i++) {
        if(i%4 == 0 && i != 0) printf(" ");
        printf("%d", binary[i]);
    }
}

Bin Bin::BinAdd(const Bin& bin2) const {
    Bin res;
    uchar* temp = res.binary;
    if(!temp) {
        fprintf(stderr, "Malloc on bin fails with error code 5"); exit(5);
    }

    const uchar *ptr1 = binary + num_bits - 1, *ptr2 = bin2.binary + num_bits - 1;
    uchar *ptr = temp + num_bits - 1; 
    uchar carry = 0; 

    //Without bin[0]
    for(; ptr != temp; /*Moving pointers*/ ptr1--, ptr2--, ptr--) {
        //Addition
        uchar sum = *ptr1 + *ptr2 + carry;
        *ptr = sum % 2;
        carry = sum / 2;
    }

    //Handling bin[0]
    uchar carry_bef = carry;
    0[temp] = (*ptr1 + *ptr2 + carry) % 2;
    uchar carry_aft = (*ptr1 + *ptr2 + carry) / 2;
    if(carry_bef != carry_aft) fprintf(stderr, "\nWarning : Overflow occurs in BinAdd()");
 
    return res;
}
