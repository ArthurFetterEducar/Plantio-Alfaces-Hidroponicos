#include "TCC.h"
#include "OledMenu.h"
#include "DefineTCC.h"




int MinBomba, StatusBomba = 1;
int MinDHT, Temp = 0, Humi;
int MinServo;
int MinSonar,distancia = 0,StatusSonar = 0 ;
int StatusPeltier = 0;
float lmQuente = 0, lmFrio = 0;
int menu = 0;

int hora, minuto;

void setup() {
  //attachInterrupt(digitalPinToInterrupt(PINO_BOIA1), Desliga_Bomba, RISING);
  //attachInterrupt(digitalPinToInterrupt(PINO_BOIA2), Desliga_Bomba, RISING);
  SetupTCC();
  MinServo = Minuto();
  MinBomba = Minuto();
  MinDHT = Minuto();
  MinSonar = Minuto();
  distancia = Checagem_Nutrientes();
  Temperatura();
  Setup_Oled(1, 1, 1);
  PrintOled();
}

void loop() {

  
  //============================ Config Oled ==============
  ClearOled();
  menu =  Botao(menu);

  if (menu == 0)
    Menu1(0, StatusSonar, 0, 0);
  else if (menu == 1)
    Menu2(1, StatusBomba);
  else if (menu == 2)
    Menu3(Temp, lmQuente, lmFrio);
  else if (menu == -1)
    MenuHora(hora, minuto);
  PrintOled();
  //============================  Fim Config Oled ===========
  hora = Hora();
  minuto = Minuto();
  lmFrio = LeituraLmF();
  lmQuente = LeituraLmQ();

  //============================== Rotina Bomba =============
  if ((MinBomba + MinutoBombaD) == minuto && StatusBomba == 1)
  {
    digitalWrite( 2 , HIGH );
    MinBomba = minuto;
    StatusBomba = 0;
    Serial.println("Liga");
  }

  if ((MinBomba + MinutoBombaL) == minuto && StatusBomba == 0)
  {
    digitalWrite( 2 , LOW );
    MinBomba = minuto;
    StatusBomba = 1;
    Serial.println("Deliga");

  }
  //============================== Fim Rotina Bomba =============

  //=============================  Rotina DHT ===================
  if ((MinDHT + MinutoDHTR) == minuto)
  {
    Temp = Temperatura();
    Humi = Umidade();
    MinDHT = minuto;

    Serial.print("DHT LE");
  }
  //=============================  Fim Rotina DHT ===============

  //=============================  Rotina Peltier ================
  //Verifica se a temperatura esta a cima do normal
  //Liga peltier e le LM35 do Peltier
  if (Temp > 28 && StatusPeltier == 0 && Temp > 0)
  {
    LigaPeliterF(Temp);
    StatusPeltier = 1;
  }

  if (Temp < 23 && StatusPeltier == 0 && Temp > 0)
  {
    LigaPeliterQ(Temp);

    StatusPeltier = 1;
  }

  if (Temp == 24 && StatusPeltier == 1 || Temp <= 0)
  {
    DesligaPeliterQ();
    DesligaPeliterF();
    StatusPeltier = 0;
  }
  //============================= Fim Rotina Peltier =============

  //=============================== Rotina Servo =================
  if ((MinServo + MinutoServo) == minuto)
  {
    Reabastecimento_Nutriente();
    MinServo  = minuto;
  }
  //============================= Fim da Rotina Servo ============

  //================================ Rotina Sonar  ===============
  if((MinSonar + MinutoSonar) == minuto)
  {
    distancia = Checagem_Nutrientes();
    if (distancia <= 12 ) 
    StatusSonar = 1;
    else StatusSonar = 0;
    Serial.print("Distancia:");
    Serial.println(distancia);
    
  }
  //============================== Fim da Rotina Sonar  ==========
  

}
