#include <Servo.h>

#define GrausInicial 
#define GrausFinal 
#define SERVO_PIN
#define SERVO_DELAY

Servo_motor servo; 

int pos = 0;                    // Posição do servo motor

servo_motor.attach(SERVO_PIN);  // Pino do Servo Motor


void nutrientesServo() 
{
  for (pos = GrausInicial; pos <= GrausFinal; pos += 1)   // Servo vai ate o valor determinado
  { 
    servo_motor.write(pos);                               // Aplicação para o servo ir ate o local desejado 
    delay(15);                                            // Delay para ir ate a posição (delay necessário para o funcionamento)
  }

  delay(SERVO_DELAY);                                     // Mantém o servo motor estático pelo tempo necessário
  
  for (pos = GrausFinal; pos >= GrausInicial; pos -= 1)   // Volta para o valor inicial 
  {  
    servo_motor.write(pos);                               // Aplicação para o servo ir ate o local desejado 
    delay(15);                                            // Delay para ir ate a posição determinada (delay necessário para o funcionamento)
  }
}
