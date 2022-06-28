#define SENS_BOIA_C                           //Pino Analogico para a boia 

int leitura_boiaC;                            //Variaveis de Leitura da Boia


int boiaCima() {
  pinMode(SENS_BOIA_C, INPUT);
  
  leitura_boiaC = digitalRead(SENS_BOIA_B);    //Leitura do pino
                                              
  return leitura_boisaC;
}
