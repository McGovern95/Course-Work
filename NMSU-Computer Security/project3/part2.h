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

void DecryptSessionKey(void);
void SignMessage(void);
void EncryptDES(void);

#endif
