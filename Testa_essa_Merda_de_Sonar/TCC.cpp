//Biblioteca Main do TCC voltada aos atuadores e sensores
#include "DefineTCC.h"
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Arduino.h"
//#include <Servo.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <ESP32_Servo.h>

//================================

//Senha Do Wifi!
const char *ssid     = "123";
const char *password = "123123123";

//PWM Peltier Quente
int freq = 20000;
int ledChannel = 0;
int resolution = 8;

//PWM Peltier Frio
int ledChanne2 = 1;
//LM35
float LMQ = 0;
float LMF = 0;

//Temperatura do DHT
float temp, Umi;

// Pociçao do Servo
int pos;

//Sonar 
float Distancia,intervalo;

//Variaveis para o retorno da funçao Hora( )&& Minuto( )
int h, m;
//================================

//Config De Conexao do Servdor para o GetHora e GetMinuto
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -10800); //Define o Fuso - Horario

//Config do Pino e Modelo do DHT
DHT dht(PINO_DHT22, DHTTYPE);

//Criando objeto para o servo motor
Servo myservo;

//Define Todos os Pinos em nivle logico Baixo no começo do Codigo
void LowPin();

//================================

//Chama todas as fucçoes nescessarias para o funcionamento dos componentes!
void SetupTCC() {
  LowPin();
  dht.begin();
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin();
  timeClient.update();
  timeClient.forceUpdate();
  //================================
  pinMode(PINO_PELTIER_F, OUTPUT);
  pinMode(PINO_PELTIER_Q, OUTPUT);
  //================================
  pinMode(PINO_DHT22, OUTPUT);
  //================================
  pinMode(PINO_LM35_Q , INPUT);
  pinMode(PINO_LM35_F , INPUT);
  //================================
  pinMode(COOLER_F, OUTPUT);
  pinMode(COOLER_Q, OUTPUT);
  //================================
  pinMode(PINO_BOMBA, OUTPUT);
  //================================
  pinMode(PINO_SERVO, OUTPUT);
  myservo.attach(PINO_SERVO);
  //================================
  pinMode(PINO_BOIA1, INPUT);
  pinMode(PINO_BOIA2, INPUT);
  //================================
  pinMode(PINO_TRIG, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
  //================================

  //PWM QUENTE
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(PINO_PELTIER_Q, ledChannel);
  //================================
  //PWM FRIO
  ledcSetup(ledChanne2, freq, resolution);
  ledcAttachPin(PINO_PELTIER_F, ledChanne2);
}

//Define Todos os Pinos em nivel logico Baixo no começo do Codigo
void LowPin() {
  digitalWrite(39, HIGH);
  digitalWrite(36, LOW);
  digitalWrite(34, LOW);
  digitalWrite(35, LOW);
  digitalWrite(32, LOW);
  digitalWrite(33, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  digitalWrite(14, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(23, LOW);
  digitalWrite(22, LOW);
  digitalWrite(1, LOW);
  digitalWrite(3, LOW);
  digitalWrite(21, LOW);
  digitalWrite(19, LOW);
  digitalWrite(18, LOW);
  digitalWrite(5, LOW);
  digitalWrite(17, LOW);
  digitalWrite(16, LOW);
  digitalWrite(4, LOW);
  digitalWrite(2, LOW);
  digitalWrite(15, LOW);

}
//Atribui a Hora de Um WebServer
int Hora() {
  h = (timeClient.getHours());
  return h;
}
//Atribui os minutos de Um WbeServer
int Minuto() {
  m = (timeClient.getMinutes());
  return m;
}

//Le a temperatura do DHT22
float Temperatura() {
  temp = dht.readTemperature();
  return temp;
}
//Le a Humidade do DHT22
float Umidade() {
  Umi = dht.readHumidity();
  return Umi;
}


//Le a tensao do LM35 sobre o peltier Frio
float LeituraLmF() {
  int adcVal = analogRead(PINO_LM35_F);
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  // convert the voltage to the temperature in °C
  return milliVolt / 5;
}


//Le a tensao do LM35 sobre o peltier Quente
float LeituraLmQ() {
  int adcVal = analogRead(PINO_LM35_Q);
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  // convert the voltage to the temperature in °C
  return milliVolt / 5;
}

//Liga o Peltier Quente e o Cooler
void LigaPeliterQ(float temp) {
  /* Potencia
    Nivel Adequado:24C
    Frio -> No Talo: 14C
    Medio:16
    Baixo:20 até o 24

    Quente-> No Talo: 34
    Medio:30
    Baixo:26 até o 24

    OBS:histerese entre 20 e 28 Gruaus para ligar \0/
  */

  if (temp <= 16) {
    ledcWrite(ledChannel , PWM_ALTO);
    Serial.println("PWM ALTO");
  }
  if (temp > 16 && temp <= 20) {

    ledcWrite(ledChannel , PWM_MEDIO);
    Serial.println("PWM_MEDIO");
  }
  if (temp > 20 && temp <= 24) {
    ledcWrite(ledChannel , PWM_BAIXO);
    Serial.println
    ("PWM BAIXO");
  }
  digitalWrite(COOLER_Q, HIGH);
}

//Desliga o Peltier Quente e o Cooler
void DesligaPeliterQ() {
  ledcWrite(ledChannel , PWM_DESLIGADO);
  digitalWrite(COOLER_Q, LOW);
}



//Liga o Peltier Frio e o Cooler
void LigaPeliterF(float temp) {
  /* Potencia
    Nivel Adequado:24C
    Frio -> No Talo: 14C
    Medio:16
    Baixo:20 até o 24

    Quente-> No Talo: 34
    Medio:30
    Baixo:26 até o 24

    OBS:histerese entre 20 e 28 Gruaus para ligar \0/
  */
  if (temp >= 28) {
    if (temp >= 34)
      ledcWrite(ledChanne2 , PWM_ALTO);
    if (temp > 30 && temp <= 34)
      ledcWrite(ledChanne2 , PWM_MEDIO);
    if (temp > 26 && temp <= 30)
      ledcWrite(ledChanne2 , PWM_BAIXO);
  }
  digitalWrite(COOLER_F, HIGH);
}

//Desliga o Peltier Frio e o Cooler
void DesligaPeliterF() {
  ledcWrite(ledChannel , PWM_DESLIGADO);
  digitalWrite(COOLER_F, LOW);
}

// Rotina do Servo Motor para reabastecimento de nutrientes da estufa
void Reabastecimento_Nutriente() {
  myservo.write(180);
  delay(2000);
  myservo.write(150);
}

void Desliga_Bomba() {
  digitalWrite(2, LOW);
}

int Checagem_Nutrientes (){
  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);
  
  digitalWrite(PINO_TRIG, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(PINO_TRIG, LOW);

  intervalo = pulseIn(PINO_ECHO, HIGH);

  Distancia = (intervalo * 0.034) / 2;

  return Distancia;
}
