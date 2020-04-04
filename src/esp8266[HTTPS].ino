#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#ifndef STASSID
#define STASSID "Samarth"
#define STAPSK  "9717234045"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "corona.lmao.ninja";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "7B 00 29 73 45 13 A3 F7 95 84 42 EA E0 28 1B F4 0D B8 11 53";

void setup() {
  Serial.begin(9600);
  //Serial.println();
  //Serial.print("connecting to ");
  //Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  //Serial.println("");
  //Serial.println("WiFi connected");
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());
}

void loop() {
  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  //Serial.print("connecting to ");
  //Serial.println(host);

  //Serial.printf("Using fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);

  String url = "/countries/india";
  //Serial.print("requesting URL: ");
  //Serial.println(url);
  
  if (!client.connect(host, httpsPort)) {
    //Serial.println("connection failed");
    return;
  }
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  //Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      //Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
//  if (line.startsWith("{\"state\":\"success\"")) {
//    Serial.println("esp8266/Arduino CI successfull!");
//  } else {
//    Serial.println("esp8266/Arduino CI has failed");
//  }
  //Serial.println("reply was:");
  //Serial.println("==========");
  Serial.println(line);
  //Serial.println("==========");
  //Serial.println("closing connection");
  delay(300000);
}