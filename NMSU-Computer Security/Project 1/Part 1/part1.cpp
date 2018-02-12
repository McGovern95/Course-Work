#include <stdint.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int frequency[26][2]; 
int key[] = {'E','T','A','O','I','N','S','H','R','D','L','C','U','M','W','F','G','Y','P',
     'B','V','K','J','X','Q','Z'};

int main(){
      
	 ifstream file("ciphertext.txt");
	 string s;
     getline(file, s, (char) file.eof());

     cout << s << endl;

     for(int i=0; i<26;i++){
          frequency[i][1] = 'A' + i;

     }

     //counts the frequency of letters
     //
     for(int i=0;i<s.length();i++){
     	if (s.at(i) == 'A')
     		{frequency[0][0]++;}
     	if (s.at(i) == 'B')
     		{frequency[1][0]++;}
     	if (s.at(i) == 'C')
     		{frequency[2][0]++;}
     	if (s.at(i) == 'D')
     		{frequency[3][0]++;}
     	if (s.at(i) == 'E')
     		{frequency[4][0]++;}
     	if (s.at(i) == 'F')
     		{frequency[5][0]++;}
     	if (s.at(i) == 'G')
     		{frequency[6][0]++;}
     	if (s.at(i) == 'H')
     		{frequency[7][0]++;}
     	if (s.at(i) == 'I')
     		{frequency[8][0]++;}
     	if (s.at(i) == 'J')
     		{frequency[9][0]++;}
     	if (s.at(i) == 'K')
     		{frequency[10][0]++;}
     	if (s.at(i) == 'L')
     		{frequency[11][0]++;}
     	if (s.at(i) == 'M')
     		{frequency[12][0]++;}
     	if (s.at(i) == 'N')
     		{frequency[13][0]++;}
     	if (s.at(i) == 'O')
     		{frequency[14][0]++;}
     	if (s.at(i) == 'P')
     		{frequency[15][0]++;}
     	if (s.at(i) == 'Q')
     		{frequency[16][0]++;}
     	if (s.at(i) == 'R')
     		{frequency[17][0]++;}
     	if (s.at(i) == 'S')
     		{frequency[18][0]++;}
     	if (s.at(i) == 'T')
     		{frequency[19][0]++;}
     	if (s.at(i) == 'U')
     		{frequency[20][0]++;}
     	if (s.at(i) == 'V')
     		{frequency[21][0]++;}
     	if (s.at(i) == 'W')
     		{frequency[22][0]++;}
     	if (s.at(i) == 'X')
     		{frequency[23][0]++;}
     	if (s.at(i) == 'Y')
     		{frequency[24][0]++;}
     	if (s.at(i) == 'Z')
     		{frequency[25][0]++;}
     	
     }//end for
     //prints the frequency of letters
     /*for(int j = 0;j<26;j++){
     	cout << (char)('A' + j) << ": ";
     	cout << frequency[j] << "" <<endl;
     }*/




    

    
 
}//end main