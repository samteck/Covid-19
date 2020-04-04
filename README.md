# Covid-19
## Status and Notifcation on Coronavirus Cases

This is a project in which we will get Covid-19 stats from a HTTPS secured API, parse the response and Display it locally on a LCD Display.
Also, if there is a increase in the number of cases we will hava a buzzer that will beep to alert the user.

#### API Reference
We are using below API which return details of coronavirus cases in particular country
**https://corona.lmao.ninja/countries/:country** 


## Revision 1.0 ##
In this reviosn we will use Arduino as a Host MCU and esp8266 as wifi module. We will communicate with esp8266 via AT commands.

<img src="https://github.com/samteck/Covid-19/blob/master/diagrams/REV1.0-Architecture.png" width="700">

Since we were not able to make a HTTPS connection via AT commands (esp firmware doesn't support that). We have set up an additional Flask server on Raspberry Pi which will router HTTP request to HTTPS and server the response back to ESP8266 which will be forwarded to Arduino.

## Hardware Requirements
1. Arduino Uno
2. ESP8266-01 module
3. HD44780 (LCD)


Note : This project is developed using VSCode and Arduino extension from Microsoft
Learn : Configure Visual Studio code for Arduino Development