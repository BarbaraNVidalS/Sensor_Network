//Reference: https://github.com/sparkfun/HC-SR04_UltrasonicSensor.git
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include <DHT.h>

//Definicion de tipo de sensor DHT
#define DHTTYPE DHT11
#define DHTPIN 10

DHT dht(DHTPIN, DHTTYPE);
float humidity, temperature;

// Pins
const int TRIG_PIN = 7;
const int ECHO_PIN = 8;
const int INFRA_PIN = 9;//infrarrojo
const int LEDPin= 13;
const int PIRPin= 4;
unsigned int ADCValue; // analogico

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;

void setup() {
  
  pinMode(LEDPin, OUTPUT);
  pinMode(PIRPin, INPUT);
  pinMode(INFRA_PIN, INPUT);
  
  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  //Set Echo pin as input to measure the duration of 
  //pulses coming back from the distance sensor
  pinMode(ECHO_PIN, INPUT);

  // We'll use the serial monitor to view the sensor output
  Serial.begin(9600);

  // Indicar a la libreria que tenemos conectada una pantalla de 16x2
  lcd.begin(16, 2);
  // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.home ();

  dht.begin();
}

void loop() {
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float inches;
  int value = 0; // infrarrojo
  
  //SENSOR INFRARROJO
  value = digitalRead(INFRA_PIN);

  if(value == HIGH){
    lcd.setCursor(0,0);
    lcd.print("NO obstaculo");
    delay(1000);
    lcd.clear();
    } else {
      lcd.setCursor(0,0);
      lcd.print("Obstaculo");
      delay(1000);
      lcd.clear();
    }

  //DHT11
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  lcd.setCursor(0,0);
  lcd.print("Humedad = ");
  lcd.setCursor(0,1);
  lcd.print(humidity);
  delay(1000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Temperatura = ");
  lcd.setCursor(0,1);
  lcd.print(temperature);
  delay(1000);
  lcd.clear();

  //ULTRASONICO ANALOGICO
  ADCValue = analogRead(0);
  ADCValue *= 3;
  lcd.setCursor(0,0);
  lcd.print("Distancia Analogico ");
  lcd.setCursor(0,1);
  lcd.print(ADCValue, DEC);
  lcd.print(" mm");
  delay(1000);
  lcd.clear();
  
  //PIR
  int val = digitalRead(PIRPin);
  if (val == HIGH) {
    digitalWrite(LEDPin, HIGH);
    delay(1000);
    digitalWrite(LEDPin, LOW);
    delay(1000);
  }
  else {
    digitalWrite(LEDPin, LOW);
  }
  
  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed
  //of sound in air at sea level (~340 m/s).
  cm = pulse_width / 58.0;
  inches = pulse_width / 148.0;

  // Print out results
  if ( pulse_width > MAX_DIST ) {
    Serial.println("Out of range");
  } else {
    Serial.print(cm);
    Serial.print(" cm \t");
    Serial.print(inches);
    Serial.println(" in");
  }
   // Wait at least 60ms before next measurement
  delay(60);

  lcd.setCursor ( 0, 0 );
  lcd.print("Distancia Digital");
  // Mover el cursor a la segunda linea (1) primera columna
  lcd.setCursor ( 0, 1 );
  lcd.print(cm);
  lcd.print(" cm");
  // Esperar un segundo
  delay(2000);
  lcd.clear();
}
