/* Implement SHA-1 and produce hash valuee */

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

//1 mega-byte
#define MAX_SIZE 1048576
//Macro for Circular shift
#define CIRC_SHIFT(n, x) (((x) << n) | ((x)>> (32 - n)))
//constant for showing passes
#define SHOW_PASS 0

/* Reads file into unsigned char array and counts characters in file */
unsigned int readFile(unsigned char buffer[]) {
  char ch = 0;
  int i = 0;
  //Keeps reading in characters until it reaches EOF
  while((ch = getchar()) != EOF) {
    //Stores characters into buffer array
    buffer[i] = ch; 
    i++; //i for index
    //error checking if file is too large
    if(i > MAX_SIZE) {
      cout << "ERROR: Input File too large.\n";
      exit(EXIT_FAILURE); //Indicates there was an error and has to quit program
    }
  }//end of while
  buffer[i+1] = 0x80; //sticks the byte at the end of the array
  return i; //returns amount of characters in file
}//end of readFile

/* Calculate the number of blocks */
unsigned int calculateBlocks (unsigned int sizeOfFileInBytes) {
  unsigned int totalBits = (8 * sizeOfFileInBytes) + 1; //calculates total bits
  unsigned int blockCount = (((8 * sizeOfFileInBytes) + 1) / 512) + 1; //calculates block count

  //Checks if an extra block is necessary
  //so theres enough room for the bitcount of the file
  if((totalBits % 512) > 448) {
    blockCount = blockCount + 1; 
  }

  return blockCount;
}

/* Converts character array to packed integer array */
void convertCharArrayToIntArray (unsigned char buffer[], unsigned int message[], unsigned int sizeOfFileInBytes) {
  unsigned char a; //for holding chars from file
  unsigned int packedInt = 0; //for holding the packed 4 characters
  int i = 0, j = 0, count = 1;
  while(i < sizeOfFileInBytes) {
    if(count % 4 == 1) {
      a = buffer[i]; //assigns the character stored at buffer[count] to a
      packedInt += (a << 24);
      message[j] = packedInt;
      i++;
      count++;
    }
    else if (count % 4 == 2) {
      a = buffer[i];
      packedInt += (a << 16);
      message[j] = packedInt;
      i++;
      count++;
    }
    else if (count % 4 == 3) {
      a = buffer[i];
      packedInt += (a << 8);
      message[j] = packedInt;
      i++;
      count++;
    }
    else if (count % 4 == 0) {
      a = buffer[i];
      packedInt += a;
      message[j] = packedInt;
      packedInt = 0; //sets back to 0 for new pass
      i++;
      count++;
      j++; //counter for every 4 characters
    }
  }
  //When it reaches the end
  //appends the extra byte
  if(i == sizeOfFileInBytes) {
    //Stores as 80000000
    if(sizeOfFileInBytes % 4 == 0) {
      packedInt += (0x80 << 24);
      message[j] = packedInt;
    }
    //Stores as 800000
    else if(sizeOfFileInBytes % 4 == 1){ 
      packedInt += (0x80 << 16);
      message[j] = packedInt;
    }
    //Stores as 8000
    else if(sizeOfFileInBytes % 4 == 2) {
      packedInt += (0x80 << 8);
      message[j] = packedInt;

    }
    //Stores as 80
    else if(sizeOfFileInBytes % 4 == 3) {
      packedInt += 0x80;
      message[j] = packedInt;
    }
  }
}//end of converCharArrayToIntArray

/* Adds bit count to last block*/
void addBitCountToLastBlock(unsigned int message [], unsigned int sizeOfFileInBytes, unsigned int blockCount) {
  //Calculates the size of the file in bits
  unsigned sizeOfFileInBits = sizeOfFileInBytes * 8;
  //Finds the index of last block
  int indexOfEndOfLastBlock = (blockCount * 16) - 1;
  //Adds the bit count to the last block
  message[indexOfEndOfLastBlock] += sizeOfFileInBits;
}

/* Computes Message Digest */
void computeMessageDigest(unsigned int message[], unsigned int blockCount) {
  int t = 0, count = 0, i = 0, j = 0;
  //Constants used
  unsigned int h_0 = 0x67452301, h_1 = 0xEFCDAB89, h_2 = 0x98BADCFE, h_3 = 0x10325476, h_4 = 0xC3D2E1F0; //H0 - H4
  unsigned int a, b, c, d, e; //ABCDE
  unsigned int temp = 0, f = 0, k = 0; //TEMP, f(), K
  unsigned int w[80];

  while(count < blockCount) {
    a = h_0, b = h_1, c = h_2, d = h_3, e = h_4; //reassigns a-e to the new values after the first block is calculated
    //Sets W[0]-> [16] to 16 of the packed integers from message[] (16 per block)
    for(i = 0; i < 16; i++) {
      w[i] = message[j];
      j++;
    }
    count++;
    for(t = 0; t <= 79; t++) {
      if(SHOW_PASS) {
	cout << "Pass " << dec <<  t << ":"<<  hex << uppercase  << " " << a << " " <<  b << " " <<  c << " " <<  d << " " <<  e <<  endl;
      }
      /* Assigning the right constants and functions*/
      if(0 <= t && t <= 19) {
	f = (b & c) | ((~b) & d);
	k =  0x5A827999;
      }
      else if(20 <= t && t <= 39) {
	f = (b ^ c ^ d);
	k = 0x6ED9EBA1;
      }
      else if (40 <= t && t <= 59) {
	f = (b & c) | (b & d) | (c & d);
	k = 0x8F1BBCDC;
      }
      else if (60 <= t && t <= 79) {
	f = (b ^ c ^ d);
	k = 0xCA62C1D6;
      }
      //For t = 16 -> 79
      if(t >= 16 && t <= 79) {
	w[t] = (w[t-3] ^ w[t-8] ^ w[t-14] ^ w[t-16]);
	w[t] = CIRC_SHIFT(1, w[t]);
	temp = (CIRC_SHIFT(5, a) + f + e + w[t] + k);
	e = d;
	d = c;
	c = CIRC_SHIFT(30, b);
	b = a;
	a = temp;
      }
      //For t= 0 -> 15
      else {
	temp = (CIRC_SHIFT(5, a) + f + e + w[t] + k);
	e = d;
	d = c;
	c = CIRC_SHIFT(30, b);
	b = a;
	a = temp;
      }
    } //end of t loop
    //Calculates message digest after t passes
    h_0 = (h_0 + a);
    h_1 = (h_1 + b);
    h_2 = (h_2 + c);
    h_3 = (h_3 + d);
    h_4 = (h_4 + e);
  }//end of block loop
  
  cout<< "Message Digest: " << uppercase << hex << h_0 << " " << h_1 << " " << h_2 << " " << h_3 << " " << h_4 << endl;
}

int main () {

  int count = 0, messageSize = 0;
  unsigned char buffer[MAX_SIZE];
  unsigned int blockCount = 0;

  count = readFile(buffer); //sets count to number of characters in file
  blockCount = calculateBlocks(count); //counts number of blocks
  messageSize = blockCount * 16; //calculates size for message array

  unsigned int message[messageSize]; //creates message array
  fill(message, message + messageSize, 0); //fills the message array with 0s

  convertCharArrayToIntArray(buffer, message, count); //converts char to int array
  addBitCountToLastBlock(message, count, blockCount); //add bit count
  computeMessageDigest(message, blockCount); //Computes message digest
} //end main
