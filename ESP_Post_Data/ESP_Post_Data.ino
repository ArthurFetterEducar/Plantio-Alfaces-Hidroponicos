#include <Arduino.h>
#include <WiFi.h> 
#include <HTTPClient.h>
#include <stdio.h>
#include <string.h>

void WiFi_Connect(struct WiFiNetwork *network);

void ESP_HTTP_JSON_POST(class WiFiClient *esp_wifi_client, class HTTPClient *esp_http_client, String server_name, 
                        float temperature, float humidity, int water_level, float peltier_hot_temp, 
                        bool peltier_hot_state, float peltier_cold_temp, bool peltier_cold_state, bool pump_state);


// Estrutura para a identificação de uma rede WiFi
struct WiFiNetwork{
  char* ssid;       // Nome da rede
  bool encryption;  // Necessidade de senha da rede
  char* password;   // Senha da rede
};

// Configuração manual de uma rede
struct WiFiNetwork MinhaRede = { 
  "rede_sebratel_149797",   // SSID
  false,                    // Necessidade de senha
  "74440713068",            // Senha
};

String serverName = "https://hydro-farm-app.vercel.app/api/ESP-DataHandler";

unsigned long lastTime = 0;
unsigned long timerDelay = 10000; 

float temperature = 15;
float humidity = 91;
float peltier_hot_temp = 28;
float peltier_cold_temp = 18;

int water_level = 0;

bool peltier_hot_state = 0;
bool peltier_cold_state = 1;
bool pump_state = 1;

char http_post[300];

void setup() {
  Serial.begin(9600);
  
  // Configuração WiFi
  WiFi_Connect(&MinhaRede);
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status() == WL_CONNECTED) {
      WiFiClient client; 
      HTTPClient http;  // Devem ser criados apenas apos conexão wifi ser estabelecida
  
      ESP_HTTP_JSON_POST(&client, &http, serverName, temperature, humidity, water_level, peltier_hot_temp, peltier_hot_state, peltier_cold_temp, peltier_cold_state, pump_state);
    } 
    else {
      Serial.println("Error in WiFi connection");   
    }    
    
    lastTime = millis();    
  }   
}


void ESP_HTTP_JSON_POST(class WiFiClient *esp_wifi_client, class HTTPClient *esp_http_client, String server_name, 
                        float temperature, float humidity, int water_level, float peltier_hot_temp, 
                        bool peltier_hot_state, float peltier_cold_temp, bool peltier_cold_state, bool pump_state) {
  esp_http_client->begin(server_name);
  esp_http_client->addHeader("Content-Type", "application/json");

  char http_post_data[300];

  snprintf(http_post_data, sizeof(http_post_data), "{ \"Temperature\": %.2f, \"Humidity\": %.2f,  \"Water_Level\": %d, \"Peltier_Hot_Temperature\": %.2f, \"Peltier_Hot_State\": %d, \"Peltier_Cold_Temperature\": %.2f, \"Peltier_Cold_State\": %d, \"Pump_State\": %d }", temperature, humidity, water_level, peltier_hot_temp, peltier_hot_state, peltier_cold_temp, peltier_cold_state, pump_state);
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

void WiFi_Connect(struct WiFiNetwork *network)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  WiFi.begin(network->ssid, network->password);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.'); //Debugging
    delay(100);
  }

  /* Debugging */
  Serial.println(""); 
  Serial.print("Conectado a rede com endereco IP de: ");
  Serial.println(WiFi.localIP());
  /* Debugging */
}
