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

// ASCII Codes for wasd
int left = 97;
int down = 115;
int right = 100;
int up = 119;
bool rcsMode = false;
const int alarmDelay = 0;

// Constants that won't change
const int leftButton = 0; // The number of the leftButton pin
const int downButton = 1; // The number of the downButton pin
const int rightButton = 2; // The number of the rightButton pin
const int upButton = 3; // The number of the upButton pin
const int lockButton = 4; // The number of the upButton pin
const int alarm = 5; // The number of the upButton pin
const int speakerOut = 11; // The number of the upButton pin

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

// TONES  ==========================================
// Start by defining the relationship between 
//       note, period, &  frequency. 
#define  a     3900    // 261 Hz old:3830
#define  b     3038    // 329 Hz 
#define  c     2272    // 440 Hz 
#define  d     1900    // 523 Hz old:1912
// Define a special note, 'R', to represent a rest
#define  R     0

// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[], 
//  which sets each note's relative length (higher #, longer note) 
int melody[] = {   a,  b,  c,  a,  b,  c,  d };
int beats[]  = {  20, 20, 20, 20, 20, 20, 20 }; 
int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.

// Set overall tempo
long tempo = 5000;
// Set length of pause between notes
int pause = 150;
// Loop variable to increase Rest length
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;

bool startupTone = false;
bool systemPower = false;

// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                 
}

void playStartup() {
  // Set up a counter to pull from melody[] and beats[]
  for (int i=0; i<MAX_COUNT; i++) {
    tone_ = melody[i];
    beat = beats[i];

    duration = beat * tempo; // Set up timing

    playTone(); 
    // A pause between notes...
    delay(pause);
  }
  delay(100);
  soundAlarm(100);
}


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
  pinMode(speakerOut, OUTPUT);
  // Setup the Keyboard
  Keyboard.begin();
}

void soundAlarm(int alarmLength) {
  digitalWrite(alarm, HIGH);
  delay(alarmDelay + alarmLength);
  digitalWrite(alarm, LOW);
}

void flipControls() {
  if(rcsMode) {
    left = 97;
    down = 115;
    right = 100;
    up = 119;
    rcsMode = false;
  } else {
    soundAlarm(1000);
    left = 106;
    down = 110;
    right = 108;
    up = 104;
    rcsMode = true;
  }
}

void checkButtons() {
  if (digitalRead(redButton) == LOW) {
    soundAlarm(10);
    // Press backspace
    Keyboard.write(KEY_BACKSPACE);
    delay(150);
  }
  if (digitalRead(greenButton) == LOW) {
    soundAlarm(10);
    // Press r
    Keyboard.write(114);
    delay(150);
  }
  if (digitalRead(yellowButton) == LOW) {
    soundAlarm(10);
    // Press space
    Keyboard.write((char) 0x20);
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
    // Press t
    Keyboard.write(116);
    delay(150);
  }
}

void checkJoystick() {
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

void loop() {
  if(digitalRead(lockButton) == LOW) {
    if(startupTone == false) {
      delay(500);
      playStartup();
      startupTone = true;
    }
    checkButtons();
    checkJoystick();
  } else {
    startupTone = false;
  }
  delay(33);
}





