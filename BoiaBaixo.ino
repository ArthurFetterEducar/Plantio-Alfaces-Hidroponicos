#define SENS_BOIA_B                        //Pino Analogico para a boia 
void setup() {
  pinMode(SENS_BOIA_B,INPUT);
}

void loop() {
 int leitura_boiaB;                        //Variaveis de Leitura da Boia

 leitura_boiaB = analogRead(SENS_BOIA_B);  //Leitura do pino
                                          
                                           //Checa Esvaziamento
   
   if(leitura_boiaB==0)                    //Nivel: Vazio               
      return 'V';
   if(leitura_boiaB==1)                    //Nivel: Normal          
      return 'F';
      
}
