#include <Keyboard.h>

/*
 KSP Panel

 When the joystick with 4 buttons is pressed the arduino
 will emulate the pressing and holding of W A S and D to
 allow for movement in Kerbal Space Program

 The circuit:
 * 4 normally open switches are connected from ground to digital pins 0,1,2,3
ASASSSSSSWSAASASASASAS
 Created in 2017
 by d4rkd0s <http://d4rkd0s.me>AAAAAAAAAAADAWSDWAAWWAWWSDAADDDDADWSAWDS

 This code is licensed under the GNU GPL v3.0
 https://raw.githubusercontent.com/d4rkd0s/kerbal-panel/master/LICENSE
 
 */

// ASCII Codes for WASD
int left = 65;
int down = 83;
int right = 68;
int up = 87;
bool rcsMode = false;
const int alarmDelay = 0;

// Constants that won't change
const int leftButton = 0; // The number of the leftButton pin
const int downButton = 1; // The number of the downButton pin
const int rightButton = 2; // The number of the rightButton pin
const int upButton = 3; // The number of the upButton pin
const int lockButton = 4; // The number of the upButton pin
const int alarm = 5; // The number of the upButton pin

const int redButton = 6; // The number of the leftButton pin
const int greenButton = 7; // The number of the downButton pin
const int yellowButton = 8; // The number of the rightButton pin
const int whiteButton = 9; // The number of the upButton pin
const int blueButton = 10; // The number of the upButton pin

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
  pinMode(lockButton, INPUT_PULLUP);

  pinMode(redButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(yellowButton, INPUT_PULLUP);
  pinMode(whiteButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);
  
  pinMode(alarm, OUTPUT);
  // Setup the Keyboard
  Keyboard.begin();
}

void loop() {
  if (digitalRead(redButton) == LOW) {
    soundAlarm(10);
    // Press backspace
    Keyboard.write(KEY_BACKSPACE);
    delay(150);
  }
  if (digitalRead(greenButton) == LOW) {
    soundAlarm(10);
    // Press R
    Keyboard.write(82);
    delay(150);
  }
  if (digitalRead(yellowButton) == LOW) {
    soundAlarm(10);
    // Press space
    Keyboard.write(32);
    delay(150);
  }
  if (digitalRead(whiteButton) == LOW) {
    soundAlarm(100);
    // Utility
    flipControls();
    delay(1000);
  }
  if (digitalRead(blueButton) == LOW) {
    soundAlarm(10);
    // Press T
    Keyboard.write(84);
    delay(150);
  }
  
  checkButton();
  delay(33);
}

void soundAlarm(int alarmLength) {
  digitalWrite(alarm, HIGH);
  delay(alarmDelay + alarmLength);
  digitalWrite(alarm, LOW);
}

void flipControls() {
  if(rcsMode) {
    left = 65;
    down = 83;
    right = 68;
    up = 87;
    rcsMode = false;
  } else {
    soundAlarm(1000);
    left = 74;
    down = 78;
    right = 76;
    up = 72;
    rcsMode = true;
  }
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

