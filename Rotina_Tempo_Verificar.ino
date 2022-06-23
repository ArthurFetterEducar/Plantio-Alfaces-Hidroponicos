#define SENS_BOIA_B                           //Boia De Baixo
#define SENS_BOIA_C                           //Boia De Cima
#define LED_BOIA

int Tempo_Real;
const int 
Tempo_bomba=0,
Tempo_lum=0,
Tempo_temp=0,
Tempo_nutri=0,
Tempo_boiaB=0,
Tempo_boiaC=0;



void setup() {
  

}

void loop() {
  if(Tempo_Real==Tempo_bomba)                 //Checa tempo para a ativação da Bomba a vácuo 
    AtivaBomba();
  
  if(Tempo_Real==Tempo_Lum)                   //Checa tempo para a verificação dos LDR's
    LDR();
  
  if(Tempo_Real==Tempo_temp)                  //Checa tempo para a verificação do DHT22
    DHT22();
  
  if(Tempo_Real==Tempo_nutri)                 //Checa o Tempo para a ativação do Servo Motor 
    Nutriente(); 
  
        //==================Bomba C ==========================
  if(Tempo_Real==Tempo_boiaC)                 //Checa Tempo para a verificação da boia
    {
    
    int leitura_boiaC;                        //Variaveis de Leitura da Boia
                                              
    leitura_boiaC=analogRead(SENS_BOIA_C);    //Leitura do pino
                                 
        if(leitura_boiaC==0)                  //Checa excesso
        {
            digitalWrite(HIGH,LED_BOIA);
            NotificaUsuario();
            NotificaLCD();
        }
    }
       //==================Bomba B ==========================
       
       if(Tempo_Real==Tempo_boiaB)
    {
                 
    int leitura_boiaB;                          //Variaveis de Leitura da Boia

    leitura_boiaC=analogRead(SENS_BOIA_B);      //Leitura do pino

        if(leitura_boiaB==0)                    //Checa Esvaziamento
        {
            digitalWrite(HIGH,LED_BOIA);
            NotificaUsuario();
            NotificaLCD();
        }
    }


}
