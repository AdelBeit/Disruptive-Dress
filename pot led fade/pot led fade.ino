int led = 11;
int pot = A0;
int potread;
int ledval;

void setup() {
  pinMode(pot, INPUT);
  pinMode(led, OUTPUT);
  
}

void loop() {
  potread = analogRead(pot);
  ledval = (255/1023.0)*potread;
  analogWrite(led,ledval);

}
