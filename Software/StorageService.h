#ifndef StorageService_h   
#define StorageService_h

#include <Arduino.h>

class StorageService
{
public:
  // Empty virtual destructor for proper cleanup
  StorageService() {};
  virtual int save(String data)=0; //Returns number of bytes saved
  virtual String load()=0; //Returns the string in buffer 
  virtual int erase()=0; //Erase the buffer
  virtual bool isFreeSpcace(int dataSize) = 0; //Returns number of free bytes
};
#endif
