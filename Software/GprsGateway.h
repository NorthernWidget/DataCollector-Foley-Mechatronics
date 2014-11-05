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

class GprsGateway : public NetworkGateway//,public SoftwareSerial
{
	private:

		bool waitFor(char c);
		bool waitFor(String s);
		void waitTil(String sx, String sy, String sz); 
		void boot();
		String getMessage();
		int checkSocketString(String s);
		int nthIndexOf(int n, char c, String s);
		int socketStringSlice(int n, String s);

		String apn;
		String ip;
		String host;
		String request;
		String Accept; 
		String content;
		String useragent;
		String body;
		String ender;
		String Time;
		long inTime;
	    long timeOut;

		bool con;
		bool cont;

	public:
		GprsGateway(long timeout);
		bool connectToNetwork();
		bool connected();
		int sendData(String address, String data);
		String reciveData(String &address);
		long getTime();
};
#endif