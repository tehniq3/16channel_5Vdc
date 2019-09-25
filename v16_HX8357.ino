/*
 * voltmeter with 16 channels on Arduino Mega
 * original sketch by Nicu FLORICA (niq_ro)for Mihai Brindusoiu
 * http;//www.arduinotehniq.com
 * v.0, initial, 21.09.2019, Galiciuica, Dolj, Romania
 * v.1, add lcd 2004
 * v.2, add TFT HX8357 display
 */

int adc[16]; 
float volt[16];
float vref = 5.0;  // reference voltage

#include <TFT_HX8357.h> // Hardware-specific library
TFT_HX8357 tft = TFT_HX8357();       // Invoke custom library
#define TFT_GREY 0x5AEB // New colour

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
  tft.init();
  tft.setRotation(2);
} // end setup

void loop() {
  tft.setCursor(0, 0, 4); // Set "cursor" at top left corner of display (0,0) and select font 4
 // a background colour defined
  tft.fillScreen(random(0xFFFF));
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setTextFont(4);
//  tft.setTextFont(2);
    
for (byte i = 0; i <= 16; i++) 
{
  adc[i] = analogRead(i+53);
  volt[i] = adc[i]*vref/1024.;
  Serial.print("Batterry no. ");
  Serial.print(i);
  Serial.print(" = ");
  Serial.print(volt[i]);
  Serial.println("V");
  tft.print("Bat. ");
  if (i<9) tft.print(" ");
  tft.print(i+1);
  tft.print(" = ");
  tft.print(volt[i]);
  tft.println("V");
  delay(5);
}
 Serial.println("............................"); 
 delay(2000);

} // end loop
