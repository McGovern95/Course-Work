#include "part3.h"

int main(int argc, char * argv[]){
	//example run input
	//./part3 -Public pubkey.pem -DecryptedSessionKey decryptedSessionKey.txt -Cipher cipher.txt -Signature signature.txt
	//reading files
	//error checking
	int counter=0;
	while(counter < argc){
		if(strcmp(argv[counter],"-Public") == 0){
			ourPublicKey = fopen(argv[counter+1],"rb");
			if(ourPublicKey == NULL){
				printf("Could not open file %s for reading.\n",argv[counter+1]);
				exit(1);
			}
			counter++;
		}
		else if(strcmp(argv[counter],"-DecryptedSessionKey") == 0){
			decryptedSessionKey = fopen(argv[counter+1],"rb");
			if(decryptedSessionKey == NULL){
				printf("Could not open file %s for reading.\n",argv[counter+1]);
				exit(1);
			}
			counter++;
		}
		else if(strcmp(argv[counter],"-Cipher") == 0){
			cipherText = fopen(argv[counter+1],"rb");
			if(cipherText == NULL){
				printf("Could not open file %s for reading.\n",argv[counter+1]);
				exit(1);
			}
			counter++;
		}
		else if(strcmp(argv[counter],"-Signature") == 0){
			signature = fopen(argv[counter+1],"rb");
			if(signature == NULL){
				printf("Could not open file %s for reading.\n",argv[counter+1]);
				exit(1);
			}
			counter++;
		}
		else if(strcmp(argv[counter],"./part3") == 0){
		}
		else{
			printf("Error: bad parameter.\n");
			exit(1);
		}
		counter++;
	}//end of while
	
	//decrypting cipher.txt with hex key from decryptedSessionKey.txt and hex iv from iv.txt into decryptedCipher.txt
	//system("openssl enc -d -des-cbc -nosalt -K 62a66606aa5cf636 -iv 7748eaf925f7c106 -in cipher.txt -out decryptedCipher.txt");
	//printf("Decrypted ciphertext printed to decryptedCipher.txt\n");
	DecryptDES();
	
	//printing plaintext
	printf("The plaintext is: \n");
	static FILE *decryptedCipher;
	decryptedCipher = fopen("decryptedCipher.txt", "rb");
	if(!decryptedCipher){
		printf("Error reading decryptedCipher.txt.\n");
		exit(1);
	}
	char file = fgetc(decryptedCipher);
	while(file != EOF){
		printf("%c", file);
		file = fgetc(decryptedCipher);
	}
	//printf("\n");
	
	//verifying signature
	if(VerifySignature() == 1){
		printf("Signature authentication confirmed.\n");
	}
	else{
		printf("Signature authentication failed.\n");
	}
	
	//closing files
	fclose(cipherText);
	fclose(decryptedSessionKey);
	fclose(signature);
	fclose(ourPublicKey);
	fclose(decryptedCipher);
	return 0;
}//end main

