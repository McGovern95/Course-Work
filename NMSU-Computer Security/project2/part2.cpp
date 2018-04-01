#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>

#include "desfunct.h"
using namespace std;

int main(){

	static FILE *plaintext, *ciphertext, *keyfile;
	unsigned long size;
	short int pad;

    int choice;
    printf("please enter a 1 or 0 if you wanna generate your own key or provide your own \n");
    cin >> choice;
    if(choice != 0 && choice !=1){
    	printf("please enter a 1 or 0 \n");
        return 1;
    }
      if(choice == 1){
         printf("please specify the key file name you want (.key): \n");
         char* temp;
         cin >> temp;
         keyfile = fopen(temp,"wb");
         if(!keyfile){
         	printf("error creating file");
            return 1;
         }

        short int bytes_written;
		unsigned char* deskey = (unsigned char*) malloc(8*sizeof(char));
		//seed for random generator
		unsigned int seed = (unsigned int)time(NULL);
		srand (seed);

		keyGenerator(deskey);
		bytes_written = fwrite(deskey, 1, 8, keyfile);

		fclose(keyfile);
   } //end key generator code 
   
    else if(choice == 0){
        printf("what is your key? (please have it be 8 bytes long) \n");
        char* temp;
        cin >> temp;
        short int bytes_read;

		unsigned char* deskey = (unsigned char*) malloc(8*sizeof(char));
		bytes_read = fread(deskey, sizeof(unsigned char), 8, keyfile);
		if (bytes_read != 8) {
			printf("Key needs to be 8 bytes");
			fclose(keyfile);
			return 1;
		}


    	
    } 
    




}//end main();