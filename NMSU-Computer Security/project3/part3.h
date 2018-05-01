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
//unsigned char ivr[8];

void DecryptDES(void);
int VerifySignature(void);

void DecryptDES(void){

	unsigned char *output, *input, *dkey, *buffer;
	size_t size;
	
	fseek(cipherText, 0, SEEK_END);
	size = ftell(cipherText);
	fseek(cipherText, 0, SEEK_SET);
	
	//malloc the pointers
	input = (unsigned char *)malloc(size);
	output = (unsigned char *)malloc(size);
	dkey = (unsigned char *)malloc(8);
	buffer =  (unsigned char *)malloc(8);

	//read contents of cipherText to input
	fread(input, 1, size, cipherText);
    //reading in key
	fread(dkey,1,8,decryptedSessionKey);

	DES_cblock key = {dkey[0],dkey[1],dkey[2],dkey[3],dkey[4],dkey[5],dkey[6],dkey[7]};
	//reading iv
	FILE * ivkey;
	ivkey = fopen("iv.txt","rb");
	if(!ivkey){printf("no iv file in dir, exiting \n");exit(0);}
	fread(buffer,1,8,ivkey);
	DES_cblock iv = {buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7]};//random iv

    //des stuff
	DES_key_schedule schedule;
	DES_set_odd_parity(&key);
	DES_set_key_checked(&key, &schedule);
	DES_ncbc_encrypt(input, output, size, &schedule, &iv, DES_DECRYPT);

	//write out to decryptedCipher.txt
	FILE *decryptedCipher = fopen("decryptedCipher.txt", "wb");
	//fprintf(decryptedSessionKey, "%x", out);
	fwrite(output, 1, size, decryptedCipher);
	printf("Decrypted ciphertext printed to decryptedCipher.txt\n");
	
	//closing files
	fclose(decryptedCipher);
	fclose(ivkey);
	//free
	free(input);
	free(output);
	free(dkey);
	free(buffer);
	
}//end DecryptDES()

int VerifySignature(void){

	EVP_PKEY_CTX *ctx;
	unsigned char *md, *sig;
	size_t mdlen=32, siglen;
	EVP_PKEY *verify_key;
	
	//setting up mdlen and siglen
	fseek(cipherText, 0L, SEEK_SET);

	fseek(signature, 0, SEEK_END);
	siglen = ftell(signature);
	fseek(signature, 0, SEEK_SET);
	

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
	ret = EVP_PKEY_verify(ctx, sig, siglen, md, mdlen);
	
	//free
	free(md);
	free(sig);
	
	return ret;

}//end VerifySignature()


#endif
