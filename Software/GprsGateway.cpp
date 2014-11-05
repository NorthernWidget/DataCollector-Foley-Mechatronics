#include "GprsGateway.h"
#include <SoftwareSerial.h>

GprsGateway::GprsGateway(long timeout): NetworkGateway()//,SoftwareSerial(rxpin,txpin),
{   
    ip = "89.160.207.212"; // IP address of server we're connecting to
    host = "Host: sveinnel.com:5000\n"; // required in HTTP 1.1 - what's the name of the host at this IP address?
    request = "POST /geolog HTTP/1.1\n";                 
    Accept = "Accept: */*\n";
    content = "Content-Type: application/json\n";
    useragent = "User-Agent: curl/7.35.0\n"; 
    apn = "gprs.is";
    cont = false;
    timeOut = timeout;

    // for our purposes the user agent doesn't matter - if I understand correctly it's helpful to use something generic the server will recognize
    // String body = "{\"date\":\"2014-10-29 23:10\",\"temp\":\"BALLS\"}";
    // String ender ="Content-Length: " + String(body.length()) + "\n\n";

}


bool GprsGateway::connectToNetwork()
{
    Serial1.begin(9600);
    Serial.println("starting boot");
    this->boot(); // tók út Serial1.boot();
    Serial.println("Attaching GPRS...");
    Serial1.println("AT+CGATT=1");
    if(!waitFor("OK"))
        return false;
    Serial.println("Setting up PDP Context...");
    Serial1.println("AT+CGDCONT=1,\"IP\",\""+apn+"\"");
    if(!waitFor("OK"))
        return false;
    Serial.println("Activating PDP Context...");
    Serial1.println("AT+CGACT=1,1");
    if(!waitFor("OK"))
        return false;
    Serial.println("Configuring TCP connection to TCP Server...");
    Serial1.println("AT+SDATACONF=1,\"TCP\",\""+ip+"\",5000");
    if(!waitFor("OK")) 
        return false;
    Serial.println("Starting TCP Connection...");
    Serial1.println("AT+SDATASTART=1,1");
    if(!waitFor("OK")) 
        return false;
    con = true;
    return true; 

}

bool GprsGateway::connected()
{
    return false;
}

int GprsGateway::sendData(String address, String data)
{   
    ender ="Content-Length: " + String(data.length()) + "\n\n";
    data = request + host + content + ender + data;

    //Serial.println(data);

    if(!con)
    {
        connectToNetwork(); 
    }

    inTime = millis();

    while ((millis() - inTime) < timeOut)
    {
        Serial.println("Checking socket status:");
        Serial1.println("AT+SDATASTATUS=1"); // we'll get back SOCKSTATUS and then OK
        String sockstat = getMessage();
        if (!waitFor("OK"))
            return -1;
        if (sockstat=="+SOCKSTATUS:  1,0,0104,0,0,0")
        {
            Serial.println("Not connected yet. Waiting 1 second and trying again.");
            delay(1000);
        }
        else if (sockstat=="+SOCKSTATUS:  1,1,0102,0,0,0")
        {
            Serial.println("Socket connected");
            break;
        }
        else 
        {
            Serial.println("We didn't expect that.");
            return -1;
        }
    }

   int packetLength = data.length();    



    Serial.println("Sending HTTP packet...");
    Serial1.print("AT+SDATATSEND=1,"+String(packetLength)+"\r");
    if (!waitFor('>'))
        return -1;
    Serial1.print(data); //SIZE 2
    Serial1.write(26); // ctrl+z character: send the packet
    if (!waitFor("OK"))
        return -1;

    inTime = millis();

    while ((millis() - inTime) < timeOut) 
    {
        Serial1.println("AT+SDATASTATUS=1"); // we'll get back SOCKSTATUS and then OK
        String s = getMessage(); // we want s to contain the SOCKSTATUS message
        if (s == "+STCPD:1") // this means server sent data. cool, but we want to see SOCKSTATUS, so let's get next message
            s = getMessage();
        if (s == "+STCPC:1") // this means socket closed. cool, but we want to see SOCKSTATUS, so let's get next message
            s = getMessage();
        if(!waitFor("OK"))
            return -1;
    
        if (!s.startsWith("+SOCKSTATUS"))
        {
            Serial.println("Wait, this isn't the SOCKSTATUS message!");
            return -1; // something went wrong
        }
        if (checkSocketString(s) == packetLength) // checks that packetLength bytes have been acknowledged by server
            break; // we're good!
        else
        {
            Serial.println("Sent data not yet acknowledged by server, waiting 1 second and checking again.");
            delay(1000);
        }
    }
    Serial.println("Yes! Sent data acknowledged by server!");
    Serial1.println("AT+SDATASTATUS=0"); 

    //  Serial.println("Loka TCP Connection...");
    // Serial1.println("AT+CGACT=1,0");
    // waitFor("OK");
    Serial.println("Loka PDP Context...");
    Serial1.println("AT+SDATASTART=1,0");
    if (!waitFor("OK"))
        return -1;
    Serial.println("Loka GPRS...");
    Serial1.println("AT+CGATT=0");
    if (!waitFor("OK"))
        return -1;
    Serial1.println("AT+CGATT?");
    con = false;

    return 1;
}

