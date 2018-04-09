	#DES-CBC Encryption/Decryption program



Included files: 

SRC: project2.cpp desfunct.cpp desfunct.h makefile

	instructions on using this program:

	1) compile with 'make'
	2) type command ./project2 to start program
	3) enter 1 to generate key and iv. enter 0 to provide your own
	   -if 1 was entered then skip to next step, if 0 then it'll prompt for you to enter the key and then the iv file names
	4) enter either e or d to encrypt or decrypt  (note that if you're decrypting, you need to input the same key and iv that you used to encrypt it otherwise it'll fail and you'll get gibberish in your decrypted text.)
	5) if e then enter the name of the plaintext file that you'll like to encrypt, if decrypting then enter the cipertext that you've encrypted before. 
	6) the encrypted text will be in cipher.txt, decrypted text can be found decrypt.txt 