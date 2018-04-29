#ifndef PART2_H
#define PART2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/engine.h>
#include <openssl/des.h>

static FILE *plainText, *encryptedSessionKey, *theirPublicKey, *ourPrivateKey;

void DecryptSessionKey(void);
void SignMessage(void);
void EncryptDES(void);

void DecryptSessionKey(void){

	EVP_PKEY_CTX *ctx;
	ENGINE *eng = NULL;
	unsigned char *out, *in;
	size_t outlen, inlen;
	EVP_PKEY *key;
	

	//setting up in and inlen
	//get inlen
	fseek(encryptedSessionKey, 0L, SEEK_END);
	inlen = ftell(encryptedSessionKey);
	fseek(encryptedSessionKey, 0L, SEEK_SET);

	//allocate memory
	in = (unsigned char *)malloc(inlen);
	
	//read contents of encryptedSessionKey to in
	fread(in, 1, inlen, encryptedSessionKey);

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
	//was PKCS1_OAEP padding
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
	FILE *decryptedSessionKey = fopen("decryptedSessionKey.txt", "wb");
	//fprintf(decryptedSessionKey, "%x", out);
	fwrite(out, 8, 1, decryptedSessionKey);
	printf("Decrypted session key printed to decryptedSessionKey.txt\n");

	//closing files
	fclose(decryptedSessionKey);
	//free
	free(in);
	free(out);
}//end DecryptSessionKey()

void SignMessage(void){

	EVP_PKEY_CTX *ctx;
	unsigned char *md, *sig;
	size_t mdlen = 32, siglen, size;
	EVP_PKEY *signingKey;
	
	FILE *cipherText = fopen("cipher.txt", "rb");
	
	fseek(cipherText, 0L, SEEK_END);
	size = ftell(cipherText);
	fseek(cipherText, 0L, SEEK_SET);
	//size+=1;
	//allocate memory
	md = (unsigned char *)malloc(size);
	
	//read contents of plainText to in
	fread(md, 1, size, cipherText);
	
	signingKey = PEM_read_PrivateKey(ourPrivateKey,NULL,NULL,NULL);

	ctx = EVP_PKEY_CTX_new(signingKey, NULL);
	if (!ctx){
		printf("Error: not ctx\n");
		exit(1);
	}
	if (EVP_PKEY_sign_init(ctx) <= 0){
		printf("Error: EVP_PKEY_sign_init(ctx) <= 0\n");
		exit(1);
	}
	//was PKCS1 padding
	if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING) <= 0){
		printf("Error: EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING) <= 0\n");
		exit(1);
	}
	if (EVP_PKEY_CTX_set_signature_md(ctx, EVP_sha256()) <= 0){
		printf("Error: EVP_PKEY_CTX_set_signature_md(ctx, EVP_sha256()) <= 0\n");
		exit(1);
	}
	if (EVP_PKEY_sign(ctx, NULL, &siglen, md, mdlen) <= 0){
		printf("Error: EVP_PKEY_sign(ctx, NULL, &siglen, md, mdlen) <= 0\n");
		exit(1);
	}

	sig = OPENSSL_malloc(siglen);

	if (!sig){
		printf("Error: not sig\n");
		exit(1);
	}

	if (EVP_PKEY_sign(ctx, sig, &siglen, md, mdlen) <= 0){
		printf("Error: EVP_PKEY_sign(ctx, sig, &siglen, md, mdlen) <= 0\n");
		exit(1);
	}
		
	//write out to decryptedSessionKey.txt
	FILE *signature = fopen("signature.txt", "wb");
	//fprintf(cipherText, "%s", sig);
	fwrite(sig, 1, siglen, signature);
	printf("Cipher.txt signature printed to signature.txt\n");

	//closing files
	fclose(signature);
	fclose(cipherText);
	//free
	free(md);
	free(sig);

}//end SignMessage

void EncryptDES(void){

	unsigned char *output, *input;
	size_t size;
	
	fseek(plainText, 0L, SEEK_END);
	size = ftell(plainText);
	fseek(plainText, 0L, SEEK_SET);
	//size+=1;
	input = (unsigned char *)malloc(size);
	output = (unsigned char *)malloc(size);
	
	//read contents of plainText to input
	fread(input, 1, size, plainText);

	DES_cblock key = {0x62,0xa6,0x66,0x06,0xaa,0x5c,0xf6,0x36};
	DES_cblock iv = {0x77,0x48,0xea,0xf9,0x25,0xf7,0xc1,0x06};

	DES_key_schedule schedule;
	DES_set_odd_parity(&key);
	DES_set_key_checked(&key, &schedule);
	//was sizeof(input) in 3rd param
	DES_ncbc_encrypt(input, output, size, &schedule, &iv, DES_ENCRYPT);

	//write out to cipher.txt
	FILE *cipherText = fopen("cipher.txt", "wb");
	//fprintf(decryptedSessionKey, "%x", out);
	fwrite(output, 1, size, cipherText);
	printf("Encrypted plaintext printed to cipher.txt\n");

	//closing files
	fclose(cipherText);
	//free
	free(input);
	free(output);
	

}//end EncryptDES()

#endif
