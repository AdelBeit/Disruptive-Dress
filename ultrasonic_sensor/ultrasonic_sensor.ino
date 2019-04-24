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
const int TRIG_PIN = 12;
const int ECHO_PIN = 13;
const int vibromotor = 10;
const int vibromotor2 = 11;

// 60cm max distance
const float maxCM = 60.0;
const float maxIN = 36;

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
  distance = measureDistanceIN(duration); // get the distance in cm
  // vibrate if within range
  Serial.print("distance: ");
  Serial.print(distance);
  Serial.print("in  ");
  if (distance <= maxIN && distance > 0){
    Serial.println("too close!");
    int vibPower = map(distance, maxIN, 0, 150, 255);
    Serial.println(vibPower);
    analogWrite(vibromotor, vibPower);
    analogWrite(vibromotor2, vibPower);
  }
  else {
    Serial.println("you're good...");
    analogWrite(vibromotor, 0);
    analogWrite(vibromotor2, 0);
  }
//  Serial.println(" cm");
  delay(500);
}


// returns the distance based on delay
float measureDistanceCM(float microseconds){
  float seconds = microseconds / 1000000; // convert microseconds to seconds 
  float meters = seconds * 343; // distance in meters using speed of sound (343m/s)
  float cm = meters * 100; // m to cm 
  cm = cm/2; // want the distance to obstacle not roundtrip
  return cm;
}

// returns the distance based on delay
float measureDistanceIN(float microseconds){
  int in = measureDistanceCM(microseconds) * 0.393701;
  return in;
}
