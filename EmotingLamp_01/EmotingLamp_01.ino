/**
Experiment 5: Emotinglamp - Canada//Kenya.
****Storage and Playback enabled on sub/pub keys*****
2 channel setup
-publish on one channel
-read on a different channel
Inputs to update
-Name of your WIFI network
-Password of you WIFI network
-publish key
-subscribe key
-your ID name
-name of your data channel to publish on
-name of your partner's channel to read from
**/

#include <WiFiNINA.h>
#define PubNub_BASE_CLIENT WiFiClient
#include <PubNub.h>
#include <ArduinoJson.h>
#include <SparkFunLSM6DS3.h>
#include "Wire.h"

//**Details of your local Wifi Network

//Name of your access point
char ssid[] = "WIFI";
//Wifi password
char pass[] = "PASSWORD";

// channel and ID data
const char* myID = "Nairobi"; // place your name here, this will be put into your "sender" value for an outgoing messsage

char publishChannel[] = "nairobiKEN"; // channel to publish YOUR data
char readChannel[] = "ottawaCAN"; // channel to read THEIR data

int status = WL_IDLE_STATUS;       // the Wifi radio's status

// pubnub keys
char pubkey[] = "pub-c-1fa19e62-9aeb-437d-bc8d-b705830ec014";
char subkey[] = "sub-c-20d1a368-35c6-11eb-89bc-c62ebe77cce5";

// JSON variables
StaticJsonDocument<200> dataToSend; // The JSON from the outgoing message
StaticJsonDocument<200> inMessage; // JSON object for receiving the incoming values
//create the names of the parameters you will use in your message
String JsonParamName1 = "publisher";
String JsonParamName2 = "mood";

int serverCheckRate = 1000; //how often to publish/read data on PN
unsigned long lastCheck; //time of last publish

//create variable for the IMU
LSM6DS3 myIMU(I2C_MODE, 0x6A); //Default constructor is I2C, addr 0x6B

//These are the variables that will hold the values we will be using
//some are calculated locally, some come from PubNub messages

const char* inMessagePublisher; 


//Global variable declarations
int ledRED = 12;           
int ledGREEN = 11;
int ledBLUE = 10;
int ledYELLOW = 9;
int ledYELLOW1 = 6; 

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int buttonPin = 13;    //pushbtton pin
int buttonState = 0;
int Mode = 0;                 //mode of LED flashing
int lastButtonState = 0;     // previous state of the button



void setup() {
  
   Serial.begin(9600);

  //run this function to connect
  connectToPubNub();
  
  myIMU.begin();
  
  // declare output pins for the led strings:
  pinMode(ledRED, OUTPUT);
  pinMode(ledGREEN, OUTPUT);
  pinMode(ledBLUE, OUTPUT);
  pinMode(ledYELLOW, OUTPUT);
  pinMode(ledYELLOW1, OUTPUT);
  // declare input pin for the pushbutton :
  pinMode(buttonPin, INPUT);


}

void loop() {
  
//send and receive messages with PubNub, based on a timer
sendReceiveMessages(serverCheckRate);

switch (Mode){
  case 0:
     //fade red+green=yellow
    analogWrite(ledRED, 255);
    delay(100);
    fade_led(ledGREEN);
    change_mode();
    analogWrite(ledRED, LOW);
    delay(100);
    change_mode();
    break;
  case 1:
     //fade green+blue=cyan
    analogWrite(ledGREEN, 255);
    delay(100);
    fade_led(ledBLUE);
    change_mode();
    analogWrite(ledGREEN, LOW);
    delay(100);
    change_mode();
    break;
  case 2:
    //fade blue+yellow=green
    analogWrite(ledYELLOW, 255);
    delay(100);
    fade_led(ledBLUE);
    change_mode();
    analogWrite(ledYELLOW, LOW);
    delay(100);
    change_mode();
    break;
  case 3:
   //fade blue+red=purple
    analogWrite(ledRED, 255);
    delay(100);
    fade_led(ledBLUE);
    change_mode();
    analogWrite(ledRED, LOW);
    delay(100);
    change_mode();
    break;
  case 4:
    //fade yellow+red=orange
    analogWrite(ledRED, 255);
    delay(100);
    fade_led(ledYELLOW);
    change_mode();
    analogWrite(ledRED, LOW);
    delay(100);
    change_mode();
    break;
  case 5:
    //fade yellow
    analogWrite(ledYELLOW1, 255);
    delay(100);
    fade_led(ledYELLOW);
    change_mode();
    analogWrite(ledYELLOW1, LOW);
    delay(100);
    change_mode();
    break;
 }
}
