#include <WiFi.h>
int i, j=0, rede, leitura;

String x[5];

void setup() {

  Serial.begin(9600);

}

void loop() {
  
  rede = WiFi.scanNetworks();
  
  if (leitura == 0) {
    
    for (i = 0; i < rede; i++)
    {
      
      if (WiFi.RSSI(i) > -85)
      {
        WiFi.SSID(i) = x[j];
        j++;
        Serial.println (WiFi.SSID(i));
      }
    
    }
  }
 
 for (i = 0; i < rede; i++)
 {
  Serial.println(x[i]);
 }


}

