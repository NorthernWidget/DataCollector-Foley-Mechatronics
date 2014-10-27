//Implements NetworkGateway
#ifndef SmsGatway_h   
#define SmsGatway_h

#include "NetworkGateway.h"
#include <arduino.h>

class SmsGatway : public NetworkGateway
{
	private:
		
	public:
		virtual ~SmsGatway() {}
		virtual void connectToNetwork();
		virtual bool connected();
		virtual int sendData(String address, String data);
		virtual String reciveData(String address);
		virtual long getTime();
};
#endif