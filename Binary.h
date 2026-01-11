#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned int uint;
typedef unsigned char uchar;    //For 1 byte representation (just need 1 and 0)

using namespace std; 
inline uint num_bits;

class Bin {
    private : 
        uchar* binary;
    public : 
        //Constructors
        Bin();                  //Default constructor
        Bin(int num);
        Bin(const uchar* bin);
        Bin(const Bin& other);   //copy constructor for Bin
        
        //Accessor and Mutators
        int Bin2Dec();
        void PrintBinary() const;
        uchar* Dec2Bin(int num);
        Bin BinAdd(const Bin&) const;
        const uchar* GetBinary() const {return binary;};

        Bin operator+(const Bin& rhs) const {
            return BinAdd(rhs);
        }

        Bin& operator=(const Bin& rhs) {
            if(this != &rhs) {
                free(binary);

                binary = (uchar*) malloc(sizeof(uchar)*num_bits);
                if(!binary) {
                    fprintf(stderr, "Malloc fail in assignment operator =\nExit with code 10");
                    exit(10);
                }
                memcpy(binary, rhs.binary, sizeof(uchar)*num_bits);
                
            } 
            return *this;
        }

        ~Bin() {free(binary);}
};