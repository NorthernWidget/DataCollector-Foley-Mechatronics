//#include "GprsGateway.h"
#include "SmsGateway.h"
#include <SoftwareSerial.h>
#include <SerialGSM.h>

String number;
String message=NULL;


SmsGateway cell(50,51);
SoftwareSerial mySerial(52,53);


void setup(){
Serial.begin(9600);
cell.connectToNetwork();
}

 void loop()
 {
	
message = cell.reciveData(number);
if(message != NULL){
//Serial.listen();
Serial.println("Number");
Serial.println(number);
Serial.println("");
Serial.println("Message");
Serial.println(message);
}

 }