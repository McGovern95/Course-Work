#include "part2.h"

int main(int argc, char * argv[]){
	//example run input
	//./part2 -Plain plain.txt -EncryptedSessionKey encrypted_session.key -ThirdPartyPublic TApubkey.pem -Private privkey.pem
	//reading files
	int counter=0;
	while(counter < argc){
		if(strcmp(argv[counter],"-Plain") == 0){
			plainText = fopen(argv[counter+1],"rb");
			if(plainText == NULL){
				printf("Could not open file %s for reading.\n",argv[counter+1]);
				exit(1);
			}
			counter++;
		}
		else if(strcmp(argv[counter],"-EncryptedSessionKey") == 0){
			encryptedSessionKey = fopen(argv[counter+1],"rb");
			if(encryptedSessionKey == NULL){
				printf("Could not open file %s for reading.\n",argv[counter+1]);
				exit(1);
			}
			counter++;
		}
		else if(strcmp(argv[counter],"-ThirdPartyPublic") == 0){
			theirPublicKey = fopen(argv[counter+1],"rb");
			if(theirPublicKey == NULL){
				printf("Could not open file %s for reading.\n",argv[counter+1]);
				exit(1);
			}
			counter++;
		}
		else if(strcmp(argv[counter],"-Private") == 0){
			ourPrivateKey = fopen(argv[counter+1],"rb");
			if(ourPrivateKey == NULL){
				printf("Could not open file %s for reading.\n",argv[counter+1]);
				exit(1);
			}
			counter++;
		}
		else if(strcmp(argv[counter],"./part2") == 0){
		}
		else{
			printf("Error: bad parameter.\n");
			exit(1);
		}
		counter++;
	}//end of while
	
	//decrypt encrypted session key using their public key
	DecryptSessionKey();
	
	EncryptDES();
	//encrypting plain.txt with hex key from decryptedSessionKey.txt and hex iv from iv.txt into cipher.txt
	//system("openssl enc -e -des-cbc -nosalt -K 62a66606aa5cf636 -iv 7748eaf925f7c106 -in plain.txt -out cipher.txt");
	//printf("Encrypted plaintext printed to cipher.txt\n");

	//sign cipher.txt with ourPrivateKey
	SignMessage();
	
	//closing files
	fclose(plainText);
	fclose(encryptedSessionKey);
	fclose(theirPublicKey);
	fclose(ourPrivateKey);
	return 0;
}//end main
