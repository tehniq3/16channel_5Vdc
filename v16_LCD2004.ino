/*
 * voltmeter with 16 channels on Arduino Mega
 * original sketch by Nicu FLORICA (niq_ro)for Mihai Brindusoiu
 * http;//www.arduinotehniq.com
 * v.0, initial, 21.09.2019, Galiciuica, Dolj, Romania
 * v.1, add lcd 2004
 */

int adc[16]; 
float volt[16];
float vref = 5.0;  // reference voltage

/*
 LCD2004 - Arduino Mega circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
for (byte i = 54; i <= 69; i++) // A0...A15
{
  pinMode(i, INPUT);
}
 Serial.println(" "); 
 Serial.println("voltmeter with 16 channels on Arduino Mega"); 
 Serial.println("by Nicu FLORICA (niq_ro)"); 
 Serial.println("............................"); 
 lcd.begin(20, 4);  // set up the LCD's number of columns and rows:
 lcd.clear(); // clear the screen
} // end setup

void loop() {

for (byte i = 0; i <= 16; i++) 
{
  adc[i] = analogRead(i+53);
  volt[i] = adc[i]*vref/1024.;
  Serial.print("Batterry no. ");
  Serial.print(i);
  Serial.print(" = ");
  Serial.print(volt[i]);
  Serial.println("V");
  lcd.setCursor(5*(i%4),i/4);
  lcd.print(volt[i],1);
  lcd.print("V");
  delay(5);
}

 Serial.println("............................"); 
 delay(2000);
 lcd.clear();

} // end loop
