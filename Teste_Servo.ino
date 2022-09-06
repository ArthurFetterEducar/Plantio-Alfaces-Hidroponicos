


/*===========================================================
Codigo para a realizaçao de testes de comportamento da estufa
https://www.usinainfo.com.br/blog/programar-esp32-com-a-ide-arduino-tutorial-completo/
 ==========================================================*/
#include <Servo.h>

/*
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
*/
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
char flag ;


//================================DHT22=========================================
/*
DHT dht(PINO_DHT22, DHTTYPE); 
dht.begin();
float temperatura=0; 
*/
//================================PWM============================================
int duty_cicle = 0; //Modificaçao do Duty Cicle

int duty_cicle_lvl = map(duty_cicle,0,99,0,255);  //Converçao do PWM para 0% a 99%

const int freq = 20000;
const int ledChannel = 0;
const int resolution = 8;

//=================================Servo Motor ===============================================
Servo s; // Variável Servo
int pos; // Posição Servo


void setup(){
  pinMode(PINO_PELTIER_F, OUTPUT);
  
  pinMode(PINO_PELTIER_Q, OUTPUT);

  pinMode(PINO_DHT22, OUTPUT);

  pinMode(PINO_PIEZO,OUTPUT);

  pinMode(PINO_BOMBA,OUTPUT);

  pinMode(PINO_SERVO,OUTPUT);

  pinMode(PINO_BOIA1, INPUT);
  pinMode(PINO_BOIA2, INPUT);

   
  //ledcSetup(ledChannel, freq, resolution);
  
  //ledcAttachPin(PINO_PIEZO, ledChannel);

  s.attach(PINO_SERVO);
  Serial.begin(9600);
  s.write(145); // Inicia motor posição 145
  
  Serial.begin(9600);

}

void loop()
{
 for(pos = 145; pos >=100 ; pos--)
  {
 
  s.write(pos);
  delay(15);
  }
delay(1000);
  for(pos = 100; pos <= 145; pos++)
  {
    s.write(pos);
    delay(15);
  }
}
