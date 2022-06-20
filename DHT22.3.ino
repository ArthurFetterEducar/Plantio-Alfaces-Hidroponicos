#define DHTPIN 2          //Pino conectado no DHT
#define DHTTYPE DHT22     //Modelo DHT
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

//Configura DHT
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600);
  dht.begin(); 
  
  pinMode(DHTPIN,OUTPUT);

  Serial.println(F("DHTxx test!"));   //Printa um Teste DHT
}

void loop() {
  delay(2000);                        //Delay para Leitura
  
  float temp = dht.readTemperature(); //Lê a temperatura no DHT22

  if (isnan(temp))                   //Verifica se o DHT esta lendo
  {
    Serial.println(F("Falha a ler DHT"));
    return;
  }
  
  //Printa no Serial a temperatura
  Serial.print(temp);
  Serial.print(F("%  Temperature"));
  Serial.print("\n"); 
}
