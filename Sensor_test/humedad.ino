#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 10

DHT dht(DHTPIN, DHTTYPE);
float humidity, temperature;

void setup() {
  Serial.begin(9600);
  dht.begin();

}

void loop() {
  delay(1000);
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  

}
