#define PINO_BOMBA
#define TEMPO_LIGADO            //Tempo atual de acionamento da bomba

#define TEMPO_MAX               //Tempo de limitação para o desligamento da bomba
void setup() {
  pinMode(PinoBomba, OUTPUT);
  
}

void loop() {
  if(TEMPO_LIGADO <= TEMPO_MAX)
    digitalWrite(PINO_BOMBA, HIGH);
}
