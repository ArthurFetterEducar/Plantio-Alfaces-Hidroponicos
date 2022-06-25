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
  
  float temperatura = dht.readTemperature(); //Lê a temperatura no DHT22

  if (isnan (temperatura))                   //Verifica se o DHT esta lendo algum numero
  {
    
    Serial.println(F("Falha a ler DHT"));
    return;

  }
  
  Serial.print(temperatura);                 //Printa no Serial a temperatura
  Serial.print(F("%  Temperatura"));
  Serial.print("\n"); 
  
  return temperatura;                        //Retorna o valor de temperatura para verificação do Peltier
}
