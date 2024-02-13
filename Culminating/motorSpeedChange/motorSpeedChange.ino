int motorPin = 3;
int potenPin = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int PWMoutput,potReading;

  potReading = analogRead(potenPin);
  PWMoutput = map(potReading,0,1023,0,255);
  analogWrite(motorPin,PWMoutput);

}
