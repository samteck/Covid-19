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

byte separator[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.createChar(0, separator);

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
  lcd.setCursor(0,0);
  lcd.print("COVID-19 [INDIA]");
  lcd.setCursor(0,1);
  lcd.print("Status and Alert"); 
  delay(6000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Init.. ESP8266");
  lcd.setCursor(0,1);
  for(i=0;i<16;i++){
      lcd.print(".");
      delay(100);
  }
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Making APi Call");
  lcd.setCursor(0,1);
  for(i=0;i<16;i++){
      lcd.print(".");
      delay(100);
  }
  lcd.clear();

  lcd.setCursor(2,0);
  lcd.print("--OK DONE--");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("LOADING");
  lcd.setCursor(7,1);
  for(i=7;i<16;i++){
      lcd.print(".");
      delay(100);
  }
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("CASES");
  lcd.setCursor(6,0);
  lcd.print("DEATH");
  lcd.setCursor(12,0);
  lcd.print("WELL");

  lcd.setCursor(1,1);
  lcd.print("0");
  lcd.setCursor(7,1);
  lcd.print("0");
  lcd.setCursor(13,1);
  lcd.print("0");

  lcd.setCursor(5,0);
  lcd.write(byte(0));
  lcd.setCursor(11,0);
  lcd.write(byte(0));
  lcd.setCursor(5,1);
  lcd.write(byte(0));
  lcd.setCursor(11,1);
  lcd.write(byte(0));
}