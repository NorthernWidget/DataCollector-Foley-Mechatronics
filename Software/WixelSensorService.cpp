#include "WixelSensorService.h"
#include <SoftwareSerial.h>
#include <Arduino.h>

WixelSensorService::WixelSensorService(long timeOut)
{
    // wixelSerial = new Serial(19, 18); //9, 10); //53, 52); // RX, TX
    // wixelSerial->begin(9600);
    Serial3.begin(9600);
    TimeOut = timeOut;
}

WixelSensorService::~WixelSensorService()
{
    delete wixelSerial;
}

int WixelSensorService::getSensorData(int sensorId)
{
    // wixelSerial->listen();
    // wixelSerial->write(sensorId);
    //Serial3.write(sensorId);
    // delay(50);

    long startTime = millis();
    int data = 0;
    while (data==0 || (millis() - startTime) > TimeOut)
    {   
         Serial3.write(sensorId);
         delay(100);

        if(Serial3.available()){ 
            data = Serial3.read();
            Serial3.flush();
        }
    }
    data = covertToCelcius(data);
    return data;
}

int WixelSensorService::covertToCelcius(int temp)
{
    return (temp*(4.0/1023)*100)- 50;
}

