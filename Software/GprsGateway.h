//Implements NetworkGateway
#ifndef GprsGatway_h   
#define GprsGateway_h

#include <arduino.h>

class GprsGateway : public NetworkGateway
{
	private:
		
	public:
		virtual GprsGateway() {}
		virtual ~GprsGateway() {}
		virtual void connectToNetwork();
		virtual bool connected();
		virtual int sendData(String address, String data);
		virtual String reciveData(String address);
		virtual long getTime();
};