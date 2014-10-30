// if x.h hasn't been included yet...
#ifndef NetworkGateway_h   
#define NetworkGateway_h
#include <Arduino.h>

class NetworkGateway
{
public:
  // Empty virtual destructor for proper cleanup
  // virtual ~NetworkGateway() {}
  virtual bool connectToNetwork()=0;
  virtual bool connected()=0;
  virtual int sendData(String address, String data) = 0; //-1 is error
  virtual String reciveData(String &address)=0;
  virtual long getTime() = 0;
};
#endif