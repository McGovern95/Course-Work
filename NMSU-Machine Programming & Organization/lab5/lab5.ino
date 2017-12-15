
//
// Declare the things that exist in our assembly code
//
extern "C" { 
  void display_symbol();
  void display_one();
}

extern byte symbol1, symbol2, symbol3, symbol4, symbolBit;

//
// Arduino-required setup function (called once)
//
void setup()
{
  //
  // Initialize serial communications (for loop() function)
  //
  Serial.begin(9600);

  while (!Serial.available()) delay(100);
  String string = Serial.readString();

   symbol1 = string[0];
   display_one();


  while (!Serial.available()) delay(100);
      string = Serial.readString();

  

  int i = 0;
  int j = 1;
  int k = 2;
  int l = 3;

  while(true){

    if(string[i] == '\0'){
        i = 0;
        symbol1 = string[i];
        i++;
  }else{
       symbol1 = string[i];
       i++; 
  }
       if(string[j] == '\0'){
        j = 0;
        symbol2 = string[j];
        j++;
  }else{
       symbol2 = string[j];
       j++; 
  }
    if(string[k] == '\0'){
        k = 0;
        symbol3 = string[k];
        k++;
  }else{
       symbol3 = string[k];
       k++; 
  }
    if(string[l] == '\0'){
        l = 0;
        symbol4 = string[l];
        l++;
  }else{
       symbol4 = string[l];
        l++; 
  }

  display_symbol();
    delay(500);
    
 }//end while


 

}

//
// Arduino-required loop function (called infinitely)
//
void loop()
{
  delay(2000); // 2,000 millisecs == 2 seconds
  Serial.println("*"); // debug output just to show we got here
}

