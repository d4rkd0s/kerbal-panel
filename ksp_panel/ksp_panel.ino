#include <Keyboard.h>

/*
 KSP Panel

 When the joystick with 4 buttons is pressed the arduino
 will emulate the pressing and holding of W A S and D to
 allow for movement in Kerbal Space Program

 The circuit:
 * 4 normally open switches are connected from ground to digital pins 0,1,2,3

 Created in 2017
 by d4rkd0s <http://d4rkd0s.me>

 This code is licensed under the GNU GPL v3.0
 https://raw.githubusercontent.com/d4rkd0s/kerbal-panel/master/LICENSE
 
 */

// ASCII Codes for WASD
const int left = 65;
const int down = 83;
const int right = 68;
const int up = 87;

// Constants that won't change
const int leftButton = 0; // The number of the leftButton pin
const int downButton = 1; // The number of the downButton pin
const int rightButton = 2; // The number of the rightButton pin
const int upButton = 3; // The number of the upButton pin

// Variables will change as we loop
int leftButtonActual = 0; // Variable for tracking the abortButton status
int downButtonActual = 0; // Variable for tracking the abortButton status
int rightButtonActual = 0; // Variable for tracking the abortButton status
int upButtonActual = 0; // Variable for tracking the abortButton status

// Booleans to track if the buttons are pressed
bool leftButtonStatus = false;
bool downButtonStatus = false;
bool rightButtonStatus = false;
bool upButtonStatus = false;

void setup() {
  // Initialize the buttons pin as inputs
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
}

void checkButton() {
  // Read the state of the buttons and load it into the buttonStatus vars
  leftButtonActual = digitalRead(leftButton);
  downButtonActual = digitalRead(downButton);
  rightButtonActual = digitalRead(rightButton);
  upButtonActual = digitalRead(upButton); 
  
  // Check if the left button is pressed
  if (leftButtonActual == LOW && leftButtonStatus == false) {
     Serial.print("Left button was pressed");
     Keyboard.press(left);
     leftButtonStatus = true;
     Serial.print('\n');
  } else {
    if(leftButtonActual == HIGH && leftButtonStatus == true) {
      Serial.print("Left button was released");
      Keyboard.release(left);
      //Keyboard.write(keyToPress);
      leftButtonStatus = false;
      Serial.print('\n');
    }
  }

  // Check if the down button is pressed
  if (downButtonActual == LOW && downButtonStatus == false) {
     Serial.print("Down button was pressed");
     Keyboard.press(down);
     downButtonStatus = true;
     Serial.print('\n');
  } else {
    if(downButtonActual == HIGH && downButtonStatus == true) {
      Serial.print("Down button was released");
      Keyboard.release(down);
      downButtonStatus = false;
      Serial.print('\n');
    }
  }

  // Check if the right button is pressed
  if (rightButtonActual == LOW && rightButtonStatus == false) {
     Serial.print("Right button was pressed");
     Keyboard.press(right);
     rightButtonStatus = true;
     Serial.print('\n');
  } else {
    if(rightButtonActual == HIGH && rightButtonStatus == true) {
      Serial.print("Right button was released");
      Keyboard.release(right);
      rightButtonStatus = false;
      Serial.print('\n');
    }
  }

  // Check if the up button is pressed
  if (upButtonActual == LOW && upButtonStatus == false) {
     Serial.print("Up button was pressed");
     Keyboard.press(up);
     upButtonStatus = true;
     Serial.print('\n');
  } else {
    if(upButtonActual == HIGH && upButtonStatus == true) {
      Serial.print("Up button was released");
      Keyboard.release(up);
      upButtonStatus = false;
      Serial.print('\n');
    }
  }
 
}

