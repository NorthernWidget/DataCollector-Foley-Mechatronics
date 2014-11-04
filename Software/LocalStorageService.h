#ifndef LocalStorageService_h   
#define LocalStorageService_h

#include "StorageService.h"
#include <Arduino.h>
class StorageService;

class LocalStorageService : public virtual StorageService
{
public:
  // Empty virtual destructor for proper cleanup
  LocalStorageService();
  ~LocalStorageService();
  int save(String data); //Returns number of bytes saved
  String load(); //Returns the string in buffer 
  int erase(); //Erase the buffer
  bool isFreeSpcace(int dataSize); //Returns number of free bytes
};
#endif