String GprsGateway::reciveData(String &address)
{
    return "";
}

long GprsGateway::getTime()
{
    return -1;
}

bool GprsGateway::waitFor(String s)
{
    String message=getMessage();
    if (message != s)
    {
        Serial.println("Wait, that's not what we were expecting. We wanted \""+s+"\"");
        con = false;
        return false;
    }

    delay(100);
    return true;
}

void GprsGateway::waitTil(String sx,String sy, String sz)
{
    bool flagOne = false,flagTow = false, flagThre = false;
    String message;
    inTime = millis();
    
    Serial.println("waiting...");
    while ((millis() - inTime) < timeOut) 
    {
        message = getMessage();
        if(message == sx && !flagOne)
            flagOne = true;
        if(message == sy && !flagTow)
            flagTow = true;
        if(message == sz && !flagThre)
            flagThre = true;


        if (flagOne && flagTow && flagThre){
            delay(100); // cause we're probably about to send another command
            cont = true;
            Serial.println("got the string");
            return;
        }
    }
    Serial.println("timeOut");
    return;
 }  

 void GprsGateway::boot()
 {
    waitTil("+SIND: 4","+SIND: 11","+SIND: 3"); // keep printing cell output til we get "+SIND: 4"
    Serial.println("Module ready");
 }

String GprsGateway::getMessage()
{
    String s="";
    inTime = millis();
  
    while ((millis() - inTime) < timeOut) 
    {
        if(Serial1.available()>0)
        {
            s = s+(char)Serial1.read();
            if (s.length()>1 && s[s.length()-2]=='\r' && s[s.length()-1]=='\n')
            { // if last 2 chars are \r\n
                if (s==" \r\n" || s=="\r\n")
                { // skip these, move on
                    s="";
                }
                else
                { // we have a message!
                    Serial.println(s.substring(0,s.length()-2));
                    return s.substring(0,s.length()-2);
                }
            }
        }
    }
    return "Error in getMessage()";
}

bool GprsGateway::waitFor(char c) {
    inTime = millis();
  
    while ((millis() - inTime) < timeOut)
    {
        if(Serial1.available()>0)
        {
            if ((char)Serial1.read() == c)
            {
                delay(100);
                return true;
            }
        }
    }
    return false;
}

int GprsGateway::checkSocketString(String s)
{
    Serial.println(socketStringSlice(9,s));
    if (socketStringSlice(3,s) == 0)
        return 0;
    else if (socketStringSlice(3,s) == socketStringSlice(9,s))
        return socketStringSlice(3,s);
    else
        return 0;
}

// returns the index of the nth instance of char c in String s
int GprsGateway::nthIndexOf(int n, char c, String s) {
  int index=0;
  for (int i=0; i<=n; i++) {
    index = s.indexOf(c,index+1);
  }
  return index;
}

// expects string such as "SOCKSTATUS: 1,1,0102,10,10,0"
// returns nth chunk of data, delimited by commas
int GprsGateway::socketStringSlice(int n, String s) {
  String slice = s.substring(nthIndexOf(n-1,',',s)+1,nthIndexOf(n,',',s));
  char cArray[slice.length()+1];
  slice.toCharArray(cArray, sizeof(cArray));
  return atoi(cArray);
}