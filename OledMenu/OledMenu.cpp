#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128    // Largura do display em pixels
#define SCREEN_HEIGHT 64    // Altura do display em pixels
#define SCREEN_ADRESS 0X3C

#define BOTAODIR 26
#define BOTAOESQ 25

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

 bool b1,b2;


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
   
  return 1;
 }

//==============================================================================

void Menu1(int TrocaAgua,int TrocaAbs,int boia1,int boia2){
  display.setCursor(30,0);
  display.print("Abastecimento");
  
  display.setCursor(15,10);
  display.print("( )Adicionar Agua");
  display.setCursor(21,0);
  if(boia1 == 1)
  display.print("X");
  else
  display.print(" ");

  display.setCursor(15,20);
  display.print("( )Retirar Agua");
  display.setCursor(21,20);
  if(boia2 == 1)
  display.print("X");
  else
  display.print(" ");

  display.setCursor(15,30);
  display.print("( )Troca De Agua ");
  display.setCursor(21,30);
  if(TrocaAgua == 1)
  display.print("X");
  else
  display.print(" ");
  
  
  display.setCursor(15,40);
  display.print("( )Troca De ");
  display.setCursor(16,50);
  display.print("Nutriente");
  display.setCursor(21,40);
  if(TrocaAbs == 1)
  display.print("X");
  else 
  display.print(" ");

  display.setCursor(0,30);
  display.print("<");
  
  display.setCursor(120,30);
  display.print(">");
}

//==========================================================================================
void Menu2(int aquecimento,int bomba){
  display.setCursor(15,0);
  display.print("Funcionamento");
  display.setCursor(15,10);
  display.print("Da estufa!");
  
  display.setCursor(15,20);
  display.print("Aquecimento");
  display.setCursor(15,30);
  if(aquecimento == 1)
  display.print("Desligado");
  else 
  display.print("Ligado");
  
  display.setCursor(15,40);
  display.print("Bomba");
  display.setCursor(15,50);
  if(bomba == 1)
  display.print("Desligado");
  else 
  display.print("Ligado");

  display.setCursor(0,30);
  display.print("<");
  
  display.setCursor(120,30);
  display.print(">");
}

  //======================================================================================
  void Menu3(int temperatura,int lm1,int lm2){  
  display.setCursor(15,0);
  display.print("Temperatura da");

  display.setCursor(15,10);
  display.print("Estufa:");
  
  display.setCursor(60,10);
  display.print(temperatura);


   display.setCursor(0,30);
  display.print("<");
  }
  //===========================================================================================
  void MenuHora(int hora,int minuto){
  display.setTextSize(2);
  display.setCursor(25,20);
  display.print("Hora");
  
  display.setCursor(25,40);
  display.print(hora);
  display.setCursor(50,40);
  display.print(":");
  display.setCursor(65,40);
  display.print(minuto);  
  
  display.setTextSize(1);
  display.setCursor(0,30);

  
  
  display.setCursor(120,30);
  display.print(">");
  
}
void MenuSonar(int sonar){
display.setTextSize(2);
display.print(sonar);
display.setTextSize(1);

}
//==============================================================================================
void PrintOled(){
  
  display.display();
}

void ClearOled(){
  display.clearDisplay();
}

int Botao(int menu){
  pinMode(BOTAODIR , INPUT_PULLUP);
  pinMode(BOTAOESQ , INPUT_PULLUP);
  if(digitalRead(BOTAOESQ) == 0 && b1 == 0){
    menu++;
    b1 = 1;
  }
  if(digitalRead(BOTAOESQ) == 1) b1 = 0;
  if(digitalRead(BOTAODIR) == 0 && b2 == 0){
  menu--;
  b2 = 1;
  }    
  if(digitalRead(BOTAODIR) == 1) b2 = 0;
   if(menu>2)
   menu = 2;
   if(menu<-2)
   menu = -2;
  return menu;
}
