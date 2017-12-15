
//
// Assembly functions/global variables 
//
extern "C" {
  
   void initializePanel();
   void operatePanel();
   
   void control();
   void resetPanel();
   void returnPanel();   
   //int  queryPanel(byte lightVals[]);
   void parkPanel();
  
   byte readAD(byte);
   void switch2();

   void moveWest();
   byte l, r, i = 0, light_Array[25];
   int parkFlag = 0; 
   
}



//
// If there is any serial input, read it into the
// given array; the array MUST be at least 32 chars long
// - returns true if a string is read in, false otherwise
// (note: 9600baud (bits per second) is slow so we need
//  to have delays so that we don't go too fast)
//
boolean readUserCommand(char cmdString[])
{
   if (!Serial.available())
      return false;
   delayMicroseconds(5000); // allow serial to catch up
   int i=0;
   while (i < 31) {
      cmdString[i++] = Serial.read();
      delayMicroseconds(1000);
      if (!Serial.available())
         break; // quit when no more input
   }
   cmdString[i] = '\0'; // null-terminate the string
   while (Serial.available()) {
      Serial.read(); // flush any remain input (more than 31 chars)
      delayMicroseconds(1000);
   }
   return true;
}

//
// Code that uses the functions
//
void setup()
{ 
   Serial.begin(9600);
   
   control();
   initializePanel();

   //interrupt code setup
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0
    OCR1A = 46872;// 3 seconds 
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10);  
    TIMSK1 |= (1 << OCIE1A);
   
}

ISR(TIMER1_COMPA_vect){

  //code for light reading and storing into an array
  //also works as our query code 
   l = readAD(5);
   r = readAD(2);

   //ISR 
   if(i < 25){
    
    light_Array[i] = l + r;
    i++;
   
   } else {
    
    i = 0;
    light_Array[i] = l + r;
    i++; 
    
   }//end if structure
    
    //used for testing to see if light works 
    //Serial.print("light Array = ");
    //Serial.println(light_Array[i-1], DEC);
}//end ISR
  

//
// In order to process user command AND operate the
// solar panel, the loop function needs to poll for
// user input and then invoke "operatePanel" to allow
// the panel operation code to do what it needs to 
// for ONE STEP. You should not do a continuous loop
// in your assembly code, but just cycle through
// checking everything you need to one time, and then
// returning back and allowing the loop function here
// continue.
//
void loop()
{
   
   char cmd[32];

   delayMicroseconds(100); // no need to go too fast

   l = readAD(5);
   r = readAD(2);

   delay(250);//makes the mortor move slower 
    
   if (l > r && parkFlag == 0 ){
      if (l-r > 2){
          moveWest(); 
      }
      if (l < 4 && r < 4){
          parkFlag = 1;
         
      } else { 
          parkFlag = 0; 
      }
   }//end if nest  
   
   switch2();
   
   cmd[0] = '\0'; // reset string to empty
   if (readUserCommand(cmd)) {
      // this if statement just shows that command strings
      // are being read; it serves no other useful purpose
      // and can be deleted or commented out
      Serial.print("User command is (");
      Serial.print(cmd);
      Serial.println(")");
   }
   // The conditions below recognize each individual
   // command string; all they do now is print, but you
   // will need to add code to do the proper actions
   if (!strcmp(cmd,"reset")) {
      Serial.println("Do reset!");
      memset(light_Array, 0, 25);//resets the array 
      parkFlag = 0;
      resetPanel();
   } else if (!strcmp(cmd, "return")){
      Serial.println("Do return!");
      parkFlag = 1;
      returnPanel();
   } else if (!strcmp(cmd,"park")) {
      Serial.println("Do park!");
      //if parkFlag is set to 1, does nothing, otherwise it 
      //does what park is supposed to do 
      parkFlag = 1;      
   } else if (!strcmp(cmd,"query")) {
      Serial.println("Do query!");
      for(int i = 0; i < 25; i++){
         Serial.print(light_Array[i]);
         Serial.print(", ");
      }//end for
      memset(light_Array, 0, 25);//resets the array   
   }//end query else if
}


