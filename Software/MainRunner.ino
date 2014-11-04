//#include "GprsGateway.h"
#include "SerialGSM.h"
#include "SmsGateway.h"
#include "GprsGateway.h"
#include <SoftwareSerial.h>

#include "NetworkGateway.h"
#include "WixelSensorService.h"

String number;
String message=NULL;
String sec,mino,kls,day,mon,year;
int a;
int resetPin = 22; 
bool flag = true;
long curnetTime;
long timeOute;
long newTime;


SmsGateway sms(50,51);
GprsGateway gprs(50,51); //= new GprsGateway(50,51);

//WixelSensorService wixelData; //= new WixelSensorService();;

void setup()
{
    pinMode(resetPin, OUTPUT);
    digitalWrite(resetPin, LOW);
    Serial.begin(9600);
    curnetTime = millis();

    


}

void loop()
{  
    if(Serial.available()){ 
        char reader = Serial.read();

        if(reader == '1'){ 
            digitalWrite(resetPin, HIGH);
            gprs.connectToNetwork();
            gprs.sendData("","{\"date\":\"2014-10-29 23:10\",\"temp\":\"1\"}");
            digitalWrite(resetPin, LOW);
            delay(3000);
        }

        if(reader == '2'){ 
            digitalWrite(resetPin, HIGH);
            gprs.connectToNetwork();
            gprs.sendData("","{\"date\":\"2014-10-29 23:10\",\"temp\":\"2\"}");
            digitalWrite(resetPin, LOW);
            delay(3000);

        }

        if(reader == '3'){
            digitalWrite(resetPin, HIGH);
            sms.connectToNetwork();
            sms.sendData("+3548967358","{\"date\":\"2014-10-29 23:10\",\"temp\":\"2\"}");
            digitalWrite(resetPin, LOW);
            delay(3000);            
        }
         if(reader == '4'){
            
            digitalWrite(resetPin, HIGH);
            sms.connectToNetwork();
            message = sms.reciveData(number);
            if(number > 0){ 
                Serial.println("Number");
                Serial.println(number);
                Serial.println("");
                Serial.println("Message");
                Serial.println(message);       
            }
            digitalWrite(resetPin, LOW);
            delay(3000);            
        }
        if(reader == '5')
        {   
            String Time = sms.getTime(1);           
            Serial.println(Time);
            int lent = Time.length();
            sec = Time.substring(lent - 2); 
            mino = Time.substring(lent - 5,2); 
            kls = Time.substring(lent - 8,2); 
            day = Time.substring(lent - 11,2); 
            mon = Time.substring(lent - 14,2); 
            year = Time.substring(lent - 17,2);
            
            second(sec.toInt());
            minute(mino.toInt());
            hour


        }   
}
    // String data;
    // if (Serial.available()) {
    //     data = wixelData.getSensorData(Serial.read());        // request from wixel nr.1 -> send 1 in serial
    //     Serial.print(data);
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
