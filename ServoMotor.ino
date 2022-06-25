#include <Servo.h>

#define GrausInicial 
#define GrausFinal 

Servo servo; 

int pos = 0;        // Posição do servo motor

void setup() {
  servo.attach(9);  // Pino do Servo Motor
}

void loop() {
  for (pos = GrausInicial; pos <= GrausFinal; pos += 1) {       // Servo vai ate o valor limitado
    
    servo.write(pos);                                           // Aplicação para o servo ir ate o local desejado 
    delay(15);                                                  // delay para ir ate a posição
  }
  for (pos = GrausFinal; pos >= GrausInicial; pos -= 1) {       // Volta para o valor inicial
    servo.write(pos);                                           // Aplicação para o servo ir ate o local desejado 
    delay(15);                                                  // delay para ir ate a posição
  }
}
