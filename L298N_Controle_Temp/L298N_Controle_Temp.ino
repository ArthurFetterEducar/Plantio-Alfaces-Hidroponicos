/*
  Este código controla uma carga a partir do CI ponte-H L298N
*/

#define EN_PIN      
#define BRIDGE_IN_1    
#define BRIDGE_IN_2    

#define TEMP_IDEAL 

char L298_Controle(float temperatura)
{  
  pinMode(EN_PIN, OUTPUT); 
  pinMode(BRIDGE_IN_1, OUTPUT); 
  pinMode(BRIDGE_IN_2, OUTPUT); 

  char peltier_status;  

  if(temperatura > (TEMP_IDEAL + TEMP_OFFSET)) {
    digitalWrite(BRIDGE_IN_1, HIGH);
    digitalWrite(BRIDGE_IN_2, LOW);

    peltier_status = 'Q';                                 // Modifica o estado do peltier para "Quente"
  }
  else if(temperatura < (TEMP_IDEAL - TEMP_OFFSET)) {
    digitalWrite(BRIDGE_IN_1, LOW);
    digitalWrite(BRIDGE_IN_2, HIGH);

    peltier_status = 'F';                                 // Modifica o estado do peltier para "Frio"
  }
  else {
    digitalWrite(BRIDGE_IN_1, LOW);
    digitalWrite(BRIDGE_IN_2, LOW);

    peltier_status = 'D';                                 // Modifica o estado do peltier para "Desligado"
  }

  return peltier_status;
}
