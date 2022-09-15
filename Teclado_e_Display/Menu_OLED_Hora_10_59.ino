#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // Largura do display em pixels
#define SCREEN_HEIGHT 64    // Altura do display em pixels
#define SCREEN_ADRESS 0X3C

#define PINO_BOIA 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



int i,f_setup = 0,wiificheck = 0;
float temperatura = 21,hora=10,minuto=43;
int dir = 1,enter = 0,menu = 0;
char leitura;


void setup() {
 Serial.begin(9600);
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 display.setTextSize(1);      // Tamanho de Fonte
 display.setTextColor(WHITE);
 display.clearDisplay();
 f_setup = Verifica_Sensor(temperatura); //Ira printar a verificaçao do sensor de boia e DHT
 display.display();
 delay(2000);
  
}

//=============================== LOOP ==========================================

void loop() {
 display.clearDisplay(); //Limpa tela
  display.setTextSize(1);
 if(f_setup == 1) //Apos Verificar sensores ira pedir para se conectar o wifi
 {
  wiificheck = wifi(enter); //Checa se o wifi foi conectado 
  dir = Cursor(dir); //printa o cursor na tela
 }

 if(wiificheck == 1)
 {
   f_setup = 0;
   
   if(menu >= 2)
   menu = 2;

   
   if(menu <= -2)
   menu = -2;
   if(menu == 0)
   Menu1();
   else if(menu == 1)
   Menu2();
   else if (menu == 2)
   Menu3(temperatura);
   else if( menu == -1)
   MenuHora(hora,minuto);
   else if(menu == -2)
   {
      wifi(enter);
      dir = Cursor(dir);
      display.setCursor(120,30);
      display.print(">");   
   }

   
 
 
 
 }//if para interaçoes de menu


leitura = Serial.read();   //Leitura de Botoes Botar Switch no codigo principal
if(leitura == 'w')
dir++;
if(leitura == 's')
dir--;
if(leitura == 'a')
menu--;
if(leitura == 'd')
menu++;
if(leitura == 'e')
enter = 1;

  display.display(); 
}//loop



//================Essa funça ira verificar os dois sensores e avisar pro usuario vai ser executado so uma vez entao ira no setup da main =============
int Verifica_Sensor(int temperatura){
  display.setCursor(15,5);
  display.print("Sensor de ");
  display.setCursor(15,15);
  display.print("temperatura");
  
  display.setCursor(15,25);
  if (isnan(temperatura))                     
  {
      
    display.print("Medida Invalida!");
  }          
  else{ 
   display.print("Medida Valida!");
    
  }
  
  display.setCursor(15,40);
  display.print("Sensores de Boia");
 
  //if(digitalRead(PINO_BOIA) == 1)
  int boia = 0;
  display.setCursor(15,50);
  if(boia == 1)
  {
   display.print("excesso de Agua");
  }
  else
  display.print("OK..");
  
  return 1;
 }//fim da funçao


//================= Wifi ================
int wifi(int enter){
  display.setCursor(50,10);
  display.print("Wifi");

  if (enter == 1)
  return 1;
  else 
  return 0;
}


//=================== Cursor ================
int Cursor(int dir){
 if(dir <= 0 ) //Limite de tela para o cursor
 dir = 1;
 if(dir >= 9 ) //Limite de tela para o cursor
 dir = 9;
 display.setCursor(0,10+(5*dir));
 display.print(">");
 return dir;
}

//================= Menu 1 ==================
void Menu1(){
  
  int boia1,boia2;
  int TrocaAgua = 1; 
  int TrocaAbs = 1;
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
  if(boia1 == 2)
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
//========================= Menu 2 =============
void Menu2(){
  display.setCursor(15,0);
  display.print("Funcionamento");
  display.setCursor(15,10);
  display.print("Da estufa!");
  
  display.setCursor(15,20);
  display.print("Aquecimento");
  int aquecimento = 1; 
  int bomba = 1;
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
//=============== Menu 3 =============
void Menu3(int temperatura){  
  display.setCursor(15,0);
  display.print("Temperatura da");

  display.setCursor(15,10);
  display.print("Estufa:");
  
  display.setCursor(60,10);
  display.print(temperatura);

  int lm1= 50,lm2= 12;
  
  display.setCursor(15,25);
  display.print("Aquec: ");
  display.setCursor(50,25);
  display.print(lm1);
  
  display.setCursor(15,40);
  display.print("Resf: ");
  display.setCursor(45,40);
  display.print(lm2);

   display.setCursor(0,30);
  display.print("<");
  
  
  
}

//============ Menu Hora ==============
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
  display.print("<");
  
  display.setCursor(120,30);
  display.print(">");
  
}
