#include "WixelSensorService.h"
#include <SoftwareSerial.h>
#include <arduino.h>

WixelSensorService::WixelSensorService(int RX, int TX)
{
    wixelSerial = new SoftwareSerial(RX, TX); //9, 10); //53, 52); // RX, TX
    wixelSerial->begin(9600);
}

WixelSensorService::WixelSensorService()
{
    delete wixelSerial;
}

int WixelSensorService::getSensorData(int sensorId)
{
    wixelSerial->write(sensorId);
    delay(100);

    int data;
    if (wixelSerial->available())
    {
        data = wixelSerial->read();
    }

    return data;
}

int WixelSensorService::getData()
{
    if(wixelSerial->available())
        return wixelSerial->read();
    return 0;
}