#define SENS_BOIA_B                        //Pino Analogico para a boia 

int leitura_boiaB;                         //Variaveis de Leitura da Boia 


int boiaBaixo() {
 pinMode(SENS_BOIA_B,INPUT); 
 
 leitura_boiaB = digitalRead(SENS_BOIA_B);  //Leitura do pino 
 
 return leitura_boiaB;
}
