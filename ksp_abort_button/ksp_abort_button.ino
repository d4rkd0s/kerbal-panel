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

// Constants that won't change
const int abortButton = 2; // The number of the abortButton pin

// Setup a light for now
const int ledPin = 13;

// Variables will change:
int abortStatus = 0; // Variable for tracking the abortButton status

void setup() {
  // Initialize the abortButton pin as an input
  pinMode(abortButton, INPUT);
  // Setup the Keyboard
  Keyboard.begin();
}

void loop() {
  // Read the state of the abortButton and load it into the abortStatus
  abortStatus = digitalRead(abortButton);

  // Check if the abortButton is pressed
  if (abortStatus == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
