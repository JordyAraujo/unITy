/*
  source: www.electroschematics.com
  You'll need to change the led pins and the codes
  accordingly to your configuration and IR remote
*/

#include <IRremote.h>

int RECV_PIN = 3; // the pin where you connect the output pin of TSOP4838
int led1 = 8;
int led2 = 9;
int led3 = 10;
int led4 = 11;
int energy = 2;
int energy2 = 0;
int button = 12;
int pinButton = 6; // Interrupt 4 = PIN 7
int itsONled[] = {0, 0, 0, 0};
int stateLED = LOW;
int stateButton;
int previous = LOW;
long time = 0;
long debounce = 500;
/* the initial state of LEDs is OFF (zero)
  the first zero must remain zero but you can
  change the others to 1's if you want a certain
  led to light when the board is powered */
#define code1 1100 // code received from button A
#define code2 3148 // code received from button B
#define code3 59139 // code received from button C
#define code4 13242
#define code5 1040
#define code6 3088
#define code7 1041
#define code8 3089

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600); // you can comment this line
  irrecv.enableIRIn(); // Start the receiver
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(energy, OUTPUT);
  pinMode(energy2, OUTPUT);
  pinMode(button, INPUT);
  pinMode(pinButton, INPUT);
  digitalWrite(energy, HIGH);
  digitalWrite(energy2, HIGH);
}

void loop() {

   stateButton = digitalRead(pinButton);  
  if(stateButton == HIGH && previous == LOW && millis() - time > debounce) {
    if(stateLED == HIGH){
      stateLED = LOW; 
    } else {
       stateLED = HIGH; 
    }
    time = millis();
  }
  digitalWrite(led1, stateLED);
  previous == stateButton;

  if (digitalRead(button) == HIGH) {
    itsONled[0] = 0;
  }

  if (digitalRead(button) == LOW) {
    itsONled[0] = 1;
  }

  if (irrecv.decode(&results)) {
    unsigned int value = results.value;
    switch (value) {

      case code1:
        if (itsONled[0] == 1) { // if first led is on then
          digitalWrite(led1, LOW); // turn it off when button is pressed
          itsONled[0] = 0; // and set its state as off
        } else { // else if first led is off
          digitalWrite(led1, HIGH); // turn it on when the button is pressed
          itsONled[0] = 1; // and set its state as on
        }
        break;

      case code2:
        if (itsONled[0] == 1) {
          digitalWrite(led1, LOW);
          itsONled[0] = 0;
        } else {
          digitalWrite(led1, HIGH);
          itsONled[0] = 1;
        }
        break;

      case code3:
        if (itsONled[1] == 1) { // if first led is on then
          digitalWrite(led2, LOW); // turn it off when button is pressed
          itsONled[1] = 0; // and set its state as off
        } else { // else if first led is off
          digitalWrite(led2, HIGH); // turn it on when the button is pressed
          itsONled[1] = 1; // and set its state as on
        }
        break;

      case code4:
        if (itsONled[1] == 1) {
          digitalWrite(led2, LOW);
          itsONled[1] = 0;
        } else {
          digitalWrite(led2, HIGH);
          itsONled[1] = 1;
        }
        break;

      case code5:
        if (itsONled[2] == 1) {
          digitalWrite(led3, LOW);
          itsONled[2] = 0;
        } else {
          digitalWrite(led3, HIGH);
          itsONled[2] = 1;
        }
        break;

      case code6:
        if (itsONled[2] == 1) {
          digitalWrite(led3, LOW);
          itsONled[2] = 0;
        } else {
          digitalWrite(led3, HIGH);
          itsONled[2] = 1;
        }
        break;

      case code7:
        if (itsONled[3] == 1) {
          digitalWrite(led4, LOW);
          itsONled[3] = 0;
        } else {
          digitalWrite(led4, HIGH);
          itsONled[3] = 1;
        }
        break;

      case code8:
        if (itsONled[3] == 1) {
          digitalWrite(led4, LOW);
          itsONled[3] = 0;
        } else {
          digitalWrite(led4, HIGH);
          itsONled[3] = 1;
        }
        break;
    }
    Serial.println(value); // you can comment this line
    delay(500);
    irrecv.resume(); // Receive the next value
  }
}
