#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "desfunct.h"


/********************************************/
/* Tables for initial and final permutation */
/********************************************/

// initial mpermutation
char IP[64] = {
	58,	50,	42,	34,	26,	18,	10,	2,
	60,	52,	44,	36,	28,	20,	12,	4,
	62,	54,	46,	38,	30,	22,	14,	6,
	64,	56,	48,	40,	32,	24,	16,	8,
	57,	49,	41,	33,	25,	17,	9,	1,
	59,	51,	43,	35,	27,	19,	11,	3,
	61,	53,	45,	37,	29,	21,	13,	5,
	63,	55,	47,	39,	31,	23,	15,	7
};

//  half permutation
int HP[32] = {
	16,  7,  20, 21, 29, 12, 28, 17,	 
	 1, 15,  23, 26,  5, 18, 31, 10,
	 2,  8,  24, 14, 32, 27,  3,  9,
	19, 13,  30,  6, 22, 11,  4, 25
};

// final permutation
char FP[64] = {
	40,	8,	48,	16,	56,	24,	64,	32,
	39,	7,	47,	15,	55,	23,	63,	31,
	38,	6,	46,	14,	54,	22,	62,	30,
	37,	5,	45,	13,	53,	21,	61,	29,
	36,	4,	44,	12,	52,	20,	60,	28,
	35,	3,	43,	11,	51,	19,	59,	27,
	34,	2,	42,	10,	50,	18,	58,	26,
	33,	1,	41,	9,	49,	17,	57,	25
};

/*******************************/
/* Tables for the key schedule */
/*******************************/

// PC-1 table (initial key permutation)
int PC1[56] = {
	57,	49,	41,	33,	25,	17,	9,
	1,	58,	50,	42,	34,	26,	18,
	10,	2,	59,	51,	43,	35,	27,
	19,	11,	3,	60,	52,	44,	36,
	63,	55,	47,	39,	31,	23,	15,
	7,	62,	54,	46,	38,	30,	22,
	14,	6,	61,	53,	45,	37,	29,
	21,	13,	5,	28,	20,	12,	4
};

// PC-2 table (permutation for generating each subkey)
int PC2[48] = {
	14,	17,	11,	24,	1,	5,	3,	28,
	15,	6,	21,	10,	23,	19,	12,	4,
	26,	8,	16,	7,	27,	20,	13,	2,
	41,	52,	31,	37,	47,	55,	30,	40,
	51,	45,	33,	48,	44,	49,	39,	56,
	34,	53,	46,	42,	50,	36,	29,	32
};


/*********************************/
/* Tables for the round function */
/*********************************/

// expansion box
char E[48] = {
	32,	1,	2,	3,	4,	5,
	4,	5,	6,	7,	8,	9,
	8,	9,	10,	11,	12,	13,
	12,	13,	14,	15,	16,	17,
	16,	17,	18,	19,	20,	21,
	20,	21,	22,	23,	24,	25,
	24,	25,	26,	27,	28,	29,
	28,	29,	30,	31,	32,	1
};

// substitution boxes
// addressable using xxyyyy where xx are the first and last bits, and yyyy are the middle 4 bits
char S1[64] = {
	14,	4,	13,	1,	2,	15,	11,	8,	3,	10,	6,	12,	5,	9,	0,	7,
	0,	15,	7,	4,	14,	2,	13,	1,	10,	6,	12,	11,	9,	5,	3,	8,
	4,	1,	14,	8,	13,	6,	2,	11,	15,	12,	9,	7,	3,	10,	5,	0,
	15,	12,	8,	2,	4,	9,	1,	7,	5,	11,	3,	14,	10,	0,	6,	13
};

char S2[64] = {
	15,	1,	8,	14,	6,	11,	3,	4,	9,	7,	2,	13,	12,	0,	5,	10,
	3,	13,	4,	7,	15,	2,	8,	14,	12,	0,	1,	10,	6,	9,	11,	5,
	0,	14,	7,	11,	10,	4,	13,	1,	5,	8,	12,	6,	9,	3,	2,	15,
	13,	8,	10,	1,	3,	15,	4,	2,	11,	6,	7,	12,	0,	5,	14,	9
};

char S3[64] = {
	10,	0,	9,	14,	6,	3,	15,	5,	1,	13,	12,	7,	11,	4,	2,	8,
	13,	7,	0,	9,	3,	4,	6,	10,	2,	8,	5,	14,	12,	11,	15,	1,
	13,	6,	4,	9,	8,	15,	3,	0,	11,	1,	2,	12,	5,	10,	14,	7,
	1,	10,	13,	0,	6,	9,	8,	7,	4,	15,	14,	3,	11,	5,	2,	12
};

