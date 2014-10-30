//Implements NetworkGateway
#ifndef SmsGateway_h   
#define SmsGateway_h

#include "NetworkGateway.h"
#include "Arduino.h"
#include "SerialGSM.h"
#include <SoftwareSerial.h>

class NetworkGateway;
class SmsGateway : public virtual NetworkGateway , public SerialGSM
{
	
	private:
		// void* cell;


	public:
		SmsGateway(int rxpin,int txpin);
		~SmsGateway();
		bool connectToNetwork();
		bool connected();
		int sendData(String address, String data);
		String reciveData(String &address);
		long getTime();

	
};
#endif