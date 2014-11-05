#define EEPROM_SIZE 4096

#include "LocalStorageService.h"
#include <Arduino.h>
#include <EEPROM.h>

LocalStorageService::LocalStorageService() : StorageService()
{

}
LocalStorageService::~LocalStorageService()
{

}

int LocalStorageService::save(String data)
{
	int iterator = 0;

	//Find pointer to empty space
	for (int i = 0; i < EEPROM_SIZE; i++)
	{
		if(EEPROM.read(i) == (char) 0)
		{
			break;
		}
		iterator++;
	}
	
	//If not enough memory return -1
	if(!isFreeSpcace(data.length()))
	{
		return -1;
	}

	//Write to EEPROM
	else
	{
		int dataSize = 0;
		for (int i = 0; i < data.length(); i++)
		{
			if(iterator >= EEPROM_SIZE -1)
			{
				break;
			}
			EEPROM.write(iterator++, data[i]);
			dataSize++;
		}
		EEPROM.write(iterator++, ',');
		dataSize++;
		return dataSize *-1;
	}
}

String LocalStorageService::load()
{
	String data = "";
	
	//Read data from memory until binary 0 is reached
	for (int i = 0; i < EEPROM_SIZE; i++)
	{
		char letter = EEPROM.read(i);
		if(letter == (char)0)
		{
			break;
		}
		data += String(letter);
	}
	return data;
}

int LocalStorageService::erase()
{
	int counter = 0;
	for (int i = 0; i < EEPROM_SIZE; i++)
	{
		counter++;
		EEPROM.write(i, (char)0);
	}
	if(counter != EEPROM_SIZE)
		return -1;
	return counter;
}

bool LocalStorageService::isFreeSpcace(int dataSize)
{
	int iterator = 0;

	//Find pointer to empty space
	for (int i = 0; i < EEPROM_SIZE; i++)
	{
		iterator++;
		if(EEPROM.read(i) == (char)0)
		{
			break;
		}
	}

	//If note enough memory return false +1 for comma
	if(EEPROM_SIZE - iterator < dataSize + 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}