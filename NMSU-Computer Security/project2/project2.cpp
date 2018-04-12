#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "desfunct.h"
using namespace std;

int main(){
   
	static FILE *inputFile, *outputFile, *keyFile, *ivFile;
	unsigned long size;
	char temp[35]="";
	int writeToFile, desMode, pad, keyRead, ivRead;
	unsigned long countBlock, totalBlock;
	
	//key variables 
	unsigned char block[8];
	unsigned char desBlock[8];
	subKey* subKeys = (subKey*)malloc(17*sizeof(subKey));
	unsigned char desKey[8];
	unsigned char ivKey[8];

	//asks user if they want to generate key and iv or give their own
	int choice;
	printf("Please enter a 1 if you want to generate your own key and IV," 
		"or a 0 if you want to provide your own key and IV.\n(please use "
		"the same key and iv that you "
		"encrypted with to successfully decrypt)\n");
	cin >> choice;
	
	if(choice != 0 && choice !=1){
		printf("please enter a 1 or 0, Exiting program now \n");
		exit(1);
	}
	
	//key generation code
	if(choice == 1){
	
		printf("Generating key into key.txt\n");
		printf("Generating IV into iv.txt\n");
		keyFile = fopen("key.txt","wb");
		ivFile = fopen("iv.txt","wb");
		
		if(!keyFile || !ivFile){
			printf("error creating file, Exiting program now \n");
			exit(2);
		}

		//seed for random generator
		unsigned int seed = (unsigned int)time(NULL);
		srand (seed);
		
		//generates the key and iv
		generator(desKey,ivKey);
		
		//writes iv and key to key.txt and iv.txt
		writeToFile = fwrite(desKey, 1, 8, keyFile);
		writeToFile = fwrite(ivKey, 1, 8, ivFile);
		
		//clean memory
		fclose(keyFile);
		fclose(ivFile);
		
	} //end key generator code 
		
	//key provided by user code
	else if(choice == 0){
	
		printf("what is your key file? \n");
		scanf("%s", temp);
		keyFile = fopen(temp,"r");
		
		if(keyFile==NULL){
			printf("%s does not exist, Exiting program now \n",temp);
			exit(3);
		}

		printf("what is your iv file? \n");
		scanf("%s", temp);
		ivFile = fopen(temp,"r");
		
		if(ivFile==NULL){
			printf("%s does not exist, Exiting program now \n",temp);
			exit(4);
		}
		
		//read from file
		keyRead = fread(desKey, sizeof(unsigned char), 8, keyFile);
		ivRead = fread(ivKey, sizeof(unsigned char), 8, ivFile);
		
		if (keyRead != 8 || ivRead != 8) {
			printf("Key and IV needs to be 8 bytes, Exiting program now \n");
			exit(5);
		}
			
	}//end key provided by user
 
	//create subkeys
	subkeyGenerator(subKeys, desKey);

	//asks user if they want to encrypt or decrypt
	char choice2;
	printf("did you want to Encrypt or Decrypt? (e/d)\n");
	cin >> choice2;
	
	//input checking 
	if(choice2 != 'e' && choice2 !='d'){
		printf("please enter an 'e' or 'd', Exiting program now \n");
		exit(6);
	}
	
	//encryption
	if(choice2 == 'e'){

		//prompts user for plaintext file	
		printf("Please enter the plain text to be encrypted \n");
		scanf("%s", temp);
		inputFile = fopen(temp,"r");
		
		//file input checking
		if(inputFile==NULL){
			printf("%s does not exist, Exiting program now \n",temp);
			exit(7);
		}
		
		printf("The cipher will be put in cipher.txt \n");
		outputFile = fopen("cipher.txt","wb");

		//set desMode to ecrypting(1)
		desMode = 1;
		printf("Encrypting--------- \n");
		
		//fseek to find # of block
		fseek(inputFile, 0L, SEEK_END);
		size = ftell(inputFile);
		fseek(inputFile, 0L, SEEK_SET);

		//padding scheme used 

		//puts inputfile into blocks
		if(size%8)
			totalBlock = size/8 +1;
		else
			totalBlock = size/8;
  
		//reads through input file and pads and encrypts
		//we are using pkcs#5 padding, because we are using 8-byte blocks 
		countBlock = 0;
		while(fread(block,1,8,inputFile)){
		
			countBlock++;
			if(countBlock == totalBlock){
			
				pad = 8 - size%8;
				
				if(pad < 8){
					//fill rest of block if below 8 
					memset((block + 8 - pad), (unsigned char)pad, pad);
				}//end pad<8 

				//CBC formula: Ci = Ek(P XOR Ci-1), C0 = IV

				//xor the plaintxt with the ivkey
				for(int i=0; i< 8;i++)
					block[i] = (unsigned char)(block[i] ^ ivKey[i]);

				//encrypting
				desFunction(subKeys, block, desBlock, desMode);


				//writes to cipher.txt
				writeToFile = fwrite(desBlock, 1, 8, outputFile);

				//extra block for padding
				if (pad == 8){ 
				    //fills block with 8 bytes
					memset(block, (unsigned char)pad, 8);

					//xor the encrypted plaintxt with ivkey
					for(int i=0; i<8;i++)
						block[i] = (unsigned char)(block[i] ^ ivKey[i]);

					//encrypting
					desFunction(subKeys, block, desBlock, desMode);

					//writes to cipher.txt
					writeToFile = fwrite(desBlock, 1, 8, outputFile);

			 	}//end padding == 8
			 
			}//end if countBlock ==
			
			else{ 
				//xor the encrypted plaintxt with ivkey
				for(int i=0; i<8;i++)
					block[i] = (unsigned char)(block[i] ^ ivKey[i]);

				//encrypting
				desFunction(subKeys, block, desBlock, desMode);

				//writes to cipher.txt
				writeToFile = fwrite(desBlock, 1, 8, outputFile);

			}//end else
			memset(block, 0, 8);

		}//end while
	
	}//end encryption choice

	//decryption
    else if(choice2 == 'd'){
    
    	//prompts user for cipher file
		printf("Please enter the cipher text to be decrypted \n");
		scanf("%s", temp);
		inputFile = fopen(temp,"r");
		
		//file input checking
		if(inputFile==NULL){
	   		printf("%s does not exist, Exiting program now \n",temp);
	   		exit(8);
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

				//CBC Decrypt Formula: Pi = Dk(Ci) xor Ci-1, C0 = IV

				//decrypts
				desFunction(subKeys, block, desBlock, desMode);
				//xor the cipher with ivkey
				for(int i=0; i<8;i++)
					desBlock[i] = (unsigned char)(desBlock[i] ^ ivKey[i]);
					
				pad = desBlock[7];
                  //block is less than 8 bytes
				if (pad<8){
					//write to decrypt.txt
					writeToFile = fwrite(desBlock, 1, 8 - pad, outputFile);
				}
			
			}//end if countBlock ==
			
	  		else{ 
		
			    //decrypts
				desFunction(subKeys, block, desBlock, desMode);

				//xor the cipher with the iv key
				for(int i=0; i<8;i++)
					desBlock[i] = (unsigned char)(desBlock[i] ^ ivKey[i]);
	
				//writes to decrypt.txt
				writeToFile = fwrite(desBlock, 1, 8, outputFile);

	   		}//end else
	   		
	  		memset(block, 0, 8);
	
		}//end while

	}//end decrpytion choice
  
	//clean up memory for valgrind 
	fclose(inputFile);
	fclose(outputFile);
	free(subKeys);

	return 0;

}//end main();
