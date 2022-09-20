#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

int Setup_Oled(int temperatura,int boia1,int boia2){
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);      // Tamanho de Fonte
  display.setTextColor(WHITE);
  display.clearDisplay();
  
  display.setCursor(15,5);
  display.print("Sensor de ");
  display.setCursor(15,15);
  display.print("temperatura");
  
  display.setCursor(15,25);
  if (isnan(temperatura))                     
    display.print("Medida Invalida!");       
  else 
   display.print("Medida Valida!");
  
  display.setCursor(15,40);
  display.print("Sensores de Boia");
  
  display.setCursor(15,50);
  if(boia1 == 1)
    display.print("excesso de Agua");
  else if(boia2 == 1)
    display.print("Falta de Agua");
  else
    display.print("OK..");
    display.display();
  return 1;
 }

 int wifi(int enter){
  display.clearDisplay();
  display.setCursor(50,10);
  display.print("Wifi");
  display.display();
  if (enter == 1)
  return 1;
  else 
  return 0;
}
