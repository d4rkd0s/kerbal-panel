#include <Keyboard.h>

/*
 KSP Abort Button

 When the button connected to Digital Pin 2 is pressed
 the arduino will emulate a keyboard press of "backspace"
 which in Kerbal Space Program initiates the abort sequence.

 The circuit:
 * pushbutton attached to pin 2

 Created in 2017
 by d4rkd0s <http://d4rkd0s.me>

 This code is licensed under the GNU GPL v3.0
 https://raw.githubusercontent.com/d4rkd0s/kerbal-panel/master/LICENSE
 
 */

// ASCII Code for backspace is 08
const int keyToPress = 8;

// Constants that won't change
const int abortButton = 2; // The number of the abortButton pin

// Setup a light for now
const int buttonLed = 3;

// Variables will change:
int abortStatus = 0; // Variable for tracking the abortButton status

// Boolean to track if the button is pressed
bool btnstatus = false;

void setup() {
  // Initialize the abortButton pin as an input
  pinMode(abortButton, INPUT);
  // Setup the Keyboard
  Keyboard.begin();
  
}

void loop() {
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(buttonLed, fadeValue);
    checkButton();
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(buttonLed, fadeValue);
    checkButton();
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}

void checkButton() {
  // Read the state of the abortButton and load it into the abortStatus
  abortStatus = digitalRead(abortButton);
  // Check if the abortButton is pressed
  if (abortStatus == HIGH && btnstatus == true) {
     Serial.print("Abort Button is NOT pressed");
     btnstatus = false;
     Serial.print('\n');
  } else if(abortStatus == LOW && btnstatus == false) {
    // turn LED off:
    Serial.print("Abort Button is pressed");
    Keyboard.write(keyToPress);
    btnstatus = true;
    Serial.print('\n');
  }
}

