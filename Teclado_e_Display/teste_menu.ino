#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


int selected = 0;
int entered = -1;

void displaymenu(void) {

  int down = digitalRead(2);
  int up = digitalRead(3);
  int enter = digitalRead(4);
  int back = digitalRead(5);

  if(up == HIGH && down == HIGH){
    Serial.println("Don't press both buttons at the same time");
  };
  
  if(up == HIGH) {
    selected = selected + 1;
    delay(50);
  };
  
  if(down == HIGH) {
    selected = selected - 1;
    delay(50);
  };

  if(enter == HIGH) {
    entered = selected;
  };

  if(back == HIGH) {
    entered = -1;
  };
  Serial.println(entered);
  const char *options[7] = { 
    " Menu option 1 ", 
    " Menu option 2 ", 
    " Menu option 3 ", 
    " Menu option 4 ",
    " Menu option 5 ",
    " Menu option 6 ",
    " Menu option 7 " 
  };
  
  if(entered == -1) {
    display.clearDisplay();
    display.setTextSize(1);             
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println(F("Custom menu test"));
    display.println("");
    for(int i=0;i < 7; i++) {
      if(i == selected) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.println(options[i]);
      } else if(i != selected){
        display.setTextColor(SSD1306_WHITE);
        display.println(options[i]);
      }
    }
  } else if(entered == 0) {
      display.clearDisplay();
      display.setTextSize(1);             
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0,0);
      display.println(F("Custom menu test"));
      display.println("Menu option 1");
      display.setTextColor(SSD1306_WHITE);
      display.setTextSize(2);
      display.println("Some cool stuff");
  } else if(entered == 1) {
      display.clearDisplay();
      display.setTextSize(1);             
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0,0);
      display.println(F("Custom menu test"));
      display.println("Menu option 2");
      display.setTextColor(SSD1306_WHITE);
      display.setTextSize(2);
      display.println("More cool stuff :)");
  }
  display.display();
}

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  displaymenu();
}
