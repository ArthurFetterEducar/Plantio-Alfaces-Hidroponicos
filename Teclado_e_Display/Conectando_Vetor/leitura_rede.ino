#include <ESP8266WiFi.h>
int i,j,rede,leitura;

void setup() {
  Serial.begin(115200);

}

void loop() {
  rede = WiFi.scanNetworks();
  if(leitura == 0){
  for(i = 0; i < rede; i++)
  {
     if(WiFi.RSSI(i) > -85)
     {
      
      Serial.println (WiFi.SSID(i));  
      Serial.println (WiFi.RSSI(i));
     }
  }
 }
  


}
