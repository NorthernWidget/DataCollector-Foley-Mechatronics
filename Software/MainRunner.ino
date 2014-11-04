//#include "GprsGateway.h"
#include "SerialGSM.h"
#include "SmsGateway.h"
#include "GprsGateway.h"

//#include "NetworkGateway.h"
#include "WixelSensorService.h"
#include "Time.h"

String number;
String message=NULL;
String sec,mino,kls,da,mon,ye;
int a;
int resetPin = 22; 
bool flag = true;
long curnetTime;
long timeOute;
long newTime;
String timeDayt;
int data1, data2, data3;

SmsGateway sms(50,51);
GprsGateway gprs(50,51); //= new GprsGateway(50,51);

WixelSensorService wixelData(53,52); //= new WixelSensorService();;

void setup()
{
    pinMode(resetPin, OUTPUT);
    digitalWrite(resetPin, LOW);
    Serial.begin(9600);
    curnetTime = millis();

    


}

void loop()
{  
    if(Serial.available())
    { 
        char reader = Serial.read();

        if(reader == '1')
        { 
            delay(100);
            data1 = wixelData.getSensorData(1);
            Serial.println(data1);
        }
        if(reader == '2')
        { 
            delay(100);
            data2 = wixelData.getSensorData(2);        // request from wixel nr.X -> send X in serial
            Serial.println(data2);
        }
        if(reader == '3')
        { 
            delay(100); 
            data3 = wixelData.getSensorData(3);
            Serial.println(data3);

            // reader = '2';
        }

        if(reader == 'a')
        { 
            digitalWrite(resetPin, HIGH);
            gprs.connectToNetwork();
            gprs.sendData("","{\"date\":\""+timeDayt+"\",\"temp\":\""+(String)data1+"\"}");
            delay(1000);
            digitalWrite(resetPin, LOW);
            delay(1000);
        }

        if(reader == 't')
        {
           timeDayt=(String)year()+"/"+(String)month()+"/"+(String)day()+","+(String)hour()+":"+(String)minute()+":"+(String)second();

            // digitalWrite(resetPin, HIGH);
            // sms.connectToNetwork();
            // sms.sendData("+3548967358","{\"date\":\"2014-10-29 23:10\",\"temp\":\"2\"}");
            // digitalWrite(resetPin, LOW);
            // delay(3000);            
        }
        if(reader == 's')
        {
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
            delay(1000);
            digitalWrite(resetPin, LOW);
            delay(1000);            
        }
        
        if(reader == '5')
        {   
            // digitalWrite(resetPin, HIGH);
            String Time = sms.getTime(1);           
            Serial.println(Time);
            int lent = Time.length();
            sec = Time.substring(lent - 2,lent);
            Serial.println(sec); 
            mino = Time.substring(lent - 5,lent-3); 
            Serial.println(mino);
            kls = Time.substring(lent - 8,lent-6); 
            Serial.println(kls);
            da = Time.substring(lent - 11,lent-9); 
            Serial.println(da);
            mon = Time.substring(lent - 14,lent-12); 
            Serial.println(mon);
            ye = Time.substring(lent - 17,lent-15);
            Serial.println(ye);

            long h = (long)kls.toInt();
            long m = (long)mino.toInt();
            long s = (long)sec.toInt();
            long d = (long)da.toInt();
            long mo = (long)mon.toInt();
            long y = (long)ye.toInt();

            setTime(h,m,s,d,mo,y);
            Serial.println((String)year()+"/"+(String)month()+"/"+(String)day()+","+(String)hour()+":"+(String)minute()+":"+(String)second());
            // digitalWrite(resetPin, LOW);
            // delay(3000);
        }   
    }
    
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
