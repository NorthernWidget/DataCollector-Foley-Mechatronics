#define EEPROM_SIZE 4096

#include "LocalStorageService.h"
#include <JsonGenerator.h>
#include <arduino.h>
#include <EEPROM.h>

LocalStorageService::LocalStorageService()
{

}

int LocalStorageService::save(String data)
{
	int iterator = 0;
	
	//Find pointer to empty space
	for (int i = 0; i < EEPROM_SIZE; i++)
	{
		iterator++;
		if(EEPROM.read(i) == 0)
		{
			break;
		}
	}
	
	//If note enough memory return -1
	if(!isFreeSpcace(data.length()))
	{
		return -1
	}

	//Write to EEPROM
	else
	{
		int dataSize = 0;
		for (int i = 0; i < data.length(); i++)
		{
			if(iterator >= EEPROM_SIZE)
			{
				break;
			}
			EEPROM.write(iterator++, data[i]);
			dataSize++;
		}
		return dataSize;
	}
}

String LocalStorageService::load()
{
	String data = "";
	
	//Read data from memory until binary 0 is reached
	for (int i = 0; i < EEPROM_SIZE; i++)
	{
		char letter = EEPROM.read(i);
		if(letter == 0)
		{
			break;
		}
		else
		{
			data += letter;
		}
	}
	return data;
}

int LocalStorageService::erase()
{
	for (int i = 0; i < EEPROM_SIZE; i++)
	{
		write(i, 0);
	}
}

bool LocalStorageService::isFreeSpcace(int dataSize)
{
	int iterator = 0;

	//Find pointer to empty space
	for (int i = 0; i < EEPROM_SIZE; i++)
	{
		iterator++;
		if(EEPROM.read(i) == 0)
		{
			break;
		}
	}

	//If note enough memory return -1
	if(EEPROM_SIZE - iterator < dataSize);
	{
		return false;
	}
	else
	{
		return true;
	}
}