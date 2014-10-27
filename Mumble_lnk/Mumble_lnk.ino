#include <SerialGSM.h>
#include <SoftwareSerial.h>

SerialGSM cell(50,51);// RX, TX
SoftwareSerial mySerial(52, 53); // RX, TX
String Message;

int LedPin = 30;

  
boolean sendonce=true;
void setup(){  
  Serial.begin(9600);
  cell.begin(9600);
  cell.Verbose(true);
  cell.Boot();
  cell.DeleteAllSMS();
  cell.FwdSMS2Serial();
  Serial.println("Sindri");
  pinMode(LedPin, OUTPUT);
  digitalWrite(LedPin, LOW);
 }


void loop(){
  if (cell.ReceiveSMS()){
	 Serial.print("Sender: ");
	 Serial.println(cell.Sender());
	 Serial.print("message: ");
          Message = cell.Message();
	 Serial.println(Message);
         cell.DeleteAllSMS();
  }
    if(Message == "L1"){
      digitalWrite(LedPin, HIGH); 

    }

  Message = "";

}
