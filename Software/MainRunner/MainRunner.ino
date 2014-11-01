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
mySerial.begin(9600);
mySerial.println("Sindri");
}

 void loop()
 {
	
message = cell.reciveData(number);
if(message != NULL){
mySerial.listen();
Serial.println("Number");
Serial.println(number);
Serial.println("");
Serial.println("Message");
Serial.println(message);
mySerial.println(message);
}

 }
