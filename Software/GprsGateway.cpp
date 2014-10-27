#include "GprsGateway.h"

GprsGateway::GprsGateway(int rxpin,int txpin)
{	
}


void GprsGateway::connectToNetwork()
{

}

bool GprsGateway::connected()
{
	return false;
}

int GprsGateway::sendData(String address, String data)
{
	return -1;
}

String GprsGateway::reciveData(String address)
{
	return "";
}

long GprsGateway::getTime()
{
	return -1;
}