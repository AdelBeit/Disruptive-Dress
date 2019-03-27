/******************************************************************************
https://github.com/sparkfun/MMA8452_Accelerometer

Hardware hookup:
  Arduino --------------- MMA8452Q Breakout
    3.3V  ---------------     3.3V
    GND   ---------------     GND
  SDA (A4) --\/330 Ohm\/--    SDA
  SCL (A5) --\/330 Ohm\/--    SCL
******************************************************************************/

#include <Wire.h> // Must include Wire library for I2C
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library

// Begin using the library by creating an instance of the MMA8452Q
//  class. We'll call it "accel". That's what we'll reference from
//  here on out.
MMA8452Q accel;

int led1 = 2;
int led2 = 3;

int tolerance=20; // Sensitivity of the Alarm
boolean calibrated=false; // When accelerometer is calibrated - changes to true 
boolean moveDetected=false; // When motion is detected - changes to true

//Accelerometer limits
int xMin; //Minimum x Value
int xMax; //Maximum x Value
int xVal; //Current x Value

int yMin; //Minimum y Value
int yMax; //Maximum y Value
int yVal; //Current y Value

int zMin; //Minimum z Value
int zMax; //Maximum z Value
int zVal; //Current z Value


void setup()
{
  Wire.begin();
  Serial.begin(9600);
  accel.init();
  Serial.println("PULL THE LEVER");
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop()
{
  // accel.available() waits for new data
  //  from the accelerometer.
  if (accel.available())
  {
    // read the new variables:
    accel.read();
    if(!calibrated)
    {
      calibrateAccel();
    }
//    printCalculatedAccels();
//    printOrientation();

    Serial.println(); // Print new line every time.
    
    
    // If the button is pressed, initialise and recalibrate the Accelerometer limits.
    if(accel.readPL() == PORTRAIT_D)
    {
      calibrateAccel();
    }
    
    // Once the accelerometer is calibrated - check for movement 
    if(calibrated)
    {
      if(checkMotion())
      {
        moveDetected = true;
      }
    }
    
    // If motion is detected - sound the alarm !
    if(moveDetected)
    {
      Serial.println("ALARM");
      ALARM();
      delay(1000);
    }
  }
}

//This is the function used to sound the buzzer
void buzz(int reps, int rate){
 for(int i=0; i<reps; i++){
 analogWrite(buzzerPin,900);
 delay(100);
 analogWrite(buzzerPin,0);
 delay(rate);
 }
} 




// Function used to calibrate the Accelerometer
void calibrateAccel(){
 // reset alarm
 moveDetected=false;
 
 //initialise x,y,z variables
 xVal = analogRead(x);
 xMin = xVal;
 xMax = xVal;
 
 yVal = analogRead(y);
 yMin = yVal;
 yMax = yVal;
 
 zVal = analogRead(z);
 zMin = zVal;
 zMax = zVal;
 
 // Calibration sequence initialisation sound - 3 seconds before calibration begins
 buzz(3,1000);
 
 //calibrate the Accelerometer (should take about 0.5 seconds)
 for (int i=0; i<50; i++){
 // Calibrate X Values
 xVal = analogRead(x);
 if(xVal>xMax){
 xMax=xVal;
 }else if (xVal < xMin){
 xMin=xVal;
 }

 // Calibrate Y Values
 yVal = analogRead(y);
 if(yVal>yMax){
 yMax=yVal;
 }else if (yVal < yMin){
 yMin=yVal;
 }

 // Calibrate Z Values
 zVal = analogRead(z);
 if(zVal>zMax){
 zMax=zVal;
 }else if (zVal < zMin){
 zMin=zVal;
 }

 //Delay 10msec between readings
 delay(10);
 }
 
 //End of calibration sequence sound. ARMED.
 buzz(3,40);
 printValues(); //Only useful when connected to computer- using serial monitor.
 calibrated=true;
 
}

//Function used to detect motion. Tolerance variable adjusts the sensitivity of movement detected.
boolean checkMotion(){
  boolean validate=false;
  xVal = analogRead(x);
  yVal = analogRead(y);
  zVal = analogRead(z);
  
  if(xVal >(xMax+tolerance)||xVal < (xMin-tolerance))
  {
    validate=true;
    Serial.print("X Failed = ");
    Serial.println(xVal);
  }
  
  if(yVal >(yMax+tolerance)||yVal < (yMin-tolerance))
  {
    validate=true;
    Serial.print("Y Failed = ");
    Serial.println(yVal);
  }
  
  if(zVal >(zMax+tolerance)||zVal < (zMin-tolerance))
  {
    validate=true;
    Serial.print("Z Failed = ");
    Serial.println(zVal);
  }
 
 return validate;
}

//Function used to blink the LED.
void ALARM(){
  
  //don't check for movement until recalibrated again
  calibrated=false;
  
  // sound the alarm and blink LED
  digitalWrite(led1, HIGH);
  delay(100);
  digitalWrite(led1, LOW);
}

// Prints the Sensor limits identified during Accelerometer calibration.
// Prints to the Serial monitor.
void printValues(){
  Serial.print("xMin=");
  Serial.print(xMin);
  Serial.print(", xMax=");
  Serial.print(xMax);
  Serial.println();
  
  Serial.print("yMin=");
  Serial.print(yMin);
  Serial.print(", yMax=");
  Serial.print(yMax);
  Serial.println();
  
  Serial.print("zMin=");
  Serial.print(zMin);
  Serial.print(", zMax=");
  Serial.print(zMax);
  Serial.println();
  
  Serial.println("------------------------");
}

void printAccels()
{
  Serial.print("x: ");
  Serial.print("\t");
  Serial.print(accel.x, 3);
  Serial.print("\t");
  Serial.print("y: ");
  Serial.print("\t");
  Serial.print(accel.y, 3);
  Serial.print("\t");
  Serial.print("z: ");
  Serial.print("\t");
  Serial.print(accel.z, 3);
  Serial.print("\t");
}

void printCalculatedAccels()
{ 
  Serial.print("x: ");
  Serial.print(accel.cx, 3);
  Serial.print("\t");
  Serial.print("y: ");
  Serial.print(accel.cy, 3);
  Serial.print("\t");
  Serial.print("z: ");
  Serial.print(accel.cz, 3);
  Serial.print("\t");
}

void printOrientation()
{
  byte pl = accel.readPL();
  switch (pl)
  {
    case PORTRAIT_U:
      Serial.print("Portrait Up");
      break;
    case PORTRAIT_D:
      Serial.print("Portrait Down");
      break;
    case LANDSCAPE_R:
      Serial.print("Landscape Right");
      break;
    case LANDSCAPE_L:
      Serial.print("Landscape Left");
      break;
    case LOCKOUT:
      Serial.print("Flat");
      break;
  }
}
