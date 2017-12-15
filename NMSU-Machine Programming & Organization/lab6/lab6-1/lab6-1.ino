extern byte tempV1;
extern byte tempV2;

extern "C"{
void setupTherm();
void readTherm();
}



void setup() {
// put your setup code here, to run once:
Serial.begin(9600);//initialize serial window
setupTherm();//initialize therm calls our assembly code

}

void loop() {
// put your main code here, to run repeatedly:
delay(2000);
readTherm();

Serial.print("Integer degree: ");
Serial.println(tempV1, DEC);

Serial.print("Fractional degree: ");
Serial.println(tempV2, DEC);

  
 int ftempV1 = ((tempV1 * 1.8 )+ 32) * 10;
 double ftempV2 = (((double)tempV2/256) * 1.8 * 10);

//Serial.print("ftempV2 after the conversion: ");
//Serial.println(ftempV2);
int fahren = ftempV1 + ftempV2;
Serial.print("Tenth-degrees Fahrenheit: ");
Serial.println(fahren, DEC);



}
