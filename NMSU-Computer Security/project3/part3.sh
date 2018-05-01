#! /bin/bash

make part3
./part3 -Public pubkey.pem -DecryptedSessionKey decryptedSessionKey.txt -Cipher cipher.txt -Signature signature.txt
