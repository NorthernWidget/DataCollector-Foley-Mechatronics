#include "GprsGateway.h"
#include <SoftwareSerial.h>

GprsGateway::GprsGateway(int rxpin,int txpin):SoftwareSerial(rxpin,txpin), NetworkGateway()
{	
	apn = APN;
	ip = IP;
}


bool GprsGateway::connectToNetwork()
{
	 this->begin(9600);
	 this->boot();
	 this->println("AT+CGATT=1");
	 if(!waitFor("OK"))
	 	return false;
	 this->println("AT+CGDCONT=1,\"IP\",\""+apn+"\"");
	 if(!waitFor("OK"))
	 	return false;
	 this->println("AT+CGACT=1,1");
 	 if(!waitFor("OK"))
 	 	return false;
 	 this->println("AT+SDATACONF=1,\"TCP\",\""+ip+"\",5000");
  	 if(!waitFor("OK")) 
  	 	return false;
  	this->println("AT+SDATASTART=1,1");
  	if(!waitFor("OK")) 
  	 	return false;
  	connected = true;
  	return true; 

}

bool GprsGateway::connected()
{
	return connected;
}

int GprsGateway::sendData(String address, String data)
{
	data = REQUEST + HOST + CONTENT + ENDER + data;

	if(!connected)
		{
		connectToNetwork();	
		}

	 while (1) {
	    Serial.println("Checking socket status:");
	    this->println("AT+SDATASTATUS=1"); // we'll get back SOCKSTATUS and then OK
	    String sockstat = getMessage();
	    if(!waitFor("OK")) 
	    if (sockstat=="+SOCKSTATUS:  1,0,0104,0,0,0") {
	      Serial.println("Not connected yet. Waiting 1 second and trying again.");
	      delay(1000);
	    }
	    else if (sockstat=="+SOCKSTATUS:  1,1,0102,0,0,0") {
	      Serial.println("Socket connected");
	      break;
	    }
	    else {
	      Serial.println("We didn't expect that.");
	      return -1;
    	}
  	}

  	 int packetLength = data.length();  	

  	Serial.println("Sending HTTP packet...");
    this->print("AT+SDATATSEND=1,"+String(packetLength)+"\r");
    waitFor('>'); 
    this->print(data); //SIZE 2
  	this->write(26); // ctrl+z character: send the packet
  	waitFor("OK");

  	this->println("AT+CGATT=0");
  	waitFor("OK");
  	connected = false;

  	return 1;
}

String GprsGateway::reciveData(String &address)
{
	return "";
}

long GprsGateway::getTime()
{
	return -1;
}
bool GprsGateway::waitFor(String s)
{
	String message=getMessage();
  	if (message != s) {
    Serial.println("Wait, that's not what we were expecting. We wanted \""+s+"\"");
    connected = false;
    return false;
  }
  delay(100);
  return true;
}
void GprsGateway::waitTil(String s)
{

}
void GprsGateway::boot()
{
	delay(15000);
}
String GprsGateway::getMessage() {
  String s="";
  while(1) {
    if(cell.available()>0) {
      s = s+(char)cell.read();
      if (s.length()>1 && s[s.length()-2]=='\r' && s[s.length()-1]=='\n') { // if last 2 chars are \r\n
        if (s==" \r\n" || s=="\r\n") { // skip these, move on
          s="";
        }
        else { // we have a message!
          Serial.println(s.substring(0,s.length()-2));
          return s.substring(0,s.length()-2);
        }
      }
    }
  }
}