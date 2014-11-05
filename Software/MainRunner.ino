//#include "GprsGateway.h"
#include "SerialGSM.h"
#include "SmsGateway.h"
#include "GprsGateway.h"

//#include "NetworkGateway.h"
#include "WixelSensorService.h"
//#include "Time.h"
#include "StorageService.h"
#include "LocalStorageService.h"

#define GSM_RESET_PIN 22
#define SAMPLE_DATA_FREQ 300000//900000   // ms
#define SEND_DATA_FREQ 900000//3600000    // ms
#define TIME_OUT 45000            // ms
#define MAX_TRIALS 5
#define ERASE_PIN 50
#define MANUAL_SEND_PIN 51
#define LED_PIN 13

long lastDataSample;
long lastDataTransmit;
int faildTransmits;
bool sendRequest;

String number;
String message=NULL;
String sec,mino,kls,da,mon,ye;
int a;

bool flag = true;
long curnetTime;
long timeOute;
long newTime;
String timeDayt;
String dataToStore;

SmsGateway sms(TIME_OUT);
GprsGateway gprs(TIME_OUT);
LocalStorageService storage;
WixelSensorService wixelData(TIME_OUT);

void collectData(int sensorId);
String parseDataToJson(int data, int sensorId);
String concatToJson(String data);
int sendToServer(String data);
bool eraseRequest();


void setup()
{
    pinMode(GSM_RESET_PIN, OUTPUT);
    pinMode(ERASE_PIN, INPUT_PULLUP);
    pinMode(MANUAL_SEND_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(GSM_RESET_PIN, LOW);
    digitalWrite(LED_PIN, LOW);

    Serial.begin(9600);
    curnetTime = millis();
    lastDataSample = millis();
    lastDataTransmit = millis();
    faildTransmits = 0;
    sendRequest = false;
}

void loop()
{
    if((millis() - lastDataSample) > SAMPLE_DATA_FREQ || sendRequest)
    {
        //get sensor 1 data
        Serial.println('1');
        collectData(1);

        //get sensor 2 data
        Serial.println('2');
        collectData(2);

        //get sensor 3 data
        Serial.println('3');
        collectData(3);

        lastDataSample = millis();
    }

    if((millis() - lastDataTransmit) > SEND_DATA_FREQ || sendRequest)
    {
        //send sensor data to server
        String stuff = storage.load();
        Serial.println("stored data = " + stuff);
        String data = concatToJson(stuff);
        Serial.println("Data to send -> " + data);

        // TODO: try more
        if (sendToServer(data) > 0)
        {
            //Erase memory
            Serial.println("Erase memory");
            storage.erase();

            lastDataTransmit = millis();
            faildTransmits = 0;
            sendRequest = false; // TODO
        }
        else if (faildTransmits >= MAX_TRIALS)
        {
            faildTransmits = 0;
            lastDataTransmit = millis();
            sendRequest = false;  // TODO
        }
        else
            faildTransmits++;
    }

    if(eraseRequest())
    {
        //Erase memory
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Erase memory");
        storage.erase();        
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }

    if(manualSendRequest())
    {
        //Set ready for sending data
        sendRequest = true;
        Serial.println("Send request");
    }

}

void collectData(int sensorId)
{
    int tempData = wixelData.getSensorData(sensorId);
    Serial.println(tempData);
    dataToStore = parseDataToJson(tempData, sensorId);
    
    //store sensor data
    if(storage.isFreeSpcace(dataToStore.length()))
    {
        storage.save(dataToStore); 
    }
}

String parseDataToJson(int data, int sensorId)
{
    String jsoon = "{\"date\": \"" + String(millis()) + "\", \"temp\": \"" +  String(data) + "\", \"sensorId\": \"" + String(sensorId) + "\"}";
    return jsoon;
}

String concatToJson(String data)
{
    return "[" + data.substring(0, data.length()-1) + "]";
}

int sendToServer(String data)
{
    int ret = 0;
    digitalWrite(GSM_RESET_PIN, HIGH);
    Serial.println("in sendToServer()");
    gprs.connectToNetwork();
    ret = gprs.sendData("", data);
    delay(500);
    digitalWrite(GSM_RESET_PIN, LOW);
    delay(500);
    return ret;
}

bool eraseRequest()
{
    if(digitalRead(ERASE_PIN) == LOW)
        return true;
    else
        return false;
}

bool manualSendRequest()
{
    if(digitalRead(MANUAL_SEND_PIN) == LOW)
        return true;
    else
        return false;
}