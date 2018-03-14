//extern byte val;
//extern byte width;
//extern byte ascii;

//extern "C" { 
///  void decode_morse();
//}
extern byte val, width, ascii, times;
extern "C" void GoAggies(void);
extern "C" void decode_morse();

//
// function to read a 2-digit decimal value from user
//
byte read2DigitValue()
{
  byte inch; int val;
  Serial.println("Enter a 2-digit decimal value:");
  while (!Serial.available()) delay(100);
  inch = Serial.read();
  val = (inch - '0') * 10;
  while (!Serial.available()) delay(100);
  inch = Serial.read();
  val += (inch - '0');
  Serial.print("The value entered is ");
  Serial.println(val,DEC);
  return (byte) val;
}

void flashGoAggies() 
{
  times = read2DigitValue();
  GoAggies();
  
}
void decodeMorse(const String & string, char message[])
{
  // Write your code below.
  // string contains the input binary string separated by single spaces
  // message contains the decoded English characters and numbers    
  //You will call the assembly function decode_morse()

  
   
  
   byte b = 0;
   byte e = 0;
   int count = 0;

   while(string[e] != '\0'){


    while(!isspace(string[e])&& string[e] != '\0'){
       e++;
    }
     
    width = e - b;
    val = 0;


    while( b < e){
       val <<=1;
       if(string[b] == '1'){
            val = val|1;
       }
       b++;
    }
     
   decode_morse();
   message[count] = ascii;
   count++;
   Serial.println(val);
   b++;
   e++;
    
   }

   
  
}



void decodeMorse() 
{
  Serial.println("Input a Morse code string (separate the code for characters by a space):");

  while (!Serial.available()) delay(100);
  String string = Serial.readString();

  Serial.print("The Morse code string is: ");
  Serial.println(string);

  //string = "1000 100 0"; // "01 1000";
  char message[100];

  decodeMorse(string, message);

  if(strlen(message) > 0) {
    Serial.print("The decoded message is: ");
    Serial.println(message);
  } else {
    Serial.print("Failure in decoding the input Morse code\n");
  }  
}

void setup() {
  //
  // Initialize serial communications
  //
  Serial.begin(9600);

  //flashGoAggies();

  decodeMorse();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(20000); // 20,000 millisecs == 20 seconds
  Serial.println("*");
}
