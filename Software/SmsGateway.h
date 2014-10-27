//Implements NetworkGateway
#ifndef SmsGateway_h   
#define SmsGateway_h

#include "NetworkGateway.h"
#include <Arduino.h>

class SmsGateway : public NetworkGateway
{
	private:
		
	public:
		SmsGateway();
		virtual void connectToNetwork();
		virtual bool connected();
		virtual int sendData(String address, String data);
		virtual String reciveData(String address);
		virtual long getTime();
};
#endif