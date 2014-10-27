// if x.h hasn't been included yet...
#ifndef NetworkGateway_h   
#define NetworkGateway_h
#include <arduino.h>

class NetworkGateway
{
public:
  // Empty virtual destructor for proper cleanup
  virtual ~NetworkGateway() {}
  virtual void connectToNetwork();
  virtual bool connected();
  virtual int sendData(String address, String data) = 0; //-1 is error
  virtual String reciveData(String address);
  virtual long getTime() = 0;
};
#endif