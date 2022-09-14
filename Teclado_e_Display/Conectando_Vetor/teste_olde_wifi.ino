#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

#define SCREEN_WIDTH 128    // Largura do display em pixels
#define SCREEN_HEIGHT 64    // Altura do display em pixels
#define SCREEN_ADRESS 0X3C

#define PINO_BOIA 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const char  *ssid = "123";
char senha[13] = {'\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\0'};

int i, f_setup = 0, wiificheck = 0;
float temperatura = 21, hora = 10, minuto = 43;
int dir = 0, enter = 0, menu = 0;
char leitura;
  


void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);      // Tamanho de Fonte
  display.setTextColor(WHITE);
  display.clearDisplay();
  //Ira printar a verificaçao do sensor de boia e DHT
  display.display();
  delay(2000);

}
void loop() {
  display.clearDisplay();
  //print_linha();
  menu = Cursor( menu);
 
  if(leitura == 'w')
  {
    if(senha[menu] == '\n')
    senha[menu] = 48;
    else
    senha[menu]++;
  }
  if(leitura == 's')
  {
    if(senha[menu] == '\n')
    senha[menu] = '\n';
    else if(senha[menu] < 48)
    senha[menu] == 48;
    else
    senha[menu]--;
    
  }
  display.setCursor(10,0);
  display.print(senha[menu]);
  
  //Linha 
  display.setCursor(10, 32);
  display.print("_"); 
  display.setCursor(10, 30);
  display.print(senha[0]);
    
  display.setCursor(20, 32);
  display.print("_");
  display.setCursor(20, 30); 
  display.print(senha[1]);
    
  display.setCursor(30, 32);
  display.print("_");
  display.setCursor(30, 30);
  display.print(senha[2]);
    
  display.setCursor(40, 32);
  display.print("_");
   display.setCursor(40, 30);
  display.print(senha[3]);
    
  display.setCursor(50, 32);
  display.print("_");
   display.setCursor(50, 30);
  display.print(senha[4]);
    
  display.setCursor(60, 32);
  display.print("_");
   display.setCursor(60, 30);
  display.print(senha[5]);
    
  display.setCursor(70, 32);
  display.print("_");
   display.setCursor(70, 30);
  display.print(senha[6]);
    
  display.setCursor(80, 32);
  display.print("_");  
  display.setCursor(80, 30);
  display.print(senha[7]);
          
  display.setCursor(90, 32);
  display.print("_");
   display.setCursor(90, 30);
  display.print(senha[8]);
    
  display.setCursor(100, 32);
  display.print("_");
   display.setCursor(100, 30);
  display.print(senha[9]);
    
  display.setCursor(110, 32);
  display.print("_");
   display.setCursor(110, 30);
  display.print(senha[10]);
    
  display.setCursor(120, 32);
  display.print("_");
  display.setCursor(120, 30);
  display.print(senha[12]);
    
  //Leitura dos botoes
  leitura = Serial.read();   //Leitura de Botoes
  if (leitura == 'w')
    dir++;
  if (leitura == 's')
    dir--;
  if (leitura == 'a')
    menu--;
  if (leitura == 'd')
    menu++;
  if (leitura == 'e')
    enter = 1;



 display.display();
 if(leitura == 'e'){
 for(i = 0;i <= 12; i++){
 if(senha [i] == '\n')
 senha[i] = '\0';
 }
 WiFi.begin(ssid, senha);
 
 
 }
}

void print_linha(){
    display.setCursor(10, 32);
  display.print("_"); 
  display.setCursor(10, 30);
  display.print(senha[0]);
    
  display.setCursor(20, 32);
  display.print("_");
  display.setCursor(20, 30); 
  display.print(senha[1]);
    
  display.setCursor(30, 32);
  display.print("_");
  display.setCursor(30, 30);
  display.print(senha[2]);
    
  display.setCursor(40, 32);
  display.print("_");
   display.setCursor(40, 30);
  display.print(senha[3]);
    
  display.setCursor(50, 32);
  display.print("_");
   display.setCursor(50, 30);
  display.print(senha[4]);
    
  display.setCursor(60, 32);
  display.print("_");
   display.setCursor(60, 30);
  display.print(senha[5]);
    
  display.setCursor(70, 32);
  display.print("_");
   display.setCursor(70, 30);
  display.print(senha[6]);
    
  display.setCursor(80, 32);
  display.print("_");  
  display.setCursor(80, 30);
  display.print(senha[7]);
          
  display.setCursor(90, 32);
  display.print("_");
   display.setCursor(90, 30);
  display.print(senha[8]);
    
  display.setCursor(100, 32);
  display.print("_");
   display.setCursor(100, 30);
  display.print(senha[9]);
    
  display.setCursor(110, 32);
  display.print("_");
   display.setCursor(110, 30);
  display.print(senha[10]);
    
  display.setCursor(120, 32);
  display.print("_");
  display.setCursor(120, 30);
  display.print(senha[11]);
    
 
  
}
int Cursor(int menu){
   if (menu <= 0 ) //Limite de tela para o cursor
    menu = 0;
  if (menu >= 11 ) //Limite de tela para o cursor
    menu = 11;
  display.setCursor(10 + (10 * menu), 31);
  display.print("_");
  return menu;
}
