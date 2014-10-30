//#include "GprsGateway.h"
#include "SerialGSM.h"
#include "SmsGateway.h"
#include "GprsGateway.h"
#include <SoftwareSerial.h>

#include "NetworkGateway.h"

String number;
String message=NULL;
int a;

SmsGateway sms(50,51);
SoftwareSerial mySerial(52,53);


void setup(){
Serial.begin(9600);
sms.connectToNetwork();
a=sms.sendData("+3548967358","Hallo Sveinn theta er GeoLog");
//cell.SendSMS("896-7388","Hallo Sveinn thetta er GeoLog");

}

 void loop()
 {
	
message = sms.reciveData(number);
if(message != NULL){
//Serial.listen();
Serial.println("Number");
Serial.println(number);
Serial.println("");
Serial.println("Message");
Serial.println(message);
}

 }