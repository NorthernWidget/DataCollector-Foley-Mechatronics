#include "SmsGateway.h"
#include <SoftwareSerial.h>

SmsGateway::SmsGateway(int rxpin,int txpin):SerialGSM(rxpin,txpin), NetworkGateway()
{	
}

SmsGateway::~SmsGateway()
{
}

void SmsGateway::connectToNetwork()
{
		this->begin(9600);
		this->Boot();
		this->Verbose(true);
		Serial.println("Connected");
		this->DeleteAllSMS();
		this->FwdSMS2Serial();
}

bool SmsGateway::connected()
{	



	return false;
}

int SmsGateway::sendData(String address, String data)
{

	this->Boot(); 
  	this->FwdSMS2Serial();
	this->Rcpt(address);
	this->Message(data);
	this->SendSMS();

	return -1;
}

String SmsGateway::reciveData(String &address)
{
	String tmp;

	if(this->ReceiveSMS()){ 
		address = "";
		String Message = this->Message();
		tmp = this->Sender();

		for(int i=0 ; i < tmp.length()-2 ; i++){

			address += tmp[i];

		}

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
