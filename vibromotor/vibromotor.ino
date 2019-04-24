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

const int motorPin = 11;     // motor connected to PWM pin 9
const int motorPin2 = 10;     // motor connected to PWM pin 9
const int led = 11;

const int button_PIN = 8;

void setup() {
  pinMode(button_PIN, INPUT_PULLUP);
  pinMode(led,OUTPUT);
  delay(300);
  Serial.begin(9600);

}

void loop() {
//  analogWrite(motorPin, 255);  //turn motor on
//  analogWrite(motorPin2,255);
//  digitalWrite(led,HIGH);
//  if(!digitalRead(button_PIN)){
//    analogWrite(motorPin, 255);  //turn motor on
//  }
//  else{
//    analogWrite(motorPin,0);
//  }
  for(int i=0; i<255;i+=10){
    analogWrite(motorPin,i);
    delay(200);
    Serial.println(i);
  }
}
