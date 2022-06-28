#define PINO_BOMBA              //Tempo atual de acionamento da bomba       

#define TEMPO_MAX               //Tempo de limitação para o desligamento da bomba
pinMode(PinoBomba, OUTPUT);

void bombaDagua(tempo_atual) {
  pinMode(PinoBomba, OUTPUT);
  
  if(estado_bomba == 1)
  {
    if(tempo_bomba >= TEMPO_MAX)
      digitalWrite(PINO_BOMBA, LOW);
  }
  else
    
  // A terminar
}
