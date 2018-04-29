#ifndef PART3_H
#define PART3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/engine.h>
#include <openssl/des.h>

static FILE *ourPublicKey, *decryptedSessionKey, *cipherText, *signature;

void DecryptDES(void);
int VerifySignature(void);

void DecryptDES(void){

	unsigned char *output, *input;
	size_t size;
	
	fseek(cipherText, 0L, SEEK_END);
	size = ftell(cipherText);
	fseek(cipherText, 0L, SEEK_SET);
	//size+=1;
	input = (unsigned char *)malloc(size);
	output = (unsigned char *)malloc(size);
	
	//read contents of cipherText to input
	fread(input, 4, size, cipherText);

	DES_cblock key = {0x62,0xa6,0x66,0x06,0xaa,0x5c,0xf6,0x36};
	DES_cblock iv = {0x77,0x48,0xea,0xf9,0x25,0xf7,0xc1,0x06};

	DES_key_schedule schedule;
	DES_set_odd_parity(&key);
	DES_set_key_checked(&key, &schedule);
	//was sizeof(input) in 3rd param
	DES_ncbc_encrypt(input, output, size, &schedule, &iv, DES_DECRYPT);

	//write out to decryptedCipher.txt
	FILE *decryptedCipher = fopen("decryptedCipher.txt", "wb");
	//fprintf(decryptedSessionKey, "%x", out);
	fwrite(output, 1, size, decryptedCipher);
	printf("Decrypted ciphertext printed to decryptedCipher.txt\n");

	//closing files
	fclose(decryptedCipher);
	//free
	free(input);
	free(output);
	

}//end DecryptDES()

int VerifySignature(void){

	EVP_PKEY_CTX *ctx;
	unsigned char *md, *sig;
	size_t mdlen, siglen;
	EVP_PKEY *verify_key;
	
	//setting up mdlen and siglen
	fseek(cipherText, 0L, SEEK_END);
	mdlen = ftell(cipherText);
	fseek(cipherText, 0L, SEEK_SET);
	//mdlen+=1;
	fseek(signature, 0L, SEEK_END);
	siglen = ftell(signature);
	fseek(signature, 0L, SEEK_SET);
	//siglen+=1;

	//setting up md and sig
	md = (unsigned char *)malloc(mdlen);
	fread(md, 1, mdlen, cipherText);
	
	sig = (unsigned char *)malloc(siglen);
	fread(sig, 1, siglen, signature);
	
	//setting up verify_key
	verify_key = PEM_read_PUBKEY(ourPublicKey, NULL, NULL, NULL);

	/*
	* NB: assumes verify_key, sig, siglen md and mdlen are already set up
	* and that verify_key is an RSA public key
	*/
	ctx = EVP_PKEY_CTX_new(verify_key, NULL);
	if (!ctx){
		printf("ERROR: not ctx\n");
		exit(1);
	}
	if (EVP_PKEY_verify_init(ctx) <= 0){
		printf("ERROR: EVP_PKEY_verify_init(ctx) <= 0\n");
		exit(1);
	}
	if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING) <= 0){
		printf("ERROR: EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING) <= 0\n");
		exit(1);
	}
	if (EVP_PKEY_CTX_set_signature_md(ctx, EVP_sha256()) <= 0){
		printf("ERROR: EVP_PKEY_CTX_set_signature_md(ctx, EVP_sha256()) <= 0\n");
		exit(1);
	}

	//ret == 1 is succes, 0 failure, and < 0 for other error
	int ret;
	ret = EVP_PKEY_verify(ctx, md, mdlen, sig, siglen);
	
	//free
	free(md);
	free(sig);
	
	return ret;

}//end VerifySignature()


#endif
