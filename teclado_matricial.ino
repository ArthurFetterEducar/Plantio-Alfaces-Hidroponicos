



int b1,b2,b3,b4,b5;
int botao1,botao2,botao3,botao4,botao5;
int comando = 0;

void setup() {
 pinMode(botao1,INPUT);
 pinMode(botao2,INPUT);
 pinMode(botao3,INPUT);
 pinMode(botao4,INPUT);
 pinMode(botao5,INPUT); 
}

void loop() {

 // Botão da esquerda
 if(botao1 == 0 && b1 == 0){
  comando = 1;             // Comando que sera retornado
  b1 = 1;                  // Impede a repetição 
 }
 if(botao1 == 1)
  b1 = 0;                  // Sinaliza que o boão foi solto

 // Botão da direita
 if(botao2 == 0 && b2 == 0){
  comando = 2;             // Comando que sera retornado
  b2 = 2;                  // Impede a repetição 
 }
 if(botao2 == 1)
  b2 = 0;                  // Sinaliza que o boão foi solto

 // Botão de Cima 
  if(botao3 == 0 && b3 == 0){
  comando = 3;             // Comando que sera retornado
  b3 = 1;                  // Impede a repetição 
 }
 if(botao3 == 1)
  b3 = 0;                  // Sinaliza que o boão foi solto
  
 //Botão Baixo
  if(botao4 == 0 && b4 == 0){
  comando = 4;             // Comando que sera retornado
  b4 = 1;                  // Impede a repetição 
 }
 if(botao4 == 1)
  b4 = 0;                  // Sinaliza que o boão foi solto 
  
 //Botão de Confirmar
  if(botao5 == 0 && b5 == 0){
  comando = 5;             // Comando que sera retornado
  b5 = 1;                  // Impede a repetição 
 }
 if(botao5 == 1)
  b5 = 0;                  // Sinaliza que o boão foi solto   
 
 return comando;

}
