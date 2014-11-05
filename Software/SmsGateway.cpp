#include "SmsGateway.h"
#include <SoftwareSerial.h>

SmsGateway::SmsGateway(long TimeOute): NetworkGateway(),SerialGSM()
{   
    timeOute = TimeOute;
}

SmsGateway::~SmsGateway()
{

}
bool SmsGateway::connectToNetwork()
{
    Serial1.begin(9600);
    // Serial1.listen();
    //Serial1.boot();
    this->boot();
    //Serial1.Verbose(true);
    this->Verbose(true);
    Serial.println("Connected");
    //Serial1.DeleteAllSMS();
    //Serial1.FwdSMS2Serial();
    return true;
}

bool SmsGateway::connected()
{   



    return false;
}

int SmsGateway::sendData(String address, String data)
{

    //Serial1.Boot(); 
    // Serial1.FwdSMS2Serial();
    this->FwdSMS2Serial();
    // Serial1.Rcpt(address);
    // Serial1.Message(data);
    // Serial1.SendSMS();
    // Serial1.DeleteAllSMS();
    this->Rcpt(address);
    this->Message(data);
    this->SendSMS();
    this->DeleteAllSMS();
    delay(10000);
    return -1;
}

String SmsGateway::reciveData(String &address)
{
    String tmp;

    // Serial1.FwdSMS2Serial();
    this->FwdSMS2Serial();
    for(int i = 0 ; i < 15 ; i++){              
        Serial.println(i);
        if(waitFor("+CMT")){ 
            address = "";
            // String Message = Serial1.Message();
            String Message = this->Message();
            // tmp = Serial1.Sender();
            tmp = this->Sender();


            for(int i=0 ; i < tmp.length()-2 ; i++){

                address += tmp[i];

            }

            // Serial1.DeleteAllSMS();
            this->DeleteAllSMS();
            Serial.println(Message);
            return Message;
        }
    }

    // else
    return "";
}

long SmsGateway::getTime()
{   
    // Serial1.FwdSMS2Serial();
    // String timeMessage = getMessage();
    // Serial.println(timeMessage);
    // String s = "+CMT: \"+3548967358\",\"+3548900100\"";
    // if(timeMessage.substring(0,s.length()) == s)
    // {
    //  Serial.println(timeMessage);
    // }

    return -1;
}
String SmsGateway::getTime(int i){


    return "";
}
void SmsGateway::boot()
{
    waitTil("+SIND: 4","+SIND: 11","+SIND: 3"); // keep printing cell output til we get "+SIND: 4"
    Serial.println("Module ready");
}

void SmsGateway::waitTil(String sx,String sy, String sz)
{
    bool flagOne = false,flagTow = false, flagThre = false;
    String message;
    while (1) {
        message = getMessage();
        if(message == sx && !flagOne)
            flagOne = true;
        if(message == sy && !flagTow)
            flagTow = true;
        if(message == sz && !flagThre)
            flagThre = true;


        if (flagOne && flagTow && flagThre){
            delay(100); // cause we're probably about to send another command
          
            return;
      }
    }  
}

String SmsGateway::getMessage() {
  String s="";
  inTime = millis();
  while ((millis() - inTime) < timeOute)  {
    if(Serial1.available()>0) {
      s = s+(char)Serial1.read();
      if (s.length()>1 && s[s.length()-2]=='\r' && s[s.length()-1]=='\n') { // if last 2 chars are \r\n
        if (s==" \r\n" || s=="\r\n") { // skip these, move on
          s="";
        }
        else { // we have a message!
          Serial.println(s.substring(0,s.length()-2));
          return s.substring(0,s.length()-2);
        }
      }
    }
  }
}
bool SmsGateway::waitFor(String s)
{
    
    bool flagOne = false;
    String message;
    inTime = millis();
    while ((millis() - inTime) < 10) {
        message = getMessage();
        Serial.println(inTime);
        if(message > 0)
            if(message[0] == s[0] && message[1] == s[1] && message[2] == s[2] && message[3] == s[3] ){
                flagOne = true;
                Time = message.substring(52,10);
            }
                
        

        if (flagOne){
          delay(100); // cause we're probably about to send another command
          
          return true;
      }
    }
    return false;  
}