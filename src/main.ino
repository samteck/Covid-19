#include <SoftwareSerial.h>

SoftwareSerial esp8266(10, 11);  //RX,TX

String AP = "Samarth";    
String PASS = "9717234045";
String HOST = "corona.lmao.ninja";
String PORT = "80";

String getData = "GET /countries/india";

int countTrueCommand;
int countTimeCommand; 
boolean found = false;

void setup() {

  Serial.begin(9600);       // communication with the host computer
  esp8266.begin(115200); // communication with esp8266 

  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");

}

void loop() 
{
  sendCommand("AT+CIPMUX=1",5,"OK");
  //sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
  //sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
  //esp8266.println(getData);delay(1500);countTrueCommand++;
  //sendCommand("AT+CIPCLOSE=0",5,"OK");

  sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");   // this is working
  esp8266.println("AT+CIPSEND=0,34" +String(getData.length()+4),4,">");
    delay(1000);
     esp8266.println(getData);
     delay(1000);
 
  if (esp8266.available()) {
    Serial.write(esp8266.read());
  }
  
  //sendCommand("AT+CIPCLOSE=0",5,"OK");
  
}



void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }