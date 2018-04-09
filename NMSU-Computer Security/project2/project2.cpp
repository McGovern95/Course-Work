#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <unistd.h> 

#include "desfunct.h"
using namespace std;

#define SIZEOFKEY (unsigned char*) malloc(8*sizeof(char))

int main(){
   
   static FILE *inputFile, *outputFile, *keyFile, *ivFile;
   unsigned long size;
   char* temp;
   int writeToFile, desMode, pad, keyRead, ivRead;
   unsigned long countBlock, totalBlock;
   //key variables 
   unsigned char* block = SIZEOFKEY;
   unsigned char* desBlock = SIZEOFKEY;
   subKey* subKeys = (subKey*)malloc(17*sizeof(subKey));
   unsigned char* desKey = SIZEOFKEY;
   unsigned char* ivKey = SIZEOFKEY;

    int choice;
    printf("Please enter a 1 if you want to generate your own key and IV," 
           "or a 0 if you want to provide your own key and IV.\n(please use "
           "the same key and iv that you "
           "encrypted with to successfully decrypt)\n");
    cin >> choice;
    if(choice != 0 && choice !=1){
    	printf("please enter a 1 or 0 \n");
        return 1;
    }
      //key generation code
      if(choice == 1){
         printf("Generating key into key.txt\n");
	     printf("Generating IV into iv.txt\n");
         keyFile = fopen("key.txt","wb");
	     ivFile = fopen("iv.txt","wb");
         if(!keyFile || !ivFile){
         	printf("error creating file");
            return 1;
         }
        
		//seed for random generator
		unsigned int seed = (unsigned int)time(NULL);
		srand (seed);
        //generates the key and iv
		generator(desKey,ivKey);
     
		writeToFile = fwrite(desKey, 1, 8, keyFile);
		writeToFile = fwrite(ivKey, 1, 8, ivFile);

		fclose(keyFile);
		fclose(ivFile);
      } //end key generator code 
    //key provided by user code
    else if(choice == 0){
        printf("what is your key file? \n");
        scanf("%s", temp);
        keyFile = fopen(temp,"r");
	if(keyFile==NULL){
	    printf("%s does not exist \n",temp);
	    return 1;
	}

	printf("what is your iv file? \n");
        scanf("%s", temp);
        ivFile = fopen(temp,"r");
	if(ivFile==NULL){
	    printf("%s does not exist \n",temp);
	    return 1;
	}

	keyRead = fread(desKey, sizeof(unsigned char), 8, keyFile);
	ivRead = fread(ivKey, sizeof(unsigned char), 8, ivFile);
	if (keyRead != 8 || ivRead != 8) {
	      printf("Key and IV needs to be 8 bytes \n");
	      return 1;
	}	
    }//end already have key check
 
    /*
		CREATES SUBKEYS
	*/
	subkeyGenerator(subKeys, desKey);

     char choice2;
     printf("did you want to Encrypt or Decrypt? (e/d)\n");
     cin >> choice2; 
     if(choice2 != 'e' && choice2 !='d'){
    	 printf("please enter an 'e' or 'd' \n");
          return 1;
   	 }

/*

	ENCRYPTION

*/

    if(choice2 == 'e'){
	printf("Please enter the plain text to be encrypted \n");
	scanf("%s", temp);
	inputFile = fopen(temp,"r");
	if(inputFile==NULL){
	   printf("%s does not exist \n",temp);
	   return 1;
	}
    printf("The cipher will be put in cipher.txt \n");
	outputFile = fopen("cipher.txt","wb");
  
	desMode = 1;
    printf("Encrypting--------- \n");
    //fseek to find # of block
	fseek(inputFile, 0L, SEEK_END);
	size = ftell(inputFile);
	fseek(inputFile, 0L, SEEK_SET);
	
	//puts inputfile into blocks
	if(size%8)
		totalBlock = size/8 +1;
	else
		totalBlock = size/8;
  
	//reads through input file and pads and encrypts
	countBlock = 0;
	while(fread(block,1,8,inputFile)){
	     countBlock++;
	    if(countBlock == totalBlock){
	       pad = 8 - size%8;
		if(pad < 8){
		 memset((block + 8 - pad), (unsigned char)pad,pad);
		}//end pad<8 
		
		desFunction(subKeys, block, desBlock, desMode);

		//xor the plaintxt with the ivkey
		for(int i=0; i< 8;i++)
			desBlock[i] = (unsigned char)(desBlock[i] ^ ivKey[i]);
		
		writeToFile = fwrite(desBlock, 1, 8, outputFile);

            if (pad == 8){ // Write an extra block for padding
		    memset(block, (unsigned char)pad, 8);
	        desFunction(subKeys, block, desBlock, desMode);
		
		//xor the encrypted plaintxt with ivkey
		for(int i=0; i<8;i++)
			desBlock[i] = (unsigned char)(desBlock[i] ^ ivKey[i]);
		
		writeToFile = fwrite(desBlock, 1, 8, outputFile);

	     }//end padding ==8
         
	}//end if countBlock ==
	  else{ 
		desFunction(subKeys, block, desBlock, desMode);
		
		//xor the encrypted plaintxt with ivkey
		for(int i=0; i<8;i++)
			desBlock[i] = (unsigned char)(desBlock[i] ^ ivKey[i]);
		
		writeToFile = fwrite(desBlock, 1, 8, outputFile);

	   }//end else
	memset(block, 0, 8);
	
      }//end while
	
       }//end encryption choice

/*

	DECRYPTION

*/

    else if(choice2 == 'd'){
	printf("Please enter the cipher text to be decrypted \n");
	scanf("%s", temp);
	inputFile = fopen(temp,"r");
	if(inputFile==NULL){
	   printf("%s does not exist \n",temp);
	   return 1;
	}

    printf("The decrypted cipher will be put in decrypt.txt \n");
    outputFile = fopen("decrypt.txt","wb");

    desMode = 0;
	printf("Decrypting---------- \n");
	
    //fseek to find # of block
	fseek(inputFile, 0L, SEEK_END);
	size = ftell(inputFile);
	fseek(inputFile, 0L, SEEK_SET);

	if(size%8)
		totalBlock = size/8 + 1;
	else
		totalBlock = size/8;

   countBlock = 0;
   //reads through input file and pads and decrypts
	while(fread(block,1,8,inputFile)){
	     countBlock++;
	     if(countBlock == totalBlock){

		//xor the cipher with ivkey
		for(int i=0; i<8;i++)
			block[i] = (unsigned char)(block[i] ^ ivKey[i]);
	
		desFunction(subKeys, block, desBlock, desMode);

	    pad = desBlock[7];

		if (pad<8){
		writeToFile = fwrite(desBlock, 1, 8 - pad, outputFile);
		
		}
	}//end if countBlock ==
	  else{ 
		
		//xor the cipher with the iv key
		for(int i=0; i<8;i++)
			block[i] = (unsigned char)(block[i] ^ ivKey[i]);
		
		desFunction(subKeys, block, desBlock, desMode);
		writeToFile = fwrite(desBlock, 1, 8, outputFile);

	   }//end else
	  memset(block, 0, 8);
	
      }//end while

       }//end decrpytion choice
  
  fclose(inputFile);
  fclose(outputFile);

  return 0;

}//end main();
