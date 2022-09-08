#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "NomeDaRede";
const char *password = "Senha";



char daysOfTheWeek[7][12] = {"Dommingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sabado"};


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "br.pool.ntp.org", -10656); //Define o Fuso - Horario

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
   timeClient.forceUpdate(); //Força Atualizaçao 

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  

  delay(1000);
}
