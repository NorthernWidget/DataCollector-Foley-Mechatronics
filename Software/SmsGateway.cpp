#include "SmsGateway.h"
#include <SoftwareSerial.h>

SmsGateway::SmsGateway(int rxpin,int txpin):SerialGSM(rxpin,txpin), NetworkGateway()
{	
//this->begin(9600);
//this->Verbose(true);
//this->Boot();
//this->DeleteAllSMS();
//this->FwdSMS2Serial();
  
	
}

SmsGateway::~SmsGateway()
{
	//delete cell;

}

void SmsGateway::connectToNetwork()
{
		this->begin(9600);
		this->Boot();
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
