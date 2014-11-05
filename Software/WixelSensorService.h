#ifndef WixelSensorService_h   
#define WixelSensorService_h

#include <Arduino.h>
#include "SensorService.h"
#include <SoftwareSerial.h>

class WixelSensorService : public SensorService
{
public:
    // Empty virtual destructor for proper cleanup
   WixelSensorService(long TimeOut);
   virtual ~WixelSensorService();
   int getSensorData(int sensorId);
   int sendDataToSensor(String data) {return 0;}
   int setDateTime(long DateTime) {return 0;}

private:
    int covertToCelcius(int temp);

  

private:
    SoftwareSerial* wixelSerial;
    int rx,tx;
    long TimeOut;

};

#endif