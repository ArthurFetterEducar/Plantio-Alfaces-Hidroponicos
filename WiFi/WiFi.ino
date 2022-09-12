#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h" 

#define API_KEY "AIzaSyB6eCwhUTpBL2gGqRIrbDbDtWnVBdzrUHI"
#define DB_URL  "https://esp32-teste-eee0e-default-rtdb.firebaseio.com/"


FirebaseData fbdo; 

// Estrutura para a identificação de uma rede WiFi
struct WiFiNetwork{
  char* ssid;       // Nome da rede
  bool encryption;  // Necessidade de senha da rede
  char* password;   // Senha da rede
};

// Configuração manual de uma rede
struct WiFiNetwork MinhaRede = { 
  "wifi_nome", // SSID
  false,                   // Necessidade de senha
  "wifi_senha",          // Senha
}; 

void WiFi_Connect(struct WiFiNetwork *network);
// void WiFi_Search();

bool signup_satus = false;

bool API_Setup(char *api_key, char *db_URL) {
  FirebaseConfig config;
  FirebaseAuth auth;
  
  config.api_key = api_key;
  config.database_url = db_URL; 

  bool signup;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok"); // Debugging
    signup = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
    signup = false;
  }

  config.token_status_callback = tokenStatusCallback; 
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true); 

  return signup;
}

void setup() {
  Serial.begin(9600);
  
  // Configuração WiFi
  WiFi_Connect(&MinhaRede);
}

void loop() {
  if(Firebase.ready() && signup_satus) {
    if (Firebase.RTDB.setInt(&fbdo, "test1/int", "")) { // Envia um int
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());        
    }  

    if (Firebase.RTDB.setFloat(&fbdo, "test1/float", 0.01 + random(0, 100))) { // Envia um float
      Serial.println("PASSED");
      Serial.println("PATH" + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());        
    }
  }
}





// void WiFi_Search()
// {
//   int i;  // Indice genérico
  
//   //ESP32 faz a busca por redes
//   WiFi.disconnect(); 
//   delay(100);  

//   Serial.println("Procurando por redes: ");

//   Serial.println("Escaneando por redes.");
//   int n = WiFi.scanNetworks(); 

//   Serial.println("Escaneamento completo.");

//   if (n == 0) {
//     Serial.println("Nenhuma rede encontrada");
//   }
//   else {
//     Serial.print(n);
//     Serial.println(" redes encontradas.");

//     for (i = 0; i < n; i++) {
//       Serial.print(i+1);
//       Serial.println(": ");
      
//       Serial.print(WiFi.SSID(i));

//       Serial.print(" (");
//       Serial.print(WiFi.RSSI(i));
//       Serial.print(")");
//       Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");

//       delay(10);      
//     }
//   }

//   Serial.println("");

//   delay(5000);  
// }


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
  Serial.print("Conectado a rede com endereço IP de: ");
  Serial.println(WiFi.localIP());
  /* Debugging */
}
