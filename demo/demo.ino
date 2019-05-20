//#include <analogWrite.h>
//
//#include <ESP32_Servo.h>

#include <Servo.h>

/**
 * Ultrasonic sensor: HC-SR04 
 * 
 */

// Ultrasonic sensor ------------------
unsigned long UltraStartTime = 0; // start time for measuring time
unsigned long UltraMeasuredTime = 0; // end of measure time
int uDelay = 500; // delay time for measuring distance
float duration;
float distance;

// vibroMotor ------------------
// different intensities for different distances, [distance feet,power] 
int stage1[] = {1,200};
int stage2[] = {2,170};
int stage3[] = {3,140};
int vibLow = 140;
int vibHigh = 200;


// Pins
const int TRIG_PIN = 8;
const int ECHO_PIN = 7;
const int vibroMotor = 10;
//const int vibroMotor2 = 10;

// 60cm max distance
const float maxCM = 60.0;
const float maxIN = 36;

// Servo ------------------
Servo backServo;
uint32_t next;
const int servo_PIN = 2;
// triggers servo
bool triggerServo = true; // triggers activating servo
bool openServo = true; // alternates between open and closed states of servo
int servoMovementInterval = 100; // delay between moving back and forth for the servo
int servoPos = 0; // position of the servo, used for continous servo movement
int Speed = 50; // used to determine speed of continous servo movement

// Felx ------------------
const int AngleChangeThreshold = 3; // angle at which movement is detected
const int FLEX_PIN = A0; // Pin connected to voltage divider output

int fDelay = 1000; // delay time for measuring bend angle

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 46300; // 47k, measured to 46.3k
//const float R_DIV = 20000; // Measured resistance of 3.3k resistor, i'm actually using a 1.1k resistor

int flexADC;
float flexV;
float flexR;

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg

unsigned long FlexStartTime = 0; // start time for measuring time
unsigned long FlexMeasuredTime = 0; // end of measure time

int inactivityInterval = 10000; // 5 seconds of inactivity will freak out the dress
int lastAngle = 0; // keeps track of most recent angle
float angle = 0;

// print statements
bool printFlex = false;
bool printedFlex = false; // dont double print flex
bool printUltra = true;
bool printVibro = true;
bool printServo = false;

void setup() {
//  Serial.begin (9600);
//  // Ultrasonic sensor
//  pinMode(TRIG_PIN, OUTPUT);
//  pinMode(ECHO_PIN, INPUT);
//  
//  // Servo
//  backServo.attach(servo_PIN);
//
//  // Flex 
//  pinMode(FLEX_PIN, INPUT);
}

