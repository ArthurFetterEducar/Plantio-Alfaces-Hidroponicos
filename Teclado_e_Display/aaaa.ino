#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // Largura do display em pixels
#define SCREEN_HEIGHT 64    // Altura do display em pixels
#define SCREEN_ADRESS 0X3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int i;



void setup() {
   Serial.begin(9600);


  
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();

 display.setTextSize(2);
  display.setTextColor(WHITE);


}

void loop() {
    display.setCursor(0, 0);
    display.print("a");
    display.display();
    for(i = 1;i<11;i++)
    display.drawPixel(i, 15, SSD1306_WHITE);
    

    
    

}
