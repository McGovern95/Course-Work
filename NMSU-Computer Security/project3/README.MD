	#Signature and Validation C program 


 Included Files:
	src: part2.c part2.h part3.c part3.h
	compile scripts: makefile part2.sh part3.sh
	keys: certificate.p12  encrypted_session.key iv.txt privkey.pem 
	      pubkey.pem TApubkey.pem 
	
	

 Instuctions on using this program:
	NOTE: a new iv.txt is randomly generating each time.

	You may either run our scripts to automatically compile and run program, or you can use command line arguements
	Script method:
	1) type make 
	2) type sh part2.sh
	3) type sh part3.sh

	command line arg method:
	 1) type make
	 2) command line syntax:
               for part 2: ./part2 -Plain (plain text file name) -EncryptedSessionKey (session key file name) -ThirdPartyPublic (third party public key file name) -Private (private key file name)
		for part 3: ./part3 -Public (public key file name) -DecryptedSessionKey (decrypted session key file name) -Cipher (cipher file name) -Signature (signature file name)

	   Example command line arguements: 
		./part2 -Plain plain.txt -EncryptedSessionKey encrypted_session.key -ThirdPartyPublic TApubkey.pem -Private privkey.pem
		./part3 -Public pubkey.pem -DecryptedSessionKey decryptedSessionKey.txt -Cipher cipher.txt -Signature signature.txt

Resources: .p12 file generated from http://www.cacert.org/
	   all libaries from https://www.openssl.org/docs/manmaster/man7/evp.html
	   
	

