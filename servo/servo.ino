#include <Servo.h>

Servo servo1;

uint32_t next;

const int servo_PIN = 11;

void setup()
{
  // the 1000 & 2000 set the pulse width 
  // mix & max limits, in microseconds.
  // Be careful with shorter or longer pulses.
  servo1.attach(servo_PIN);//, 1000, 2000);
  Serial.begin(9600);
  next = millis() + 500;
}

void loop()
{
  int i = 500;
  servo1.write(180);
  delay(i);
  servo1.write(0);
  delay(i);
//  static bool rising = true;
//
//  if(millis() > next)
//  {
//    if(rising)
//    {
//      servo1.write(180);
//      rising = false;
//    }
//    else
//    {
//      servo1.write(0);
//      rising = true;
//    }
//
//    // repeat again in 3 seconds.
//    next += 3000;
//  }
//  for(int i=0; i<180; i+=20){
//    Serial.println(i);
//    servo1.write(i);
//    delay(1000);
//  }
}
