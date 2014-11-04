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
		void boot();
		void waitTil(String sx,String sy, String sz);
		String getMessage();
		bool waitFor(String s);
		long curentTime;
		String Time;
		long inTime;
	    long timeOute;

	public:
		SmsGateway(int rxpin,int txpin);
		~SmsGateway();
		bool connectToNetwork();
		bool connected();
		int sendData(String address, String data);
		String reciveData(String &address);
		long getTime();
		String getTime(int i);

	
};
#endif