/******************************************************************************
Flex_Sensor_Example.ino
Example sketch for SparkFun's flex sensors
  (https://www.sparkfun.com/products/10264)
Jim Lindblom @ SparkFun Electronics
April 28, 2016

Create a voltage divider circuit combining a flex sensor with a 47k resistor.
- The resistor should connect from A0 to GND.
- The flex sensor should connect from A0 to 3.3V
As the resistance of the flex sensor increases (meaning it's being bent), the
voltage at A0 should decrease.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
const int FLEX_PIN = A0; // Pin connected to voltage divider output

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 10; // Measured resistance of 3.3k resistor, i'm actually using a 1.1k resistor

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg

unsigned long timestart = 0; // start time for measuring time
unsigned long measuredtime = 0; // end of measure time

float printtimer = 1;
int doprint = 1;
int i = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(FLEX_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
//  digitalWrite(LED_BUILTIN, HIGH);
//  delay(1000);
//  digitalWrite(LED_BUILTIN, LOW);
//  delay(1000);
  if(timestart == 0){
    timestart = millis();
  }
//   Read the ADC, and calculate voltage and resistance from it
  int flexADC = analogRead(FLEX_PIN);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 90.0);
  Serial.println("Resistance: " + String(flexR) + " ohms");
  Serial.println("Bend: " + String(angle) + " degrees");
  Serial.println();
  delay(500);
//  // if the flex sensor is activated then restart the timer
//  if(angle >= 10){
//    digitalWrite(LED_BUILTIN, LOW);
//    Serial.println("ITS MOVING");
//    if(doprint){
//      Serial.println("should be low");
//      doprint = 1 - doprint;
//      Serial.print(i);
//      Serial.println(" shouldve been a second now");
//      i = 0;
//    }
//    timestart = millis();
//  }
//  // check if measured time is bigger than 5 seconds
//  measuredtime = (millis() - timestart)/1000;
//  if(measuredtime >= 5){
//    digitalWrite(LED_BUILTIN, HIGH);
//  }
//  if((millis() - printtimer)/1000 >= 1){
//    doprint = 1 - doprint;
//    printtimer = millis();
//    i += 1;
//    Serial.print(i);
//    Serial.println(" ticks");
//  }
}
