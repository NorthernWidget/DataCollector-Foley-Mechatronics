
#ifndef SensorService_h   
#define SensorService_h
#include <arduino.h>

class SensorService
{
public:
  // Empty virtual destructor for proper cleanup
  virtual SensorService() {}
  virtual ~SensorService() {}
  virtual String getSensorData(int sensorId);
  virtual int sendDataToSensor(String data);
  virtual int setDateTime(long DateTime);
};
