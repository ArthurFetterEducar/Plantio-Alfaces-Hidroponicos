#define PIN_TRIG  2
#define PIN_ECHO  15

#define VELOCIDADE_SOM 0.035  // Velocidade do som em segundos

float intervalo;    // Intervalo de tempo entre o envio do sinal por PIN_TRIG e a recepção por PIN_ECHO
float distancia;    // Distancia calculada a partir do intervalo de tempo 


void setup() {
  Serial.begin(115200); 

  pinMode(PIN_TRIG, OUTPUT); // Pino PIN_TRIG deve enviar um pulso ao pino Trig do sensor 
  pinMode(PIN_ECHO, INPUT); // Pino Echo do sensor envia um pulso ao pino PIN_ECHO
}

void loop() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  
  // Espera o PIN_ECHO ir a nível alto e calcula a diferença em microssegundos
  intervalo = pulseIn(PIN_ECHO, HIGH);
  
  // Calcula a distância baseado na duração do intervalo
  distancia = intervalo * 0.017;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distancia: ");
  Serial.println(distancia);

  Serial.print("Intervalo: ");
  Serial.println(intervalo);  

  delay(1000);
}