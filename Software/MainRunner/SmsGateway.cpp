#include "SmsGateway.h"
#include <SoftwareSerial.h>

SmsGateway::SmsGateway(int rxpin,int txpin)
{	
	cell = new SerialGSM(rxpin,txpin);  
	cell->begin(9600);
	cell->Verbose(true);
	cell->Boot();
  	cell->DeleteAllSMS();
  	cell->FwdSMS2Serial();
}

SmsGateway::~SmsGateway()
{
	delete cell;

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
	if(cell->ReceiveSMS()){ 
		String Message = cell->Message();
		address = cell->Sender();
		cell->DeleteAllSMS();

		return Message;
	}
	else
	return "";
}

long SmsGateway::getTime()
{
	return -1;
}
