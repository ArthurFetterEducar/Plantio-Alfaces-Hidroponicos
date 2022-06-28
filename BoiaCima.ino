#define SENS_BOIA_C                           //Pino Analogico para a boia 

void setup() {
  
pinMode(SENS_BOIA_B, INPUT);

}
  void loop() {

  int leitura_boiaC;                          //Variaveis de Leitura da Boia

  leitura_boiaC = analogRead(SENS_BOIA_B);    //Leitura do pino
                                              //Checa Esvaziamento 
  if(leitura_boiaC==0)                        //Nivel: Elevado               
     return 'V';
  if(leitura_boiaC==1)                        //Nivel: Normal          
     return 'F';   
}
