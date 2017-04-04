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
const int leftButton = 0; // The number of the leftButton pin
const int downButton = 1; // The number of the downButton pin
const int rightButton = 2; // The number of the rightButton pin
const int upButton = 3; // The number of the upButton pin

// Setup a light for now
const int buttonLed = 3;

// Variables will change:
int leftButtonActual = 0; // Variable for tracking the abortButton status
int downButtonActual = 0; // Variable for tracking the abortButton status
int rightButtonActual = 0; // Variable for tracking the abortButton status
int upButtonActual = 0; // Variable for tracking the abortButton status


// Boolean to track if the buttons are pressed
bool leftButtonStatus = false;
bool downButtonStatus = false;
bool rightButtonStatus = false;
bool upButtonStatus = false;

void setup() {
  // Initialize the abortButton pin as an input
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(upButton, INPUT_PULLUP);
  // Setup the Keyboard
  Keyboard.begin();
 
}

void loop() {
  checkButton();
  delay(33);
//  Serial.print("Checking status...");
//  Serial.print('\n');
}

void checkButton() {
  // Read the state of the buttons and load it into the buttonStatus vars
  leftButtonActual = digitalRead(leftButton);
  downButtonActual = digitalRead(downButton);
  rightButtonActual = digitalRead(rightButton);
  upButtonActual = digitalRead(upButton);

//  Serial.print("Left button actual");
//  Serial.print('\n');
//  Serial.print(leftButtonActual);
//  Serial.print('\n');
//  Serial.print("Down button actual");
//  Serial.print('\n');
//  Serial.print(downButtonActual);
//  Serial.print('\n');
//  Serial.print("Right button actual");
//  Serial.print('\n');
//  Serial.print(rightButtonActual);
//  Serial.print('\n');
//  Serial.print("Up button actual");
//  Serial.print('\n');
//  Serial.print(upButtonActual);
//  Serial.print('\n');
 
  
  // Check if the leftButton is pressed
  if (leftButtonActual == LOW && leftButtonStatus == false) {
     Serial.print("Left button was pressed");
     leftButtonStatus = true;
     Serial.print('\n');
  } else {
    if(leftButtonActual == HIGH && leftButtonStatus == true) {
      Serial.print("Left button was released");
      //Keyboard.write(keyToPress);
      leftButtonStatus = false;
      Serial.print('\n');
    }
  }

  if (downButtonActual == LOW && downButtonStatus == false) {
     Serial.print("Down button was pressed");
     downButtonStatus = true;
     Serial.print('\n');
  } else {
    if(downButtonActual == HIGH && downButtonStatus == true) {
      Serial.print("Down button was released");
      //Keyboard.write(keyToPress);
      downButtonStatus = false;
      Serial.print('\n');
    }
  }

  if (rightButtonActual == LOW && rightButtonStatus == false) {
     Serial.print("Right button was pressed");
     rightButtonStatus = true;
     Serial.print('\n');
  } else {
    if(rightButtonActual == HIGH && rightButtonStatus == true) {
      Serial.print("Right button was released");
      //Keyboard.write(keyToPress);
      rightButtonStatus = false;
      Serial.print('\n');
    }
  }

  if (upButtonActual == LOW && upButtonStatus == false) {
     Serial.print("Up button was pressed");
     upButtonStatus = true;
     Serial.print('\n');
  } else {
    if(upButtonActual == HIGH && upButtonStatus == true) {
      Serial.print("Up button was released");
      //Keyboard.write(keyToPress);
      upButtonStatus = false;
      Serial.print('\n');
    }
  }
 
}

