#ifndef WixelSensorService_h   
#define WixelSensorService_h

#include <Arduino.h>
#include "SensorService.h"
#include <SoftwareSerial.h>

class WixelSensorService : public SensorService
{
public:
  	// Empty virtual destructor for proper cleanup
  	WixelSensorService(int RX, int TX);
  	virtual ~WixelSensorService();
  	int getSensorData(int sensorId);
  	int sendDataToSensor(String data) {return 0;}
  	int setDateTime(long DateTime) {return 0;}

  	

private:
	SoftwareSerial* wixelSerial;
	int rx,tx;

};

#endif