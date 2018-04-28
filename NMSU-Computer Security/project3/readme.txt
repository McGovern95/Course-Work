To compile both part2 and part3:
	make
To compile only one part:
	make part2
or
	make part3

Example command to run part2:
	./part2 -Plain plain.txt -EncryptedSessionKey encrypted_session.key -ThirdPartyPublic TApubkey.pem -Private privkey.pem
Example command to run part3: 
	./part3 -Public pubkey.pem -DecryptedSessionKey decryptedSessionKey.txt -Cipher cipher.txt -Signature signature.txt
