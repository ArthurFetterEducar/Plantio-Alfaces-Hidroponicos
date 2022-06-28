#define SENS_BOIA_B                        //Pino Analogico para a boia 

int leitura_boiaB;                         //Variaveis de Leitura da Boia 

pinMode(SENS_BOIA_B,INPUT); 


int boiaBaixo() {
 leitura_boiaB = digitalRead(SENS_BOIA_B);  //Leitura do pino 
 
 return leitura_boiaB;
}
