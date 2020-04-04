#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial esp8266(10, 11); // RX, TX

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String jsonn ;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, sam!");

  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  esp8266.begin(9600);
}

void loop() { // run over and over
  getdata();
}

void getdata(){
  if (esp8266.available()) {
     jsonn = esp8266.readString();
     Serial.print(jsonn);
   }
}