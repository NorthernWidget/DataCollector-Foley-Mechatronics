#include "SmsGateway.h"
#include <SoftwareSerial.h>

SmsGateway::SmsGateway(int rxpin,int txpin):SerialGSM(rxpin,txpin)
{	
	  
	
}

SmsGateway::~SmsGateway()
{
	//delete cell;

}

void SmsGateway::connectToNetwork()
{

}

bool SmsGateway::connected()
{
	return false;
}

int SmsGateway::sendData(String address, String data)
{
	return -1;
}

String SmsGateway::reciveData(String &address)
{	
	if(this->ReceiveSMS()){ 
		String Message = this->Message();
		address = this->Sender();
		this->DeleteAllSMS();
		Serial.println(Message);
		return Message;
	}
	else
	return "";
}

long SmsGateway::getTime()
{
	return -1;
}
