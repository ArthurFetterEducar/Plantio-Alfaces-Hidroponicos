/*===========================================================
Codigo para a realizaçao de testes de comportamento da estufa
 ==========================================================*/

#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

//PINO PELTIER 
#define PINO_PELTIER_F 36
#define PINO_PELTIER_Q 35

#define PINO_DHT22 18
#define DHTTYPE 22

#define PINO_PIEZO 15

#define PINO_BOMBA 39

#define PINO_SERVO 19

//PINO OLED
#define PINO_SCL 21
#define PINO_SDA 22

//PINO DO TECLADO
#define PINO_TECLA_CIMA 32
#define PINO_TECLA_DIRT 26
#define PINO_TECLA_ESQ 25
#define PINO_TECLA_BAIXO 33
#define PINO_TECLA_CONFIRMA 14
#define PINO_TECLA_COMUM 27

//Sensor Boia
#define PINO_BOIA1 12
#define PINO_BOIA2 13

//=================================Variaveis====================================
int flag = 0;


//================================DHT22=========================================
DHT dht(PINO_DHT22, DHTTYPE); 
dht.begin();
float temperatura=0; 

//=============================================================================

void setup(){
  pinMode(PINO_PELTIER_F, OUTPUT);
  
  pinMode(PINO_PELTIER_Q, OUTPUT);

  pinMode(PINO_DHT22, OUTPUT);

  pinMode(PINO_PIEZO,OUTPUT);

  pinMode(PINO_BOMBA,OUTPUT);

  pinMode(PINO_SERVO,OUTPUT);

  pinMode(LED_TROCA_AGUA,OUTPUT);
  pinMode(LED_ABS_NUTRIENTES,OUTPUT);

  pinMode(PINO_BOIA1, INPUT);
  pinMode(PINO_BOIA2, INPUT);

  Serial.begin(9600);

}

void loop()
{
 //=====================DHT22=================
  flag = Serial.read();
  if(flag == 'W'){
  digitalWrite(PINO_BOMBA,HIGH);
  Serial.print("Bomba Ativa..");  
  }
  if(flag == 'w'){
   digitalWrite(PINO_BOMBA,LOW);   
   Serial.print("Bomba Desativada..");    
  }
                                             
  



}
