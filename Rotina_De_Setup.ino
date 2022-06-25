// PINOS LDR
#define LDR1  
#define LDR2 
#define LED_LDR   
#define OBSTRUCAO 

//PINOS BOIAS
#define SENS_BOIA_B         //Boia De Baixo
#define SENS_BOIA_C         //Boia De Cima
#define LED_BOIA

void setup() {
  
  //Pinos Boia 
  pinMode(INPUT,SENS_BOIA_B); 
  pinMode(INPUT,SENS_BOIA_C);
  pinMode(OUTPUT,LED_BOIA);

  //Pinos LDR
  pinMode(INPUT,LDR1);
  pinMode(INPUT,LDR2);
  pinMode(OUTPUT,LED_LDR);

 //Exec Funçoes 
  
 //Variaveis de Leitura LDR
 int  leitura_ldr1,leitura_ldr2;
 
 //Checagem Obstruçao LDR 
 leitura_ldr1 = analogRead(LDR1);
 leitura_ldr2 = analogRead(LDR2);
 
 //------------------LEITURA DE OBSTRÇÃO------------------------------
 if((leitura_ldr1 > leitura_ldr2 + OBSTRUCAO) || (leitura_ldr2 > leitura_ldr1 + OBSTRUCAO)){
  digitalWrite(HIGH,LED_LDR);
  NotificaUsuario(); 
  NotificaLCD();
 }
 
 //----------------Leitura Sensores Boia -----------------------------
 
 //Variaveis de Leitura Boias
 int leitura_boiaC, leitura_boiaB;
 
 //Leitura dos pinos 
 leitura_boiaC = analogRead(SENS_BOIA_C);
 leitura_boiaB = analogRead(SENS_BOIA_B);
 
 //Checa esvaziamento
 if(leitura_boiaB == 0){
    digitalWrite(HIGH, LED_BOIA);
    NotificaUsuario(); 
    NotificaLCD();
  }
  
  //Checa excesso
  if(leitura_boiaC==1){
    digitalWrite(HIGH,LED_BOIA);
    NotificaUsuario(); 
    NotificaLCD(); 
  }

}

void loop() {
 

  
}