char S4[64] = {
	7,	13,	14,	3,	0,	6,	9,	10,	1,	2,	8,	5,	11,	12,	4,	15,
	13,	8,	11,	5,	6,	15,	0,	3,	4,	7,	2,	12,	1,	10,	14,	9,
	10,	6,	9,	0,	12,	11,	7,	13,	15,	1,	3,	14,	5,	2,	8,	4,
	3,	15,	0,	6,	10,	1,	13,	8,	9,	4,	5,	11,	12,	7,	2,	14
};

char S5[64]  = {
	2,	12,	4,	1,	7,	10,	11,	6,	8,	5,	3,	15,	13,	0,	14,	9,
	14,	11,	2,	12,	4,	7,	13,	1,	5,	0,	15,	10,	3,	9,	8,	6,
	4,	2,	1,	11,	10,	13,	7,	8,	15,	9,	12,	5,	6,	3,	0,	14,
	11,	8,	12,	7,	1,	14,	2,	13,	6,	15,	0,	9,	10,	4,	5,	3
};

char S6[64] = {
	12,	1,	10,	15,	9,	2,	6,	8,	0,	13,	3,	4,	14,	7,	5,	11,
	10,	15,	4,	2,	7,	12,	9,	5,	6,	1,	13,	14,	0,	11,	3,	8,
	9,	14,	15,	5,	2,	8,	12,	3,	7,	0,	4,	10,	1,	13,	11,	6,
	4,	3,	2,	12,	9,	5,	15,	10,	11,	14,	1,	7,	6,	0,	8,	13
};

char S7[64] = {
	4,	11,	2,	14,	15,	0,	8,	13,	3,	12,	9,	7,	5,	10,	6,	1,
	13,	0,	11,	7,	4,	9,	1,	10,	14,	3,	5,	12,	2,	15,	8,	6,
	1,	4,	11,	13,	12,	3,	7,	14,	10,	15,	6,	8,	0,	5,	9,	2,
	6,	11,	13,	8,	1,	4,	10,	7,	9,	5,	0,	15,	14,	2,	3,	12
};

char S8[64] = {
	13,	2,	8,	4,	6,	15,	11,	1,	10,	9,	3,	14,	5,	0,	12,	7,
	1,	15,	13,	8,	10,	3,	7,	4,	12,	5,	6,	11,	0,	14,	9,	2,
	7,	11,	4,	1,	9,	12,	14,	2,	0,	6,	10,	13,	15,	3,	5,	8,
	2,	1,	14,	7,	4,	10,	8,	13,	15,	12,	9,	0,	3,	5,	6,	11
};

char* SBOXMAP[] = {S1, S2, S3, S4, S5, S6, S7, S8};

//256 for unsigned 0-256 random characters 
void generator(unsigned char* key, unsigned char* iv) {
	
	for (int i=0; i<8; i++){ 
		key[i] = rand()%256;
		iv[i] = rand()%256;
	}
	
}//end generator();

/*
	Helpful links:
	http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
	https://en.wikipedia.org/wiki/Data_Encryption_Standard
	https://en.wikipedia.org/wiki/File:DES-key-schedule.png
	https://www.tutorialspoint.com/cryptography/data_encryption_standard.htm    

*/ 

