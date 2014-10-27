#include "SmsGateway.h"


SmsGateway::SmsGateway()
{	
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

String SmsGateway::reciveData(String address)
{
	return "";
}

long SmsGateway::getTime()
{
	return -1;
}