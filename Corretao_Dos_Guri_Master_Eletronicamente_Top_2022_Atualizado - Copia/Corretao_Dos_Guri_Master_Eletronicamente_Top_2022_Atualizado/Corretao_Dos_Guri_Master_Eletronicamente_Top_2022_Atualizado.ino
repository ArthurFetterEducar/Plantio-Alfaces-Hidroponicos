#include "TCC.h"
#include "OledMenu.h"
#include "DefineTCC.h"

#include <Arduino.h>
#include <WiFi.h> 
#include <HTTPClient.h>
#include <stdio.h>
#include <string.h>

void ESP_HTTP_JSON_POST(class WiFiClient *esp_wifi_client, class HTTPClient *esp_http_client, String server_name, 
                        float temperature, float humidity, int water_level, float peltier_hot_temp, 
                        bool peltier_hot_state, float peltier_cold_temp, bool peltier_cold_state, bool pump_state); 

int MinBomba, StatusBomba = 1, StatusBoia = 0;
int MinDHT;
float Temp = 0, Humi = 0;
int MinServo;
int MinSonar,distancia = 0,StatusSonar = 0 ;
int MinSite;
int StatusPeltierF = 0, StatusPeltierQ = 0;
float lmQuente = 0, lmFrio = 0;
int menu = 0;

int hora, minuto;

String serverName = "https://hydro-farm-app.vercel.app/api/ESP-DataHandler";

void setup() {
 // attachInterrupt(digitalPinToInterrupt(PINO_BOIA1), Desliga_Bomba, FALLING );
 // attachInterrupt(digitalPinToInterrupt(PINO_BOIA2), Desliga_Bomba, FALLING );
  SetupTCC();
  MinServo = Minuto();
  MinBomba = Minuto();
  MinDHT = Minuto();
  MinSonar = Minuto();
  MinSite = Minuto();
  distancia = Checagem_Nutrientes();
  Temperatura();
  Setup_Oled(1, 1, 1);
  PrintOled();
}

