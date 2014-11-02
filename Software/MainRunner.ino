//#include "GprsGateway.h"
#include "SerialGSM.h"
#include "SmsGateway.h"
#include "GprsGateway.h"
#include <SoftwareSerial.h>

#include "NetworkGateway.h"
#include "WixelSensorService.h"

String number;
String message=NULL;
int a;
bool flag = true;

SmsGateway* sms = new SmsGateway(50,51);
GprsGateway* gprs = new GprsGateway(50,51);

WixelSensorService* wixelData = new WixelSensorService();

void setup()
{
    Serial.begin(9600);


    /*
    gprs->connectToNetwork();

    gprs->sendData("","{\"date\":\"2014-10-29 23:10\",\"temp\":\"13\"}");
    sms->connectToNetwork();
    a=sms->sendData("+3546593512","er serverinn hruninn aftur?");
    //cell.SendSMS("896-7388","Hallo Sveinn thetta er GeoLog");
    gprs->connectToNetwork();

    gprs->sendData("","{\"date\":\"2014-10-29 23:10\",\"temp\":\"14\"}");
    
    delete sms;
    delete gprs;
    */
    //Serial.begin(9600);
    //wixelSerial->begin(9600);
}

void loop()
{  
    //Serial.print(static_cast<String>(wixelData->getData()) + " ");
    
    String data;
    if (Serial.available()) {
        data = wixelData->getSensorData(Serial.read());        // request from wixel nr.1 -> send 1 in serial
        Serial.print(data);
    }
    
    //Serial.print(data);
    /*
    if (wixelSerial->available())
    {
        Serial.print(static_cast<String>(wixelSerial->read()) + " ");
    }
    if (Serial.available())
        wixelSerial->write(Serial.read());
    delay(100);
    */
    /*
    if(flag)
    { 
        Serial.print("OLLA");
        flag = false;
    }
    message = sms.reciveData(number);
    
    if(message != NULL)
    {
        Serial.println("Number");
    
        Serial.println(number);
        Serial.println("");
        Serial.println("Message");
        Serial.println(message);
    }
    */
}