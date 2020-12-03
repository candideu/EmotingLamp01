/*Need to add title and description, as well as name and date*/
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


// Setup
void setup() {
  // declare output pins for the led strings:
  pinMode(ledRED, OUTPUT);
  pinMode(ledGREEN, OUTPUT);
  pinMode(ledBLUE, OUTPUT);
  pinMode(ledYELLOW, OUTPUT);
  pinMode(ledYELLOW1, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
}

// Main Loop
void loop() {

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
    analogWrite(ledBLUE, 255);
    delay(100);
    fade_led(ledGREEN);
    change_mode();
    analogWrite(ledBLUE, LOW);
    delay(100);
    change_mode();
    break;
  case 2:
    //fade blue+red=purple
    analogWrite(ledRED, 255);
    delay(100);
    fade_led(ledBLUE);
    change_mode();
    analogWrite(ledRED, LOW);
    delay(100);
    change_mode();
    break;
  case 3:
    //fade yellow+red=orange
    analogWrite(ledRED, 255);
    delay(100);
    fade_led(ledYELLOW);
    change_mode();
    analogWrite(ledRED, LOW);
    delay(100);
    change_mode();
    break;
  case 4:
    //fade yellow
    analogWrite(ledYELLOW1, 255);
    delay(100);
    fade_led(ledYELLOW);
    change_mode();
    analogWrite(ledYELLOW1, LOW);
    delay(100);
    change_mode();
    break;
  case 5:
    //fade blue+yellow
    analogWrite(ledYELLOW, 255);
    delay(100);
    fade_led(ledBLUE);
    change_mode();
    analogWrite(ledYELLOW, LOW);
    delay(100);
    change_mode();
    break;
 }
}
