#include "OledMenu.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void setup(){
Serial.begin(9600);
Setup_Oled(1,1,1);
delay(2000);

}

void loop() {
  wifi(0);
}
