/**
 * HC-SR04 Demo
 * Demonstration of the HC-SR04 Ultrasonic Sensor
 * Date: August 3, 2016
 * 
 * Description:
 *  Connect the ultrasonic sensor to the Arduino as per the
 *  hardware connections below. Run the sketch and open a serial
 *  monitor. The distance read from the sensor will be displayed
 *  in centimeters and inches.
 * 
 * Hardware Connections:
 *  Arduino | HC-SR04 
 *  -------------------
 *    5V    |   VCC     
 *    7     |   Trig     
 *    8     |   Echo     
 *    GND   |   GND
 *  
 * License:
 *  Public Domain
 */
 
// Pins
const int TRIG_PIN = 13;
const int ECHO_PIN = 12;
const int vibromotor = 9;

// 60cm max distance
const float maxCM = 60.0;

void setup() {
  Serial.begin (9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  float duration;
  float distance;
  // send a short burst
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // measure duration of HIGH pulse in microseconds, timeout in 1 sec
  duration = pulseIn(ECHO_PIN, HIGH, 100000); 
  distance = measureDistance(duration); // get the distance in cm
  // vibrate if within range
  if (distance <= maxCM && distance > 0){
    analogWrite(vibromotor, 255);
  }
  else {
    analogWrite(vibromotor, 0);
  }
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}


// returns the distance based on delay
float measureDistance(float microseconds){
  float seconds = microseconds / 1000000; // convert microseconds to seconds 
  float meters = seconds * 343; // distance in meters using speed of sound (343m/s)
  float cm = meters * 100; // m to cm 
  cm = cm/2; // want the distance to obstacle not roundtrip
  return cm;
}
