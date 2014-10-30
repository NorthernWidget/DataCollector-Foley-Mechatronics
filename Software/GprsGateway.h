//Implements NetworkGateway
#ifndef GprsGatway_h   
#define GprsGateway_h

#include "NetworkGateway.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

#define IP "89.160.207.212"
#define APN "gprs.is"
#define HOST "Host: sveinnel.com:5000\n"
#define REQUEST "POST /geolog HTTP/1.1\n"
#define ACCEPT "Accept: */*\n"
#define CONTENT "Content-Type: application/json\n" 
#define USERAGENT "User-Agent: curl/7.35.0\n"
#define BODYSTART "{\"date\":\""
#define BODYMID "\",\"temp\":\""
#define BODYEND "\"}"

class GprsGateway : public NetworkGateway,public SoftwareSerial
{
	private:

		bool waitFor(String s);
		void waitTil(String s); 
		void boot();
		String getMessage();

		String apn;
		String ip;


		bool connected;

	public:
		GprsGateway(int rxpin,int txpin);
		virtual bool connectToNetwork();
		virtual bool connected();
		virtual int sendData(String address, String data);
		virtual String reciveData(String &address);
		virtual long getTime();
};
#endif