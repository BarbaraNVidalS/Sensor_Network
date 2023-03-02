const int infraPin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(infraPin, INPUT);

}

void loop() {
  int value = 0;
  value = digitalRead(infraPin);

  if(value == HIGH) {
    Serial.println("Obstaculo NO detectado");
  } else {
    Serial.println("Obstaculo detectado");
  }

    delay(1000);

}