void loop() {
  analogWrite(10,200);
  // Ultrasonic Sensor and vibroMotors -------------  
//  UltraMeasuredTime = millis() - UltraStartTime; 
//  if(UltraStartTime == 0){
//    UltraStartTime = millis();
//    UltraMeasuredTime = uDelay;
//  }
//  // triggers every delay seconds 
//  if(UltraMeasuredTime >= uDelay){
//    UltraStartTime = millis();
//    // send a short burst
//    digitalWrite(TRIG_PIN, LOW);
//    delayMicroseconds(2);
//    digitalWrite(TRIG_PIN, HIGH);
//    delayMicroseconds(10);
//    digitalWrite(TRIG_PIN, LOW);
//    // measure duration of HIGH pulse in microseconds, timeout in 1 sec
//    duration = pulseIn(ECHO_PIN, HIGH, 100000); 
//    distance = measureDistanceIN(duration); // get the distance in cm
//    // vibrate if within range
//    if(printUltra){
//      Serial.print("distance: ");
//      Serial.print(distance);
//      Serial.print("in  ");
//  //  Serial.print(" cm");
//    }
//    if (distance <= maxIN and distance > 0){
//      if(printUltra) Serial.println("too close! Vibrate!");
//      int vibPower;
//      vibPower = map(floor(int(distance)/12), (maxIN/12)-1, 0, vibLow, vibHigh);
//      if(printVibro) Serial.print("power: ");
//      if(printVibro) Serial.println(vibPower);
////      Serial.println(vibPower);
////      Serial.print("distance: ");
////      Serial.println(floor(int(distance)/12));
////      vibPower = Vibrate(distance);
////      analogWrite(vibroMotor,vibPower);
//      analogWrite(vibroMotor,200);
////      analogWrite(vibroMotor2,vibPower);
//      
//    }
//    else {
//      if(printUltra) Serial.println("you're good...");
//      analogWrite(vibroMotor, 0);
////      analogWrite(vibroMotor2, 0);
////      Vibrate(distance);
//    }
//  }
//
//  // Flex and Servo -------------
//  if(FlexStartTime == 0){
//    FlexStartTime = millis();
//  }
//
//  // Read the ADC, and calculate voltage and resistance from it
//  flexADC = analogRead(FLEX_PIN);
//  flexV = flexADC * VCC / 1023.0;
//  flexR = R_DIV * (VCC / flexV - 1.0);
//  
//  // measure the amount of time that has passed
//  FlexMeasuredTime = (millis() - FlexStartTime);
//  if(FlexMeasuredTime % fDelay == 0){
//      
//    // Use the calculated resistance to estimate the sensor's
//    // bend angle:
//    lastAngle = angle;
//    angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,0, 90.0);
//    float angleChange = abs(lastAngle - angle); // keeps track of amount of change in angle
//
//    printedFlex = false;
//    // if the flex sensor is activated then restart the timer
//    if(angleChange > AngleChangeThreshold){
//      FlexStartTime = millis();
//      triggerServo = false;
//      if(printFlex){
//        Serial.println("++++++++++ movement detected, stop moving +++++++++");
////        Serial.println("Bend: " + String(angle) + " degrees");
//        Serial.print("Angle changed by: ");
//        Serial.println(angleChange);
//        Serial.println();
//        printedFlex = true;
//      }
//    }
//    
//    // print flex sensor angle
//    if(printFlex and !printedFlex){
////      Serial.println("Resistance: " + String(flexR) + " ohms");
////      Serial.println("Bend: " + String(angle) + " degrees");
//      Serial.print("Angle changed by: ");
//      Serial.println(angleChange);
//      Serial.println();
//    }
//  }
//  
//  // if enough time has passed activate the servos
//  if(FlexMeasuredTime >= inactivityInterval and FlexMeasuredTime%fDelay == 0){
//    if(printFlex)Serial.println("----------- no movement yet, freaking out -----------");
//    triggerServo = true;
//  }
//
//  if(FlexMeasuredTime%servoMovementInterval==0){
//    // no movement detected, go crazy!
//    if(triggerServo){
////      Speed = -2;
//      // move the servo
//      if(servoPos>100){
//        Speed = -25;
//        if(printServo){
//          Serial.print("moving to ");
//          Serial.println(servoPos);
//        }
//      }
//      if(servoPos<0){
//        Speed = 25;
//        if(printServo){
//          Serial.print("moving to ");
//          Serial.println(servoPos);
//        }
//      }
//    }
//    // movement detected, go slow
//    else{
////      Speed = -25;
//      // move the servo
//      if(servoPos>100){
//        Speed = -2;
//        if(printServo){
//          Serial.print("moving to ");
//          Serial.println(servoPos);
//        }
//      }
//      if(servoPos<0){
//        Speed = 2;
//        if(printServo){
//          Serial.print("moving to ");
//          Serial.println(servoPos);
//        }
//      }
//    }
//    
//    servoPos += Speed;
//    backServo.write(servoPos);
////    if(printFlex){
////      Serial.print("moving to ");
////      Serial.println(servoPos);
////    }
//   }
//  
//
//  // if movement is detected do this every 200 miliseconds
////  if(triggerServo and FlexMeasuredTime%servoMovementInterval == 0){
//    // when the time is right and the servo trigger is true then open and close the servo
////    if(openServo){
////      backServo.write(80); // move back to neutral position
////      openServo = 1 - openServo;
////    }else{
////      backServo.write(0); // extend back
////      openServo = 1 - openServo;
////    }
////  }
//  // when it's not supposed to move, move it back to neutral position
////  if(!triggerServo){
////    backServo.write(0);
////  }
//
////  delay(500);
//}
//
//// returns the distance based on delay
//float measureDistanceCM(float microseconds){
//  float seconds = microseconds / 1000000; // convert microseconds to seconds 
//  float meters = seconds * 343; // distance in meters using speed of sound (343m/s)
//  float cm = meters * 100; // m to cm 
//  cm = cm/2; // want the distance to obstacle not roundtrip
//  return cm;
//}
//
//// returns the distance based on delay
//float measureDistanceIN(float microseconds){
//  int in = measureDistanceCM(microseconds) * 0.393701;
//  return in;
//}
//
//// return intensity of vibroMotor given distance from ultrasonic sensor
//int Vibrate(float distance){
//  if(distance > 0 and distance <= stage1[0]*12){
////   analogWrite(vibroMotor,stage1[1]);
////   analogWrite(vibroMotor2,stage1[1]);
//   if(printVibro) Serial.println("========== stage 1 ==========");
//   return stage1[1];
//  } else if(distance > stage1[0]*12 and distance <= stage2[0]*12){
////   analogWrite(vibroMotor,stage2[1]);
////   analogWrite(vibroMotor2,stage2[1]);
//   if(printVibro) Serial.println("========== stage 2 ==========");
//   return stage2[1];
//  }else if(distance > stage2[0]*12 and distance <= stage3[0]*12){
////   analogWrite(vibroMotor,stage3[1]);
////   analogWrite(vibroMotor2,stage3[1]);
//   if(printVibro) Serial.println("========== stage 3 ==========");
//   return stage3[1];
//  }else{
////   analogWrite(vibroMotor,0);
////   analogWrite(vibroMotor2,0);
//   if(printVibro) Serial.println("========== stage 0 ==========");
//   return 0;
//  }
}
