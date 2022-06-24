/*
  Este código controla uma carga a partir do CI ponte-H L298
*/

#define EN_PIN      
#define BRIDGE_IN_1    
#define BRIDGE_IN_2    

#define TEMP_IDEAL 

void L298_Controle(float temperatura)
{  
  pinMode(EN_PIN, OUTPUT); 
  pinMode(BRIDGE_IN_1, OUTPUT); 
  pinMode(BRIDGE_IN_2, OUTPUT); 

  if(temperatura > (TEMP_IDEAL + 3)) {
    digitalWrite(BRIDGE_IN_1, HIGH);
    digitalWrite(BRIDGE_IN_2, LOW);
  }
  else if(temperatura < (TEMP_IDEAL - 3)) {
    digitalWrite(BRIDGE_IN_1, LOW);
    digitalWrite(BRIDGE_IN_2, HIGH);
  }
  else {
    digitalWrite(BRIDGE_IN_1, LOW);
    digitalWrite(BRIDGE_IN_2, LOW);
  }
}
