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

   static FILE *input, *output, *keyFile, *ivFile;
   unsigned long size;
   short int pad;
   char* temp;
   //DES key set vars
   short int bytesWritten, desMode;
   unsigned long blockCount = 0, numberOfBlocks;
   unsigned char* dataBlock = SIZEOFKEY;
   unsigned char* processedBlock = SIZEOFKEY;
   keySet* keySets = (keySet*)malloc(17*sizeof(keySet));
   unsigned char* desKey = SIZEOFKEY;
   unsigned char* ivKey = SIZEOFKEY;

    int choice;
    printf("Please enter a 1 if you want to generate your own key and IV, or 0 if you want to provide your own key and IV.\n");
    cin >> choice;
    if(choice != 0 && choice !=1){
    	printf("please enter a 1 or 0 \n");
        return 1;
    }
      if(choice == 1){
         printf("Generating key into key.txt\n");
	 printf("Generating IV into iv.txt\n");
         keyFile = fopen("key.txt","wb");
	 ivFile = fopen("iv.txt","wb");
         if(!keyFile || !ivFile){
         	printf("error creating file");
            return 1;
         }
                short int bytesWritten;
		short int ivWritten;
		//seed for random generator
		unsigned int seed = (unsigned int)time(NULL);
		srand (seed);

		keyGenerator(desKey);
        ivGenerator(ivKey);
		bytesWritten = fwrite(desKey, 1, 8, keyFile);
		ivWritten = fwrite(ivKey, 1, 8, ivFile);
		fclose(keyFile);
		fclose(ivFile);
      } //end key generator code 

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


	short int bytesRead;
	short int ivRead;
	bytesRead = fread(desKey, sizeof(unsigned char), 8, keyFile);
	ivRead = fread(ivKey, sizeof(unsigned char), 8, ivFile);
	if (bytesRead != 8 || ivRead != 8) {
	      printf("Key and IV needs to be 8 bytes \n");
	      fclose(keyFile);
	      fclose(ivFile);
	      return 1;
	}	
    }//end already have key check
 
    /*
		CREATES SUBKEYS
	*/
	subkeyGenerator(desKey, keySets);


     char choice2;
     printf("did you want to Encrypt or Decrypt? (e/d) \n");
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
	input = fopen(temp,"r");
	if(input==NULL){
	   printf("%s does not exist \n",temp);
	   return 1;
	}
         printf("The cipher will be put in cipher.txt \n");
	 output = fopen("cipher.txt","wb");
  
       //encrypt stuff
	desMode = 1;
        printf("Encrypting--------- \n");
    
	fseek(input, 0L, SEEK_END);

	size = ftell(input);

	fseek(input, 0L, SEEK_SET);
	
	if(size%8)
		numberOfBlocks = size/8 +1;
	else
		numberOfBlocks = size/8;

	
	while(fread(dataBlock,1,8,input)){
	     blockCount++;
	     if(blockCount == numberOfBlocks){
	        pad = 8 - size%8;
		if(pad < 8){
		 memset((dataBlock + 8 - pad), (unsigned char)pad,pad);
		}//end pad<8 
		
		desFunction(dataBlock, processedBlock, keySets, desMode);

		//this is xor the plaintxt with the ivkey
		int i;
		for(i=0; i< 8;i++){
			processedBlock[i] = (char)(processedBlock[i] ^ ivKey[i]);
		}
		bytesWritten = fwrite(processedBlock, 1, 8, output);

            if (pad == 8){ // Write an extra block for padding
		memset(dataBlock, (unsigned char)pad, 8);
	        desFunction(dataBlock, processedBlock, keySets, desMode);
		
		//this is xor the encrypted plaintxt with ivkey
		int i;
		for(i=0; i< 8;i++){
			processedBlock[i] = (char)(processedBlock[i] ^ ivKey[i]);
		}
		bytesWritten = fwrite(processedBlock, 1, 8, output);

	     }//end padding ==8
         
	}//end if blockcount ==
	  else{ 
		desFunction(dataBlock, processedBlock, keySets, desMode);
		
		//this is xor the encrypted plaintxt with ivkey
		int i;
		for(i=0; i< 8;i++){
			processedBlock[i] = (char)(processedBlock[i] ^ ivKey[i]);
		}
		bytesWritten = fwrite(processedBlock, 1, 8, output);

	   }//end else
	memset(dataBlock, 0, 8);
	
      }//end while
	
       }//end encryption choice

/*

	DECRYPTION

*/

        else if(choice2 == 'd'){
	printf("Please enter the cipher text to be decrypted \n");
	scanf("%s", temp);
	input = fopen(temp,"r");
	if(input==NULL){
	   printf("%s does not exist \n",temp);
	   return 1;
	}

      printf("The decrypted cipher will be put in decrpyt.txt \n");
      output = fopen("decrypt.txt","wb");

	printf("Decrypting---------- \n");
	//decryption stuff
	desMode = 0;

	fseek(input, 0L, SEEK_END);
	size = ftell(input);

	fseek(input, 0L, SEEK_SET);
	if(size%8)
		numberOfBlocks = size/8 + 1;
	else
		numberOfBlocks = size/8;

	while(fread(dataBlock,1,8,input)){
	     blockCount++;
	     if(blockCount == numberOfBlocks){

		//this is xor the cipher with ivkey
		int i;
		for(i=0; i< 8;i++){
			dataBlock[i] = (char)(dataBlock[i] ^ ivKey[i]);
		}

		desFunction(dataBlock, processedBlock, keySets, desMode);
	        pad = processedBlock[7];
		if (pad < 8){
		bytesWritten = fwrite(processedBlock, 1, 8 - pad, output);
		
		}
	}//end if blockcount ==
	  else{ 
		
		//this is xor the cipher with the iv key
		int i;
		for(i=0; i< 8;i++){
			dataBlock[i] = (char)(dataBlock[i] ^ ivKey[i]);
		}
		desFunction(dataBlock, processedBlock, keySets, desMode);
		bytesWritten = fwrite(processedBlock, 1, 8, output);

	   }//end else
	memset(dataBlock, 0, 8);
	
      }//end while

       }//end decrpytion choice
  
  return 0;

}//end main();
