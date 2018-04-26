#include "part2.h"

int main(int argc, char * argv[]){
	//example run input
	//./part2 -Plain plain.txt -SessionKey encrypted_session.key -ThirdPartyPublic TApubkey.pem -Private privkey.pem
	//reading files
	static FILE *plainText, *encryptedSessionKey, *theirPublicKey, *ourPrivateKey;
	int counter=0;
	while(counter < argc){
		if(strcmp(argv[counter],"-Plain") == 0){
			plainText = fopen(argv[counter+1],"r");
			if(plainText == NULL){
				printf("Could not open file %s for reading.\n",argv[counter+1]);
				exit(1);
			}
			counter++;//ff
		}
		else if(strcmp(argv[counter],"-SessionKey") == 0){
			encryptedSessionKey = fopen(argv[counter+1],"r");
			if(encryptedSessionKey == NULL){
				printf("Could not open file %s for reading.\n",argv[counter+1]);
				exit(1);
			}
			counter++;
		}
		else if(strcmp(argv[counter],"-ThirdPartyPublic") == 0){
			theirPublicKey = fopen(argv[counter+1],"r");
			if(theirPublicKey == NULL){
				printf("Could not open file %s for reading.\n",argv[counter+1]);
				exit(1);
			}
			counter++;
		}
		else if(strcmp(argv[counter],"-Private") == 0){
			ourPrivateKey = fopen(argv[counter+1],"r");
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
	EVP_PKEY_CTX *ctx;
	ENGINE *eng = NULL;
	unsigned char *out, *in;
	size_t outlen, inlen;
	EVP_PKEY *key;
	

	//setting up in and inlen
	//get inlen
	fseek(encryptedSessionKey, 0, SEEK_END);
	inlen = ftell(encryptedSessionKey);
	fseek(encryptedSessionKey, 0, SEEK_SET);
	//allocate memory
	in = (char *)malloc(inlen+1);
	
	//read contents of encryptedSessionKey to in
	fread(in, inlen, 1, encryptedSessionKey);
	//setup key
	key = PEM_read_PUBKEY(theirPublicKey,NULL,NULL,NULL);
	
	ctx = EVP_PKEY_CTX_new(key, eng);
	if(!ctx){
		printf("ERROR: not ctx\n");
		exit(1);
	}
	if(EVP_PKEY_encrypt_init(ctx) <= 0){
		printf("ERROR: EVP_PKEY_encrypt_init(ctx) <=0\n");
		exit(1);
	}
	//was oaep padding
	if(EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_NO_PADDING) <= 0){
		printf("ERROR: EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_NO_PADDING) <= 0\n");
		exit(1); 
	}
	if(EVP_PKEY_encrypt(ctx, NULL, &outlen, in, inlen) <= 0){
		printf("ERROR: EVP_PKEY_encrypt(ctx, NULL, &outlen, in, inlen) <= 0\n");
		exit(1);
	}
	
	out = OPENSSL_malloc(outlen);
	
	if(!out){
		printf("Malloc failure\n");
		exit(1);
	}
	
	if(EVP_PKEY_encrypt(ctx, out, &outlen, in, inlen) <= 0){
		printf("ERROR: EVP_PKEY_encrypt(ctx, out, &outlen, in, inlen) <= 0\n");
		exit(1);
	}
	//write out to decryptedSessionKey.txt
	FILE *decryptedSessionKey = fopen("decryptedSessionKey.txt", "w");
	fprintf(decryptedSessionKey, "%u", out);
	//fwrite(out, 1, outlen, decryptedSessionKey);
	printf("decrypted session key in DecryptedSessionKey.txt\n");

        //des command which works for me
	//openssl enc -e -des-cbc -nosalt -K 12856768 -iv 11111111 -in plain.txt -out cipher.txt
 
	
	//closing files
	fclose(plainText);
	fclose(encryptedSessionKey);
	fclose(theirPublicKey);
	fclose(ourPrivateKey);
	fclose(decryptedSessionKey);
	//free
	free(in);
}