void subkeyGenerator(subKey* subKeys, unsigned char* key){

    int i, j, size;
	unsigned char shift, firstBit, secondBit, thirdBit, fourthBit;
     
	for (i=0; i<8; i++) {
		subKeys[0].keyTemp[i] = 0;
	}
	
    //initial key permutation 
	for (i=0; i<56; i++) {
	
	   	//size must be subtracted because PC1 and PC2 are not index based, 
	    //assuming bits from 1-64 instead of 0 -63
		size = PC1[i];
		
		shift = 128 >> ((size - 1)%8);
		shift = shift & key[(size-1)/8];
		shift = shift << ((size-1)%8);

		subKeys[0].keyTemp[i/8] = subKeys[0].keyTemp[i/8] | (shift >> i%8);
		
	}//end initial key permutation 

	for (i=0; i<3; i++) {
		subKeys[0].t2[i] = subKeys[0].keyTemp[i];
		subKeys[0].t3[i] = (subKeys[0].keyTemp[i+3] & 15) << 4;
		subKeys[0].t3[i] = subKeys[0].t3[i] | (subKeys[0].keyTemp[i+4] & 240) >> 4;
	}

	subKeys[0].t2[3] = subKeys[0].keyTemp[3] & 240;
	subKeys[0].t3[3] = (subKeys[0].keyTemp[6] & 240) << 4;

	//16 create subkey loop
	for (i=0; i<16; i++){
	
		for (j=0; j<4; j++) {
			subKeys[i].t2[j] = subKeys[i-1].t2[j];
			subKeys[i].t3[j] = subKeys[i-1].t3[j];
		}
		
        int sizes[17] = {0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1};
		size = sizes[i];
		
		if (size == 1)
			shift = 128;
		else
			shift = 192;
		
        //subkey generation 
		firstBit = shift & subKeys[i].t2[0];
		secondBit = shift & subKeys[i].t2[1];
		thirdBit = shift & subKeys[i].t2[2];
		fourthBit = shift & subKeys[i].t2[3];

		
		subKeys[i].t2[0] = subKeys[i].t2[0] << size; 
		subKeys[i].t2[0] = subKeys[i].t2[0] | firstBit >> (8-size);

		subKeys[i].t2[1] = subKeys[i].t2[1] << size; 
		subKeys[i].t2[1] = subKeys[i].t2[1] | secondBit >> (8-size); 

		subKeys[i].t2[2] = subKeys[i].t2[2] << size; 
        subKeys[i].t2[2] = subKeys[i].t2[2] | thirdBit >> (8-size); 
		
		subKeys[i].t2[3] = subKeys[i].t2[3] << size; 
		subKeys[i].t2[3] = subKeys[i].t2[3] | fourthBit >> (8-size); 

		firstBit = shift & subKeys[i].t3[0];
		secondBit = shift & subKeys[i].t3[1];
		thirdBit = shift & subKeys[i].t3[2];
		fourthBit = shift & subKeys[i].t3[3];
	
		subKeys[i].t2[0] = subKeys[i].t2[0] << size; 	
        subKeys[i].t2[0] = subKeys[i].t2[0] | firstBit >> (8-size);
		
		subKeys[i].t2[1] = subKeys[i].t2[1] << size; 
        subKeys[i].t2[1] = subKeys[i].t2[1] | secondBit >> (8-size);
	
		subKeys[i].t2[2] = subKeys[i].t2[2] << size;
        subKeys[i].t2[2] = subKeys[i].t2[2] | thirdBit >> (8-size);
	
		subKeys[i].t2[3] = subKeys[i].t2[3] << size;	
		subKeys[i].t2[3] = subKeys[i].t2[3] | fourthBit >> (8-size); 

        //key permutation 
		for (j=0; j<48; j++) {
		
			size = PC2[j];
			if (size <= 28) {
				
				shift = 128 >> ((size-1)%8);
				shift = shift & subKeys[i].t2[(size-1)/8];
				shift = shift << ((size-1)%8);
			} else {
			
				shift = 128 >> ((size-29)%8);
				shift = shift & subKeys[i].t3[(size-29)/8];
				shift = shift << ((size-29)%8);
			}

			subKeys[i].keyTemp[j/8] = subKeys[i].keyTemp[j/8] | (shift >> j%8);
			
		}//end for 48 bit
	}

}//end subkeyGenerator();

