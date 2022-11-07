#include "Arduino.h"

#define PINO_PELTIER_F 26
#define PINO_PELTIER_Q 25

#define PWM_BAIXO 50
#define PWM_MEDIO 150
#define PWM_ALTO 200
#define PWM_DESLIGADO 0

#define COOLER_F 15 
#define COOLER_Q 16

#define ADC_VREF_mV    3300.0 // in millivolt
#define ADC_RESOLUTION 4096.0
#define PINO_LM35_Q 36
#define PINO_LM35_F 35

#define PINO_DHT22 4
#define DHTTYPE 22

#define PINO_TRIG  39
#define PINO_ECHO  34

#define PINO_BOMBA 2

#define PINO_SERVO 19

//PINO OLED
#define PINO_SCL 22
#define PINO_SDA 21

//PINO DO TECLADO
#define PINO_TECLA_CIMA 32
#define PINO_TECLA_DIRT 26
#define PINO_TECLA_ESQ 25
#define PINO_TECLA_BAIXO 33
#define PINO_TECLA_CONFIRMA 14


//Sensor Boia
#define PINO_BOIA1 17
#define PINO_BOIA2 18

//Define de Tempos
#define MinutoBombaL 1
#define MinutoBombaD 1

#define MinutoDHTR 1

#define MinutoServo 1

#define MinutoSonar 1
