#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial esp8266(10, 11); // RX, TX

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String serial_input;
const size_t capacity = JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 280;
DynamicJsonDocument doc(capacity);
const char* json;
int cases;
int death;
int well;
int data[3];



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
  initialScreen();
}

void loop() { // run over and over
  getdata();
}

void getdata(){
  if (esp8266.available()) {
     serial_input = esp8266.readString();
     
     int len = serial_input.length()+1;
     char char_array[len];
     serial_input.toCharArray(char_array,len);
     
     deserializeJson(doc, char_array);
     cases = doc["cases"];
     death = doc["deaths"];
     well  = doc["recovered"];

     show_cases(cases);
     show_death(death);
     show_well(well);

    //  data[0] = cases;
    //  data[1] = death;
    //  data[2] = well;

    //  Serial.println(cases);
    //  Serial.println(death);
    //  Serial.println(well);
     
   }
}

void show_cases(int value){
  Serial.println(value);
  lcd.setCursor(0,1);
  lcd.print(value);
}

void show_death(int value){
  Serial.println(value);
  lcd.setCursor(7,1);
  lcd.print(value);
}

void show_well(int value){
  Serial.println(value);
  lcd.setCursor(13,1);
  lcd.print(value);
}

void initialScreen(){
  int i=0;
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("COVID - 19");
  lcd.setCursor(0,1);
  lcd.print("Status and Alert"); 
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CASES");
  lcd.setCursor(6,0);
  lcd.print("DEATH");
  lcd.setCursor(12,0);
  lcd.print("WELL");
  // lcd.setCursor(0,0);
  // lcd.print("LOADING BOOTSTRAP");
  // lcd.setCursor(0,1);
  // for(i=0;i<20;i++){
  //     lcd.print(".");
  //     delay(150);
  // }
  // lcd.setCursor(0,2);
  // lcd.print("LOADING NCC. FILES");
  // lcd.setCursor(0,3);
  // for(i=0;i<20;i++){
  //     lcd.print(".");
  //     delay(100);
  // }
  // delay(1000);
  
  // for(i=0;i<=100;i++){
  //   lcd.clear();
  //   lcd.setCursor(0,0);
  //   lcd.print("Initializing .......");
  //   lcd.setCursor(0,1);
  //   lcd.print("PIR Sensors");
  //   lcd.setCursor(0,2);
  //   lcd.print(i);
  //   lcd.print("%");
  //   delay(50);
  // }
  // lcd.setCursor(8,2);
  // lcd.print("--OK DONE--");
  // delay(500);
  // lcd.setCursor(0,3);
  // lcd.print("LOADING START SCREEN");
  // delay(1500);
}