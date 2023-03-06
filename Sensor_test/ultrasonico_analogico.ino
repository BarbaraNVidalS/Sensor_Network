unsigned int ADCValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  ADCValue = analogRead(0);
  ADCValue *= 3;
  Serial.print("Present lenght is: ");
  Serial.print(ADCValue, DEC);
  Serial.print("mm \n");
  delay(1000);
}