void loop() {

  Serial.println(digitalRead(PINO_BOIA1));
  //============================ Config Oled ==============
  ClearOled();
  menu =  Botao(menu);
  if (menu == 0)
    Menu1(0, 0, 0,StatusSonar );
  else if (menu == 1)
    Menu2(1, StatusBomba);
  else if (menu == 2)
    Menu3(Temp, lmQuente, lmFrio);
  else if (menu == -1)
    MenuHora(hora, minuto);
  else if(menu == -2)
    MenuSonar(distancia);
  PrintOled();
  //============================  Fim Config Oled ===========
  hora = Hora();
  minuto = Minuto();
  lmFrio = LeituraLmF();
  lmQuente = LeituraLmQ();

  //============================== Rotina Bomba =============
  if ((MinBomba + MinutoBombaD) == minuto && StatusBomba == 1)
  {
    digitalWrite( PINO_BOMBA , LOW );
    MinBomba = minuto;
    StatusBomba = 0;
    Serial.println("BOMBA -> Ligada");
  }
  

  if ((MinBomba + MinutoBombaL) == minuto && StatusBomba == 0)
  {
    digitalWrite( PINO_BOMBA , HIGH );
    MinBomba = minuto;
    StatusBomba = 1;
    Serial.println("BOMBA -> Deligada");

  }
  //============================== Fim Rotina Bomba =============
   if(digitalRead(PINO_BOIA2) == 0)
  {
    digitalWrite( PINO_BOMBA , HIGH );
    Serial.println("BOMBA -> Deligada");
     StatusBomba = 0;
    StatusBoia = 1;
  }
   if(digitalRead(PINO_BOIA1) == 1){
    digitalWrite( PINO_BOMBA , HIGH );
    Serial.println("BOMBA -> Deligada");
   StatusBomba = 0;
    StatusBoia = -1;
   }
 
  //=============================  Rotina DHT ===================
  if ((MinDHT + MinutoDHTR) == minuto)
  {
    Temp = Temperatura();
    MinDHT = minuto;
    Serial.print("Temperatura do DHT -> ");
    Serial.println(Temp);
  }
  //=============================  Fim Rotina DHT ===============
 
  //=============================  Rotina Peltier ================
  //Verifica se a temperatura esta a cima do normal
  //Liga peltier e le LM35 do Peltier
    
              //(*-- Teste dos Fan's --*)
  //digitalWrite(COOLER_F, HIGH);
  //digitalWrite(COOLER_Q, HIGH);
  
  if (Temp > 26 && Temp > 0)
  {
    LigaPeliterF(Temp);
    DesligaPeliterQ();

    StatusPeltierQ = 0;
    StatusPeltierF = 1;
  }

  else if (Temp < 24  && Temp > 0)
  {
    LigaPeliterQ(Temp);
    DesligaPeliterF();

    StatusPeltierQ = 1;
    StatusPeltierF = 0;
  }
  
  else
  {
    DesligaPeliterF();
    DesligaPeliterQ();

    StatusPeltierQ = 0;
    StatusPeltierF = 0;
  }
  
  //============================= Fim Rotina Peltier =============

  //=============================== Rotina Servo =================
  if ((MinServo + MinutoServo) == minuto)
  {
    Serial.println("Girando o Servo Motor...");
    Reabastecimento_Nutriente();
    MinServo = minuto;
  }
  //============================= Fim da Rotina Servo ============

  //================================ Rotina Sonar  ===============
  if((MinSonar + MinutoSonar) == minuto)
  {
    distancia = Checagem_Nutrientes();
    if (distancia <= 12 ) 
    StatusSonar = 1;
    else StatusSonar = 0;
    MinSonar = minuto;
    Serial.print("Distancia:");
    Serial.println(distancia);
    
  }
  //============================== Fim da Rotina Sonar  ==========

  //============================== Início Rotina Site ============
  if ((MinSite + MinutoSite) == minuto)
  {
    WiFiClient client; 
    HTTPClient http; 
    
    ESP_HTTP_JSON_POST(&client, &http, serverName, Temp, Humi, StatusBoia, lmQuente, StatusPeltierQ, lmFrio, StatusPeltierF, StatusBomba);
    MinSite = minuto;
    Serial.print("Manda Pro Site.. ");
  }

}

void ESP_HTTP_JSON_POST(class WiFiClient *esp_wifi_client, class HTTPClient *esp_http_client, String server_name, 
                        float temperature, float humidity, int water_level, float peltier_hot_temp, 
                        bool peltier_hot_state, float peltier_cold_temp, bool peltier_cold_state, bool pump_state) {
  esp_http_client->begin(server_name);
  esp_http_client->addHeader("Content-Type", "application/json");

  char http_post_data[300];

  snprintf(http_post_data, sizeof(http_post_data), "{ \"Temperature\": %.2f, \"Humidity\": %.2f,  \"Water_Level\": %d, \"Peltier_Hot_Temperature\": %.2f, \"Peltier_Hot_State\": %d, \"Peltier_Cold_Temperature\": %.2f, \"Peltier_Cold_State\": %d, \"Pump_State\": %d }", temperature, humidity, water_level, peltier_hot_temp, peltier_hot_state, peltier_cold_temp, peltier_cold_state, pump_state);
//  snprintf(http_post_data, sizeof(http_post_data), "{ \"Temperature\": 1, \"Humidity\": 1,  \"Water_Level\": 1, \"Peltier_Hot_Temperature\": 1, \"Peltier_Hot_State\": 1, \"Peltier_Cold_Temperature\": 1, \"Peltier_Cold_State\": 1, \"Pump_State\": 1 }");
  Serial.println(http_post_data);
  int httpResponseCode = esp_http_client->POST(http_post_data); 

  if(httpResponseCode>0) { 
    String response = esp_http_client->getString();

    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
  } 
  else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }

  esp_http_client->end();
}
