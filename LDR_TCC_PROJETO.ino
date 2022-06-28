
// AJUSTES DE VALORES
#define OBSTRUCAO         //VALOR PARA CHECAGEM DE OBSTRUÇAO
#define VALOR_MINIMO      //VALOR MINIMO DE CLARIDADE

// PINOS DE LED
#define LED_LDR  6            
#define LEDSTRIP 

// PINOS LDR
#define LDR1 
#define LDR2 

//VARIAVEIS DE LEITURA DOS LDR'S
int  leitura_ldr1,leitura_ldr2;

void setup() 
{
pinMode(LDR1, INPUT );
pinMode(LDR1, INPUT);

pinMode(LEDSTRIP, OUTPUT);
}

void loop() 
{
 
 leitura_ldr1=analogRead(LDR1);
 leitura_ldr2=analogRead(LDR2);
 //------------------LEITURA DE OBSTRÇÃO------------------------------
 
 if((ldr1+ldr2/2)<VALOR_MINIMO)
 {
     digitalWrite(LEDSTRIP,HIGH);
 }
  else 
   digitalWrite(LEDSTRIP,HIGH);
 
 if((leitura_ldr1>leitura_ldr2+OBSTRUCAO)||(leitura_ldr2>leitura_ldr1+OBSTRUCAO))
 {
  return 1; //Retorna Valor de obstrução para as funçeos de notificações 
 }
}
