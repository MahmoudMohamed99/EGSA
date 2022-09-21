#include <VirtualWire.h>
// Receiver.
bool flag =1;
void setup()
{
 Serial.begin(9600);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  
  pinMode(2, OUTPUT); //when HIGH =>> RX
  pinMode(4, OUTPUT); //when LOW =>>  RX
  
 Serial.println("setup");
 vw_setup(2000); // Bits per sec
 vw_rx_start(); // Start the receiver PLL running
}
void loop()
{
  
  if(flag==1){

    //RX
    digitalWrite(8, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(2, LOW);
  }
  else if(flag==0){
    //TX
    digitalWrite(8, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
  }
  
 uint8_t buf[VW_MAX_MESSAGE_LEN];
 uint8_t buflen = VW_MAX_MESSAGE_LEN;
 if (vw_get_message(buf, &buflen)) // Non-blocking
 {
int i;
// Message with a good checksum received, dump HEX
Serial.print("Got: ");
for (i = 0; i < buflen; i++)
{
 Serial.print(buf[i], HEX);
 Serial.print(" ");
}
Serial.println("");

 }
 delay(400);
 flag =!flag;
 
}
