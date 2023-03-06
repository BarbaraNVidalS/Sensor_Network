#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
 
// Constructor de la librería de LCD 16x2
// Aqui se configuran los pines asignados a la pantalla del PCF8574
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
unsigned int ADCValue;

void setup()
{
  // Indicar a la libreria que tenemos conectada una pantalla de 16x2
  lcd.begin(16, 2);
  // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.home ();
}

void loop() 
{
  ADCValue = analogRead(0);
  ADCValue *= 3;
  Serial.print("Present lenght is: ");
  Serial.print(ADCValue, DEC);
  Serial.print("mm \n");
  delay(500);
  
  int i;

  lcd.setCursor ( 0, 0 );
  lcd.print("Sensor analogico: ");
  lcd.setCursor ( 0, 1 );
  lcd.print(ADCValue);
  lcd.print(" mm");
  delay(60); 
}
