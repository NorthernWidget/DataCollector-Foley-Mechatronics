#ifndef SensorService_h   
#define SensorService_h
#include <Arduino.h>

class SensorService
{
public:
  // Empty virtual destructor for proper cleanup
  SensorService() {}
  virtual ~SensorService() {}
  virtual int getSensorData(int sensorId) = 0;
  virtual int sendDataToSensor(String data) = 0;
  virtual int setDateTime(long DateTime) = 0;
};

#endif