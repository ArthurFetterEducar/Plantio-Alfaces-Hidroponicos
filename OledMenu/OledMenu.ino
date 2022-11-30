#include "OledMenu.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int menu;


void setup(){
Serial.begin(9600);
Setup_Oled(1,1,1);
PrintOled();
delay(2000);
}

void loop() {
  ClearOled();
  menu =  Botao(menu);
  if(menu == 0)
  Menu1(0,0,0,0);
  else if(menu == 1)
  Menu2(1,1);
  else if(menu == 2)
  Menu3(1,1,1);
  else if(menu == -1)
  MenuHora(1,1);  
  PrintOled();
   
  

}
