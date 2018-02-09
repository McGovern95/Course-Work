#include <stdint.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int frequency[26]; 

int main(){
      
	 ifstream file("ciphertext.txt");
	 string s;
     getline(file, s, (char) file.eof());

     cout << s << endl;
     //counts the frequency of letters
     for(int i=0;i<s.length();i++){
     	if (s.at(i) == 'A')
     		{frequency[0]++;}
     	if (s.at(i) == 'B')
     		{frequency[1]++;}
     	if (s.at(i) == 'C')
     		{frequency[2]++;}
     	if (s.at(i) == 'D')
     		{frequency[3]++;}
     	if (s.at(i) == 'E')
     		{frequency[4]++;}
     	if (s.at(i) == 'F')
     		{frequency[5]++;}
     	if (s.at(i) == 'G')
     		{frequency[6]++;}
     	if (s.at(i) == 'H')
     		{frequency[7]++;}
     	if (s.at(i) == 'I')
     		{frequency[8]++;}
     	if (s.at(i) == 'J')
     		{frequency[9]++;}
     	if (s.at(i) == 'K')
     		{frequency[10]++;}
     	if (s.at(i) == 'L')
     		{frequency[11]++;}
     	if (s.at(i) == 'M')
     		{frequency[12]++;}
     	if (s.at(i) == 'N')
     		{frequency[13]++;}
     	if (s.at(i) == 'O')
     		{frequency[14]++;}
     	if (s.at(i) == 'P')
     		{frequency[15]++;}
     	if (s.at(i) == 'Q')
     		{frequency[16]++;}
     	if (s.at(i) == 'R')
     		{frequency[17]++;}
     	if (s.at(i) == 'S')
     		{frequency[18]++;}
     	if (s.at(i) == 'T')
     		{frequency[19]++;}
     	if (s.at(i) == 'U')
     		{frequency[20]++;}
     	if (s.at(i) == 'V')
     		{frequency[21]++;}
     	if (s.at(i) == 'W')
     		{frequency[22]++;}
     	if (s.at(i) == 'X')
     		{frequency[23]++;}
     	if (s.at(i) == 'Y')
     		{frequency[24]++;}
     	if (s.at(i) == 'Z')
     		{frequency[25]++;}
     	
     }//end for
     //prints the frequency of letters
     for(int j = 0;j<26;j++){
     	cout << (char)('A' + j) << ": ";
     	cout << frequency[j] << "" <<endl;
     }




    

    
 
}//end main