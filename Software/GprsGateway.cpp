#include GprsGateway.h

virtual GprsGateway()
{	
}

virtual ~GprsGateway()
{
}

virtual void connectToNetwork()
{

}

virtual bool connected()
{
	return false;
}

virtual int sendData(String address, String data)
{
	return -1;
}

virtual String reciveData(String address)
{
	return "";
}

virtual long getTime()
{
	return -1;
}