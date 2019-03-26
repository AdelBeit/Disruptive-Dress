int pins[] = {13,12,11};

void setup()
{
  Serial.begin(9600);
  Serial.print("ready");
  pinMode(pins[0],INPUT_PULLUP);
  pinMode(pins[1],INPUT_PULLUP);
  pinMode(pins[2],INPUT_PULLUP);
  delay(1000);
  
}

void loop()
{
 check(pins[0]);
 check(pins[1]);
 check(pins[2]);
}

void check(int pin){
  if(!digitalRead(pin)){
    Serial.println(pin);
  }
}
