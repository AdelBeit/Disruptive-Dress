#include <Wire.h> // Must include Wire library for I2C
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library
#include <Mouse.h>

const int sensitivity = 1;  // Higher sensitivity value = slower mouse, should be <= about 500

int vx,vy;
int mousePins[] = {6,7,8};
int mouseNames[] = {MOUSE_LEFT,MOUSE_MIDDLE,MOUSE_RIGHT};
int mouseStates[] = {0,0,0};

MMA8452Q accel;


void setup()
{
  Mouse.begin();
  Wire.begin();
  accel.init();
  Serial.begin(9600);
  Serial.print("ready");
  pinMode(mousePins[0],INPUT_PULLUP);
  pinMode(mousePins[1],INPUT_PULLUP);
  pinMode(mousePins[2],INPUT_PULLUP);
  delay(1000);
  
}

void loop()
{
  if(accel.available())
  {
    accel.read();
    delay(10);
    Mousemove();
    mouseClick(0);
    mouseClick(1);
    mouseClick(2);
  }
}

void Mousemove()
{
  vx = -(accel.cx)*50;
  vy = (accel.cy)*50;


  if(vx != 0)
  {
    Mouse.move(vx, 0, 0);  // move mouse on y axis
  }
  if(vy != 0)
  {
    Mouse.move(0, vy, 0);  // move mouse on y axis
  }
  
}

void mouseClick(int i)
{
  if ((!digitalRead(mousePins[i])) && (!mouseStates[i]))
  {
    Serial.println("click");
    mouseStates[i] = 1;
    Mouse.begin();
    Mouse.press(mouseNames[i]);
    delay(10);
  }
  else if((digitalRead(mousePins[i])) && (mouseStates[i]))
  {
    Serial.println("not pressed");
    mouseStates[i] = 0;
    Mouse.release(mouseNames[i]);
    delay(10);
  }
}
