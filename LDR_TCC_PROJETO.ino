
// AJUSTES DE VALORES
#define OBSTRUCAO 100 //VALOR PARA CHECAGEM DE OBSTRUÇAO
#define TEMPO_LDR 1 //TEMPO PARA CHAMAR A FUNÇAO(IRA PRA O MAIN FUTURAMENTE)
#define VALOR_MINIMO 800 //VALOR MINIMO DE CLARIDADE
// PINOS DE LED
#define LED_LDR  6 //PINO
#define LEDSTRIP 7 //PINO

// PINOS LDR
#define LDR1 A4 
#define LDR2 A5
//VARIAVEIS DE LEITURA DOS LDR'S
int  leitura_ldr1,leitura_ldr2;
int  tempo=1;


void setup() {
pinMode(INPUT,LDR1);
pinMode(INPUT,LDR2);

pinMode(OUTPUT,LEDSTRIP);
pinMode(OUTPUT,LED_LDR);
}

void loop() {
 
 if(tempo=TEMPO_LDR){
 leitura_ldr1=analogRead(LDR1);
 leitura_ldr2=analogRead(LDR2);
 //------------------LEITURA DE OBSTRÇÃO------------------------------
 if((leitura_ldr1>leitura_ldr2+OBSTRUCAO)||(leitura_ldr2>leitura_ldr1+OBSTRUCAO))
 {
  digitalWrite(HIGH,LED_LDR)
  //Manda Notificaçao para Usuario 
  //Manda Por LCD
 }
 
 if((ldr1+ldr2/2)<VALOR_MINIMO)
  {
     digitalWrite(HIGH,LED_LDR)
    
  }
  else 
   digitalWrite(LOW,LED_LDR)

 }
 
}