void desFunction(subKey* subKeys, unsigned char* block, unsigned char* desBlock, int mode){

	int i, j;
	int size, keyIndex;
	unsigned char leftSplit[4], rightSplit[4], expansionTemp[6], sBoxTemp[4], leftTemp[4], rightTemp[4];
	unsigned char row, column, shift;
	unsigned char endPermTemp[8], initPermTemp[8];

	memset(initPermTemp, 0, 8);
	memset(desBlock, 0, 8);

	//size must be subtracted because sBoxes are not index based, 
	//assuming bits from 1-64 instead of 0 -63

    //initial permutation loop
	for (i=0; i<64; i++) {
		size = IP[i];
		
		shift = 128 >> ((size-1)%8);
		shift = shift & block[(size-1)/8];
		shift = shift << ((size-1)%8);

		initPermTemp[i/8] = initPermTemp[i/8] | (shift >> i%8);
	}//end init perm loop

    //left/right hand init perm
	for (i=0; i<4; i++) {
		leftTemp[i] = initPermTemp[i];
		rightTemp[i] = initPermTemp[i+4];
	}
	
    //des 16 round function
	for (j=1; j<=16; j++) {

		memcpy(leftSplit, rightTemp, 4);
		memset(expansionTemp, 0, 6);
        
        //decryption is 0
		if (mode == 0) {
			keyIndex = 17 - j;//reverses process for decryption
		} else {
			keyIndex = j;
		}

		//expansion box perm
		for (i=0; i<48; i++) {
			size = E[i];
			
			shift = 128 >> ((size-1)%8);
			shift = shift & rightTemp[(size-1)/8];
			shift = shift << ((size-1)%8);

			expansionTemp[i/8] = expansionTemp[i/8] | (shift >> i%8);
		}//end expansion box perm

        //xor and equal key 
		for (i=0; i<6; i++) {
			expansionTemp[i] = expansionTemp[i] ^ subKeys[keyIndex].keyTemp[i];
		}
        
        memset(sBoxTemp, 0, 4);
		
       /*
		Sbox xor permutation begin needs more documentation
       */

        //S1 box

		row = 0;
		
		row = row | ((expansionTemp[0] & 128) >> 6);
		
		row = row | ((expansionTemp[0] & 4) >> 2);

		column = 0;
		
		column = column | ((expansionTemp[0] & 120) >> 3);

      	sBoxTemp[0] = sBoxTemp[0] | ((unsigned char)S1[row*16+column] << 4);

        //S2 box
     
		row = 0;
		
		row = row | (expansionTemp[0] & 2);
		
		row = row | ((expansionTemp[1] & 16) >> 4);

		column = 0;
		
		column = column | ((expansionTemp[0] & 1) << 3);
		
		column = column | ((expansionTemp[1] & 224) >> 5);

		sBoxTemp[0] = sBoxTemp[0] | (unsigned char)S2[row*16+column];

		//S3 box
 
		row = 0;
		
		row = row | ((expansionTemp[1] & 8) >> 2);
		
		row = row | ((expansionTemp[2] & 64) >> 6);

		column = 0;
		
		column = column | ((expansionTemp[1] & 7) << 1);
		
		column = column | ((expansionTemp[2] & 128) >> 7);

		sBoxTemp[1] = sBoxTemp[1] | ((unsigned char)S3[row*16+column] << 4);

		//S4 box

		row = 0;
	
		row = row | ((expansionTemp[2] & 32) >> 4);
		
		row = row | (expansionTemp[2] & 1);

		column = 0;
		
		column = column | ((expansionTemp[2] & 30) >> 1);

		sBoxTemp[1] = sBoxTemp[1] | (unsigned char)S4[row*16+column];

		//S5 box
    
		row = 0;
		
		row = row | ((expansionTemp[3] & 128) >> 6); 
		
		row = row | ((expansionTemp[3] & 4) >> 2);

		column = 0;
		
		column = column | ((expansionTemp[3] & 120) >> 3);

		sBoxTemp[2] = sBoxTemp[2] | ((unsigned char)S5[row*16+column] << 4);

		//S6

		row = 0;
		
		row = row | (expansionTemp[3] & 2);
		
		row = row | ((expansionTemp[4] & 16) >> 4);

		column = 0;
		
		column = column | ((expansionTemp[3] & 1) << 3);
		
		column = column | ((expansionTemp[4] & 224) >> 5);

		sBoxTemp[2] = sBoxTemp[2] | (unsigned char)S6[row*16+column];

		//S7

		row = 0;
	
		row = row | ((expansionTemp[4] & 8) >> 2);
		
		row = row | ((expansionTemp[5] & 64) >> 6);

		column = 0;
		
		column = column | ((expansionTemp[4] & 7) << 1);
		
		column = column | ((expansionTemp[5] & 128) >> 7);

		sBoxTemp[3] = sBoxTemp[3] | ((unsigned char)S7[row*16+column] << 4);

		//S8

		row = 0;
		
		row = row | ((expansionTemp[5] & 32) >> 4);

		row = row | (expansionTemp[5] & 1);

		column = 0;
		
		column = column | ((expansionTemp[5] & 30) >> 1);

		sBoxTemp[3] = sBoxTemp[3] | (unsigned char)S8[row*16+column];

		/*
		   end Sbox xor permutation 
        */

        memset(rightSplit, 0, 4);
        //half perm rounds
		for (i=0; i<32; i++) {
		
			size = HP[i];
			
			shift = 128 >> ((size-1)%8);
			shift = shift & sBoxTemp[(size-1)/8];
			shift = shift << ((size-1)%8);

			rightSplit[i/8] = rightSplit[i/8] | (shift >> i%8);
		}

		for (i=0; i<4; i++) {
			rightSplit[i] = rightSplit[i] ^ leftTemp[i];
		}

		for (i=0; i<4; i++) {
			leftTemp[i] = leftSplit[i];
			rightTemp[i] = rightSplit[i];
		}
		
	}//end des rounds 
     
    //left/right hand  final perm
	for (i=0; i<4; i++) {
		endPermTemp[i] = rightTemp[i];
		endPermTemp[i+4] = leftTemp[i];
	}

    //final permutation 
	for (i=0; i<64; i++) {
		size = FP[i];
		
		shift = 128 >> ((size-1)%8);
		shift = shift & endPermTemp[(size - 1)/8];
		shift = shift << ((size-1)%8);

		desBlock[i/8] = desBlock[i/8] | (shift >> i%8);
	}


}//end desFunction();
