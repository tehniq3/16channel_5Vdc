/*
 * voltmeter with 16 channels on Arduino Mega
 * original sketch by Nicu FLORICA (niq_ro)for Mihai Brindusoiu
 * http;//www.arduinotehniq.com
 * v.0, initial, 21.09.2019, Galiciuica, Dolj, Romania
 */

int adc[16]; 
float volt[16];
float vref = 5.0;  // reference voltage

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
  delay(5);
}

 Serial.println("............................"); 
 delay(2000);

} // end loop
