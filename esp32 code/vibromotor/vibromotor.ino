#include <analogWrite.h>

/*
  LilyPad Vibe Board: Button Feedback
  Written by: Ho Yun "Bobby" Chan
  @ SparkFun Electronics
  Date: 1/14/2019
  https://www.sparkfun.com/products/11008

  The main code checks for a button press. If there is a button press,
  the Arduino turns on the LilyPad Vibe Board for haptic feedback.
  For a visual cue, the LED will turn on too. If not, the LED and
  motor will remain off.
*/

const int motorPin = 8;     // motor connected to PWM pin 9
const int motorPin2 = 10;     // motor connected to PWM pin 9
const int LED_BUILTIN = 2;

const int button_PIN = 8;

void setup() {

  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  int i = 500;
  digitalWrite(LED_BUILTIN,HIGH);
  analogWrite(motorPin,255);
//  analogWrite(motorPin,50);
//  Serial.println("1  ");
//  delay(i);
//  digitalWrite(LED_BUILTIN,LOW);
//  analogWrite(motorPin,90);
//  Serial.println("2  ");
//  delay(i);
//  digitalWrite(LED_BUILTIN,HIGH);
//  analogWrite(motorPin,100);
//  Serial.println("3  ");
//  delay(i);
//  digitalWrite(LED_BUILTIN,LOW);
//  analogWrite(motorPin,140);
//  Serial.println("4  ");
//  delay(i);
}
