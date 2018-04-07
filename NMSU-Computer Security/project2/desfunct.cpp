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

int HP[] = {
	16,     7,      20,     21,     29,     12,     28,     17,	 
	 1,    15, 	23, 	26,	 5, 	18, 	31, 	10,
	 2,  	8, 	24, 	14, 	32, 	27,  	 3,  	 9,
	19,    13, 	30,  	 6, 	22, 	11,  	 4, 	25
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

void keyGenerator(unsigned char* key) {
	
	int i;
	for (i=0; i<8; i++){ 
		key[i] = rand()%255;
	}
}//end keyGenerate();

void ivGenerator(unsigned char* iv){
	int i;
	for (i=0; i<8; i++){ 
		iv[i] = rand()%255;
	}

}//end IVGenerator();

void subkeyGenerator(unsigned char* mainKey, keySet* keySets){
   int i, j;
	int shiftSize;
	unsigned char shiftByte, firstShiftBits, secondShiftBits, thirdShiftBits, fourthShiftBits;

	for (i=0; i<8; i++) {
		keySets[0].k[i] = 0;
	}

	for (i=0; i<56; i++) {
		shiftSize = PC1[i];
		//changed hex 0x80 to 128
		shiftByte = 128 >> ((shiftSize - 1)%8);
		shiftByte &= mainKey[(shiftSize - 1)/8];
		shiftByte <<= ((shiftSize - 1)%8);

		keySets[0].k[i/8] |= (shiftByte >> i%8);
	}

	for (i=0; i<3; i++) {
		keySets[0].c[i] = keySets[0].k[i];
	}

	//changed hex 0xf0 to 240
	keySets[0].c[3] = keySets[0].k[3] & 240;

	for (i=0; i<3; i++) {
		//changed hex 0x0f to 15
		keySets[0].d[i] = (keySets[0].k[i+3] & 15) << 4;
		//changed hex 0xf0 to 240
		keySets[0].d[i] |= (keySets[0].k[i+4] & 240) >> 4;
	}

	//changed hex 0x0f to 240
	keySets[0].d[3] = (keySets[0].k[6] & 240) << 4;

	//prob 16 rounds in here 
	for (i=1; i<17; i++) {
		for (j=0; j<4; j++) {
			keySets[i].c[j] = keySets[i-1].c[j];
			keySets[i].d[j] = keySets[i-1].d[j];
		}
               int keyShiftSizes[] = {-1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
		shiftSize = keyShiftSizes[i];
		if (shiftSize == 1){
			//changed hex 0x80 to 128
			shiftByte = 128;
		} else {
			//changed hex 0xc0 to 192
			shiftByte = 192;
		}

		// Process C
		firstShiftBits = shiftByte & keySets[i].c[0];
		secondShiftBits = shiftByte & keySets[i].c[1];
		thirdShiftBits = shiftByte & keySets[i].c[2];
		fourthShiftBits = shiftByte & keySets[i].c[3];

		keySets[i].c[0] <<= shiftSize;
		keySets[i].c[0] |= (secondShiftBits >> (8 - shiftSize));

		keySets[i].c[1] <<= shiftSize;
		keySets[i].c[1] |= (thirdShiftBits >> (8 - shiftSize));

		keySets[i].c[2] <<= shiftSize;
		keySets[i].c[2] |= (fourthShiftBits >> (8 - shiftSize));

		keySets[i].c[3] <<= shiftSize;
		keySets[i].c[3] |= (firstShiftBits >> (4 - shiftSize));

		// Process D
		firstShiftBits = shiftByte & keySets[i].d[0];
		secondShiftBits = shiftByte & keySets[i].d[1];
		thirdShiftBits = shiftByte & keySets[i].d[2];
		fourthShiftBits = shiftByte & keySets[i].d[3];

		keySets[i].d[0] <<= shiftSize;
		keySets[i].d[0] |= (secondShiftBits >> (8 - shiftSize));

		keySets[i].d[1] <<= shiftSize;
		keySets[i].d[1] |= (thirdShiftBits >> (8 - shiftSize));

		keySets[i].d[2] <<= shiftSize;
		keySets[i].d[2] |= (fourthShiftBits >> (8 - shiftSize));

		keySets[i].d[3] <<= shiftSize;
		keySets[i].d[3] |= (firstShiftBits >> (4 - shiftSize));

		for (j=0; j<48; j++) {
			shiftSize = PC2[j];
			if (shiftSize <= 28) {
				//changed hex 0x80 to 128
				shiftByte = 128 >> ((shiftSize - 1)%8);
				shiftByte &= keySets[i].c[(shiftSize - 1)/8];
				shiftByte <<= ((shiftSize - 1)%8);
			} else {
				//changed hex 0x80 to 128
				shiftByte = 128 >> ((shiftSize - 29)%8);
				shiftByte &= keySets[i].d[(shiftSize - 29)/8];
				shiftByte <<= ((shiftSize - 29)%8);
			}

			keySets[i].k[j/8] |= (shiftByte >> j%8);
		}
	}





}//end subkeyGenerator();

void desFunction(unsigned char* dataBlock, unsigned char* processedBlock, keySet* keySets, int mode){

	int i, k;
	int shiftSize;
	unsigned char shiftByte;

	unsigned char initialPermutation[8];
	memset(initialPermutation, 0, 8);
	memset(processedBlock, 0, 8);

	for (i=0; i<64; i++) {
		shiftSize = IP[i];
		//changed hex 0x80 to 128
		shiftByte = 128 >> ((shiftSize - 1)%8);
		shiftByte &= dataBlock[(shiftSize - 1)/8];
		shiftByte <<= ((shiftSize - 1)%8);

		initialPermutation[i/8] |= (shiftByte >> i%8);
	}

	unsigned char l[4], r[4];
	for (i=0; i<4; i++) {
		l[i] = initialPermutation[i];
		r[i] = initialPermutation[i+4];
	}

	unsigned char ln[4], rn[4], er[6], ser[4];

	int keyIndex;
	for (k=1; k<=16; k++) {
		memcpy(ln, r, 4);

		memset(er, 0, 6);

		for (i=0; i<48; i++) {
			shiftSize = E[i];
			//changed hex 0x80 to 128
			shiftByte = 128 >> ((shiftSize - 1)%8);
			shiftByte &= r[(shiftSize - 1)/8];
			shiftByte <<= ((shiftSize - 1)%8);

			er[i/8] |= (shiftByte >> i%8);
		}
                 //decryption is 0
		if (mode == 0) {
			keyIndex = 17 - k;
		} else {
			keyIndex = k;
		}

		for (i=0; i<6; i++) {
			er[i] ^= keySets[keyIndex].k[i];
		}

		unsigned char row, column;

		for (i=0; i<4; i++) {
			ser[i] = 0;
		}


		// Byte 1
		row = 0;
		//changed hex 0x80 to 128
		row |= ((er[0] & 128) >> 6);
		//changed hex 0x04
		row |= ((er[0] & 4) >> 2);

		column = 0;
		//changed hex 0x78 to 120
		column |= ((er[0] & 120) >> 3);

		ser[0] |= ((unsigned char)S1[row*16+column] << 4);

		row = 0;
		//changed hex 0x02 to 2
		row |= (er[0] & 2);
		//changed hex 0x10 to 16
		row |= ((er[1] & 16) >> 4);

		column = 0;
		//changed hex 0x01 to 1
		column |= ((er[0] & 1) << 3);
		//changed hex 0xe0 to 224
		column |= ((er[1] & 224) >> 5);

		ser[0] |= (unsigned char)S2[row*16+column];

		// Byte 2
		row = 0;
		//changed hex 0x08 to 8
		row |= ((er[1] & 8) >> 2);
		//changed hex 0x40 to 64
		row |= ((er[2] & 64) >> 6);

		column = 0;
		//changed hex 0x07 to 7
		column |= ((er[1] & 7) << 1);
		//changed hex 0x80 to 128
		column |= ((er[2] & 128) >> 7);

		ser[1] |= ((unsigned char)S3[row*16+column] << 4);

		row = 0;
		//changed hex 0x20 to
		row |= ((er[2] & 32) >> 4);
		//changed hex 0x01 to 1
		row |= (er[2] & 1);

		column = 0;
		//changed hex 0x1e to 30
		column |= ((er[2] & 30) >> 1);

		ser[1] |= (unsigned char)S4[row*16+column];

		// Byte 3
		row = 0;
		//changed hex 0x80 to 128
		row |= ((er[3] & 128) >> 6);
		//changed hex 0x04 to 4
		row |= ((er[3] & 4) >> 2);

		column = 0;
		//changed hex 0x78 to 120
		column |= ((er[3] & 120) >> 3);

		ser[2] |= ((unsigned char)S5[row*16+column] << 4);

		row = 0;
		//changed hex 0x02 to 2
		row |= (er[3] & 2);
		//changed hex 0x10 to 16
		row |= ((er[4] & 16) >> 4);

		column = 0;
		//changed hex 0x01 to 1
		column |= ((er[3] & 1) << 3);
		//changed hex 0xe0 to 224
		column |= ((er[4] & 224) >> 5);

		ser[2] |= (unsigned char)S6[row*16+column];

		// Byte 4
		row = 0;
		//changed hex 0x08 to 8
		row |= ((er[4] & 8) >> 2);
		//changed hex 0x40 to 64
		row |= ((er[5] & 64) >> 6);

		column = 0;
		//changed hex 0x07 to 7
		column |= ((er[4] & 7) << 1);
		//changed hex 0x80 to 128
		column |= ((er[5] & 128) >> 7);

		ser[3] |= ((unsigned char)S7[row*16+column] << 4);

		row = 0;
		//changed hex 0x20 to 32
		row |= ((er[5] & 32) >> 4);
		//changed hex 0x01 to 1
		row |= (er[5] & 1);

		column = 0;
		//changed hex 0x1e to 30
		column |= ((er[5] & 30) >> 1);

		ser[3] |= (unsigned char)S8[row*16+column];

		for (i=0; i<4; i++) {
			rn[i] = 0;
		}

		for (i=0; i<32; i++) {
			shiftSize = HP[i];
			//changed hex 0x80 to 128
			shiftByte = 128 >> ((shiftSize - 1)%8);
			shiftByte &= ser[(shiftSize - 1)/8];
			shiftByte <<= ((shiftSize - 1)%8);

			rn[i/8] |= (shiftByte >> i%8);
		}

		for (i=0; i<4; i++) {
			rn[i] ^= l[i];
		}

		for (i=0; i<4; i++) {
			l[i] = ln[i];
			r[i] = rn[i];
		}
	}

	unsigned char preEndPermutation[8];
	for (i=0; i<4; i++) {
		preEndPermutation[i] = r[i];
		preEndPermutation[4+i] = l[i];
	}

	for (i=0; i<64; i++) {
		shiftSize = FP[i];
		//changed hex 0x80 to 128
		shiftByte = 128 >> ((shiftSize - 1)%8);
		shiftByte &= preEndPermutation[(shiftSize - 1)/8];
		shiftByte <<= ((shiftSize - 1)%8);

		processedBlock[i/8] |= (shiftByte >> i%8);
	}


}//end desFunction();


