#ifndef LocalStorageService_h   
#define LocalStorageService_h

#include <arduino.h>
#include <StorageService.h>

class LocalStorageService : StorageService
{
public:
  // Empty virtual destructor for proper cleanup
  LocalStorageService() {}
  int save(String data)=0; //Returns number of bytes saved
  String load()=0; //Returns the string in buffer 
  int erase()=0; //Erase the buffer
  bool isFreeSpcace(int dataSize) = 0; //Returns number of free bytes
};
#endif