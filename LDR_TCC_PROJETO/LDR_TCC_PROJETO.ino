// AJUSTES DE VALORES
#define OBSTRUCAO         // Valor para chacagem de obstrução
#define VALOR_MINIMO      // Valor mínimo de claridade

// PINOS DE LED
#define LED_LDR      // ??? (Arthur)      
#define LEDSTRIP 

// PINOS LDR
#define LDR1 
#define LDR2 

// VARIAVEIS DE LEITURA DOS LDR'S
int val_ldr1, val_ldr2; 
int ldr_obstrucao;

pinMode(LDR1, INPUT);
pinMode(LDR1, INPUT);
pinMode(LEDSTRIP, OUTPUT);

int luminosidadeLDR() 
{
  val_ldr1 = analogRead(LDR1);
  val_ldr2 = analogRead(LDR2);

  if( ( (ldr1 + ldr2) / 2) < VALOR_MINIMO)
  {
    digitalWrite(LEDSTRIP, HIGH);
  }
  else 
    digitalWrite(LEDSTRIP, LOW); 

  if( (val_ldr1 > (val_ldr1 + OBSTRUCAO) ) || 
      (val_ldr2 > (val_ldr1 + OBSTRUCAO) ) )
  {
    ldr_obstrucao = 1;                  // Indica que o sensor está obstruido 
  }
  else{
    ldr_obstrucao = 0;                  // Indica que o sensor está obstruido 
  }

  return ldr_obstrucao;
}
