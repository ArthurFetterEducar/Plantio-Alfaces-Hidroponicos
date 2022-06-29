#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 2          //Pino conectado no DHT
#define DHTTYPE DHT22     //Modelo DHT

//Configura DHT
DHT dht(DHTPIN, DHTTYPE); 
dht.begin(); 

float TemperaturaDHT22()
{
  pinMode(DHTPIN, OUTPUT);

  float temperatura = dht.readTemperature();  // Lê a temperatura no DHT22

  if (isnan(temperatura))                     // Verifica se o DHT esta lendo algum numero
  {
    return TEMP_IDEAL;                        // Em caso de medidas não-numéricas, 
  }                                           // retorno mantém a refrigeração desligada

  return temperatura;                         // Retorna o valor de temperatura para verificação do Peltier
}
