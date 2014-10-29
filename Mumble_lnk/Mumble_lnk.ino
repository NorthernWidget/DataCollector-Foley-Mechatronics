#include <SerialGSM.h>
#include <SoftwareSerial.h>
#include <SerialGSM.h>
#include <SoftwareSerial.h>
SerialGSM cell(50,51);
 
void setup()
{ 
  delay(30000); // wait for GSM module
  cell.begin(9600);
}
 
void sendSMS()
{
  cell.Verbose(true); // used for debugging
  cell.Boot(); 
  cell.FwdSMS2Serial();
  cell.Rcpt("+3548656201"); // replace xxxxxxxxx with the recipient's cellular number
  cell.Message("Hello Beggi this is GeoLOG");
  cell.SendSMS();
}
void loop()
{
  int count = 0;
  sendSMS();
  while(count < 60){
    
    Serial.println(60 - count);
    delay(1000);
    count++;
  }
    
  }