#include "WixelSensorService.h"
#include <SoftwareSerial.h>
#include <arduino.h>

WixelSensorService::WixelSensorService()
{
    wixelSerial = new SoftwareSerial(53, 52); // RX, TX
    wixelSerial->begin(9600);
}

String WixelSensorService::getSensorData(int sensorId)
{
    wixelSerial->write(sensorId);
    delay(100);

    String data = "{\"1\":[";
    while (wixelSerial->available())
    {
        data += "{\"T\":\"";
        data += static_cast<String>(wixelSerial->read());
        data += "\"},";
        delay(100);
    }
    data += "]}";

    return data;
}

int WixelSensorService::getData()
{
    if(wixelSerial->available())
        return wixelSerial->read();
    return 0;
}