#define PIN_TECLA_1
#define PIN_TECLA_2
#define PIN_TECLA_3
#define PIN_TECLA_4
#define PIN_TECLA_5

int debounce1, debounce2, debounce3, debounce4, debounce5;
int tecla1, tecla2, tecla3, tecla4, tecla5;
char comando;


char teclado_matricial()
{
 pinMode(PIN_TECLA_1, INPUT);            // Define todos os pinos como entradas
 pinMode(PIN_TECLA_2, INPUT);
 pinMode(PIN_TECLA_3, INPUT);
 pinMode(PIN_TECLA_4, INPUT);
 pinMode(PIN_TECLA_5, INPUT);
 
 tecla1 = digitalRead(PIN_TECLA_1);      // Lê os pinos referentes a cada tecla
 tecla2 = digitalRead(PIN_TECLA_2); 
 tecla3 = digitalRead(PIN_TECLA_3);
 tecla4 = digitalRead(PIN_TECLA_4);
 tecla5 = digitalRead(PIN_TECLA_5);

 comando = ' ';
 
 // Botão da esquerda
 if(tecla1 == 0 && debounce1 == 0){
  comando = 'C';                         // Comando que sera retornado
  debounce1 = 1;                         // Impede a repetição 
 }
 if(tecla1 == 1)
  debounce1 = 0;                         // Sinaliza que o boão foi solto

 // Botão da direita
 if(tecla2 == 0 && debounce2 == 0){
  comando = 'B';                         // Comando que sera retornado
  debounce2 = 2;                         // Impede a repetição 
 }
 if(tecla2 == 1)
  debounce2 = 0;                         // Sinaliza que o boão foi solto

 // Botão de Cima 
  if(tecla3 == 0 && debounce3 == 0){
  comando = 'E';                         // Comando que sera retornado
  debounce3 = 1;                         // Impede a repetição 
 }
 if(tecla3 == 1)
  debounce3 = 0;                         // Sinaliza que o boão foi solto

 //Botão Baixo
  if(tecla4 == 0 && debounce4 == 0){
  comando = 'D';                         // Comando que sera retornado
  debounce4 = 1;                         // Impede a repetição 
 }
 if(tecla4 == 1)
  debounce4 = 0;                         // Sinaliza que o boão foi solto 

 //Botão de Confirmar
  if(tecla5 == 0 && debounce5 == 0){
  comando = 'e';                         // Comando que sera retornado
  debounce5 = 1;                         // Impede a repetição 
 }
 if(tecla5 == 1)
  debounce5 = 0;                         // Sinaliza que o boão foi solto   

 return comando;
}
