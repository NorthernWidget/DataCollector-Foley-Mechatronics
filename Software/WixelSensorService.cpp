#include "WixelSensorService.h"
#include <SoftwareSerial.h>
#include <Arduino.h>

WixelSensorService::WixelSensorService(int RX, int TX)
{
    rx=RX;
    tx=TX;
    // wixelSerial = new Serial(19, 18); //9, 10); //53, 52); // RX, TX
    // wixelSerial->begin(9600);
    Serial3.begin(9600);
}

WixelSensorService::~WixelSensorService()
{
    delete wixelSerial;
}

int WixelSensorService::getSensorData(int sensorId)
{
    // wixelSerial->listen();
    // wixelSerial->write(sensorId);
    Serial3.write(sensorId);
    delay(50);

    int data = 0;
    if (Serial3.available())                //wixelSerial->available())
    {
        // data = wixelSerial->read();
        data = Serial3.read();
    }
    // delete wixelSerial;
    return data;
}

