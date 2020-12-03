    //fade_led:  takes an int as input indicating which PWM pin to perform one fade cycle
  //Arguements: int led
  //Returns:  none
    void fade_led(int led){
     int count=0;
      do{
        analogWrite(led, brightness);
        // change the brightness for next time through the loop:
        brightness = brightness + fadeAmount;

        // reverse the direction of the fading at the ends of the fade:
        if (brightness <= 0 || brightness >= 255) {
          fadeAmount = -fadeAmount;
          count=count+1;
        }
      // wait for 30 milliseconds to see the dimming effect
      delay(30);
    }while(count<2);
    brightness = 0;
    analogWrite(led, brightness);
  }

  /*change_mode:  changes the led flashing mode on button press
  0 = fade red+green=yellow
  1 = fade green+blue=cyan
  2 =  fade blue+red=purple
  3 = fade yellow+red=orange
  4 = fade red
  5 = fade blue+yellow
  Arguements: none
  Returns: none */

void change_mode() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      if(Mode >= 5){
        Mode=0;
      }else{
        Serial.print("Mode max reached");
        Mode++;
      }
    } else {
       // if the current state is LOW then the button
      // wend from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
      // if the current state is HIGH then the button
      // went from off to on:
      Serial.print("Mode:  ");
      Serial.println(Mode);
    delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
}
