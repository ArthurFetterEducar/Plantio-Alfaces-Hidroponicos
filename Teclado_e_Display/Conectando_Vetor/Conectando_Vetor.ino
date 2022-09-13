/*
A Bibliote NTPClient pode ser encontrada no Arduino IDE.
Ela sincroniza por meio da internet dados de um servidor(NTP) o mesmo que tem nos sistemas operacionas como windows sendo capaz de armazenar estes dados
em variaveis para usalas como parametros de ativaçoes por tempo.
*/


#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
const char  ssid[4] = { 49,50, 51, '\0'}; 
const char *password = "123123123";



char daysOfTheWeek[7][12] = {"Dommingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sabado"};


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -10800); //Define o Fuso - Horario

void setup(){
  Serial.begin(115200); 

  WiFi.begin(ssid, password); //Conecta na Rede

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
 
  timeClient.begin();
}

void loop() {
  timeClient.update(); //Atualiza Hora
   timeClient.forceUpdate(); //Força Atualizaçao caso ocorra um bug na hora da atualizaçao!

  Serial.print(daysOfTheWeek[timeClient.getDay()]); 
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  

  delay(1000);
}
