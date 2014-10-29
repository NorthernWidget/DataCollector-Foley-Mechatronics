#include <SoftwareSerial.h>

char incoming_char=0; //Will hold the incoming character from the Serial Port.
SoftwareSerial cell(50,51); //Create a 'fake' serial port. Pin 2 is the Rx pin, pin 3 is the Tx pin.
bool ring = true;
void setup()
{
	//Initialize serial ports for communication.
	Serial.begin(9600);
	cell.begin(9600);
	Serial.println("Starting SM5100B Communication...");
}

void loop()
{
	//If a character comes in from the cellular module...
	if(cell.available() >0 && ring)
	{
		incoming_char=cell.read(); //Get the character from the cellular serial port.
		Serial.print(incoming_char); //Print the incoming character to the terminal.
		
	}
	//If a character is coming from the terminal to the Arduino...
	if(Serial.available() >0)
	{
		incoming_char=Serial.read(); //Get the character coming from the terminal
		
   		if(incoming_char == 'g')
   		{
			cell.print("AT+CGATT?\r"); //Send the character to the cellular module.
			Serial.print("Sent: AT+CGATT?\r");
   		}
   		if(incoming_char == 'a')
   		{
			cell.print("AT\r"); //Send the character to the cellular module.
			Serial.print("Sent: AT+CGATT=1\r");
   		}
   		if(incoming_char == 's')
   		{
			cell.print("AT\r"); //Send the character to the cellular module.
			Serial.print("Sent: AT+CGATT=?\r");
   		}
   		if(incoming_char == 'c')
   		{
			cell.print("AT+CCLK?\r"); //Send the character to the cellular module.
			Serial.print("Sent: AT+CCLK?\r");
   		}
   		if(incoming_char == 'm')
   		{
			cell.print("AT+CMT\r"); //Send the character to the cellular module.
			Serial.print("Sent: AT+CMT\r");
   		}
		
		if(incoming_char == 'o')
   		{
			cell.print("AT+CSQ\r"); //Send the character to the cellular module.
			Serial.print("Sent: AT+CSQ\r");
   		}
   		if(incoming_char == 'q')
   		{
			cell.print("AT+SDATASTART=1,1\r"); //Send the character to the cellular module.
			Serial.print("AT+SDATASTART=2,1\r");
   		}
   		
	}
}