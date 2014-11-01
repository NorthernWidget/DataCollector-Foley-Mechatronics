//#include "GprsGateway.h"
#include "SerialGSM.h"
#include "SmsGateway.h"
#include "GprsGateway.h"
#include <SoftwareSerial.h>

#include "NetworkGateway.h"

String number;
String message=NULL;
int a;
bool flag = true;

SmsGateway sms(50,51);
SoftwareSerial mySerial(52,53);
GprsGateway gprs(50,51);

void setup(){
Serial.begin(9600);
gprs.connectToNetwork();

gprs.sendData("","{\"date\":\"2014-10-29 23:10\",\"temp\":\"13\"}");
sms.connectToNetwork();
a=sms.sendData("+3548967358","er serverinn hruninn aftur?");
//cell.SendSMS("896-7388","Hallo Sveinn thetta er GeoLog");
gprs.connectToNetwork();

gprs.sendData("","{\"date\":\"2014-10-29 23:10\",\"temp\":\"14\"}");
}

 void loop()
 {	
 	if(flag){ 
		Serial.print("OLLA");
		flag = false;
		}
	message = sms.reciveData(number);
	
	if(message != NULL){
	
 	Serial.println("Number");
 	
	Serial.println(number);
	Serial.println("");
	Serial.println("Message");
	Serial.println(message);
}

 }