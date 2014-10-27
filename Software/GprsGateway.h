//Implements NetworkGateway
#ifndef GprsGatway_h   
#define GprsGateway_h

#include "NetworkGateway.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

class GprsGateway : public NetworkGateway
{
	private:
		
	public:
		GprsGateway(int rxpin,int txpin);
		virtual void connectToNetwork();
		virtual bool connected();
		virtual int sendData(String address, String data);
		virtual String reciveData(String address);
		virtual long getTime();
};
#endif