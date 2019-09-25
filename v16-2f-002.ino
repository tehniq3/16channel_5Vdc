/**
 * Nokia 5110 Voltmeter 5V Analog
 * v. 1.0
 * Copyright (C) 2016 Robert Ulbricht
 * http://www.arduinoslovakia.eu
 *
 * 4 channel voltmeter.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * https://www.youtube.com/watch?v=EKS8Qhs1DoU
 * https://github.com/RoboUlbricht/arduinoslovakia/blob/master/nokia5110/voltmeter_5v_analog/voltmeter_5v_analog.ino
*/ 

//#include <Adafruit_GFX.h>
//#include <Adafruit_PCD8544.h>
#include <TFT_HX8357.h> // Hardware-specific library

TFT_HX8357 display = TFT_HX8357();       // Invoke custom library

#define TFT_GREY 0x5AEB

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

struct VoltmeterData {
  const int channel;
  const char name[3];
  double value;
};

VoltmeterData data[16]={
  {A0," 0",0.},  //aici pui intrarile analogie ce le folosesti
  {A1," 1",0.},
  {A2," 2",0.},
  {A3," 3",0.},
   {A4," 4",0.},
    {A5," 5",0.},
     {A6," 6",0.},
      {A7," 7",0.},
       {A8, " 8",0.},
        {A9," 9",0.},
         {A10,"10",0.},
          {A11,"11",0.},
          {A11,"12",0.},
          {A11,"13",0.},
          {A11,"14",0.},
          {A11,"15",0.},
};

char buffer[10];
const double vref=5.0;
const int samples=8;
//int adc[16]; 
//float volt[16];
//float vref = 5.0;  // reference voltage

void setup() {
 display.init();
  display.setRotation(2);
 // Serial.begin(57600); // For debug
  display.fillScreen(TFT_WHITE);
 Serial.begin(9600);
 display.setTextSize(2);
/* for (byte i = 54; i <= 69; i++) // A0...A15
{
  pinMode(i, INPUT);
}
*/
}

void loop() {
  measure(samples);
  drawVoltmeter();
  //display.fillScreen(random(0xFFFF));
  delay(200);
}

void measure(const int smp) {
  long d;
  for(int i=0;i<16;i++) {
    d=0;
    for(int x=0;x<smp;x++)
      d+=analogRead(data[i].channel);
    data[i].value= d * vref / 1023.0 / smp;
  }  
}

void drawVoltmeter() {
 // display.fillScreen(TFT_BLACK);
  display.setCursor(10,3);display.setTextSize(2);display.setTextColor(TFT_BLUE,TFT_WHITE);
  display.print("Voltmeter");
  display.setCursor(140,0);
  display.print("Range: 0-5V");//display.setTextSize(3);
  for(int i=0;i<16;i++) {
    display.setCursor(135,28*i+36);display.setTextColor(TFT_BLACK,TFT_WHITE);display.setTextSize(3);
    display.print(data[i].name);

     display.setCursor(300,28*i+36);display.setTextColor(TFT_BLACK,TFT_WHITE);display.setTextSize(3);
    display.print("V");
    display.setCursor(0,28*i+40);display.setTextColor(TFT_BLACK,TFT_WHITE);display.setTextSize(2);
    display.print("Acumulator:");
     display.setCursor(182,28*i+36);display.setTextColor(TFT_BLACK,TFT_WHITE);display.setTextSize(3);
    display.print("=");

    display.setCursor(217,28*i+36);
    dtostrf(data[i].value, 4, 2, buffer);
    display.print(buffer);

    // analog part
  /*  const int START=32;
    for(int j=0;j<=50;j+=2) {
      display.drawLine(START+j,8*i+16,START+j,8*i+(j%10==0 ? 18 : 17),TFT_BLACK);
      }
    display.drawLine(START,8*i+20,START+data[i].value*10,8*i+20,TFT_BLACK);
    display.drawLine(START,8*i+21,START+data[i].value*10,8*i+21,TFT_BLACK);
    display.drawLine(START,8*i+22,START+data[i].value*10,8*i+22,TFT_BLACK);
    */
  }
 // display.display();
}

