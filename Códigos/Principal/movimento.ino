
void frente(float cm){

  for (int x = 0; x<(int(10*cm)); x++) {
      motor_direito.step(1);
      motor_esquerdo.step(1);
  }
 
}

void tras(float cm){
    
  for (int x = 0; x<(int(10*cm)); x++) {
      motor_direito.step(-1);
      motor_esquerdo.step(-1);
  }
}


void girar_direita(int grau){
     
  for (int x = 0; x<(int (grau*1.09)); x++) {
      motor_direito.step(-1);
      motor_esquerdo.step(1);
  }
     
}

void esquerda(){

     motor_esquerdo.step(0);
     motor_direito.step(1);

}

void direita(){
     
     motor_esquerdo.step(1);
     motor_direito.step(0);
     
}

void girar_esquerda(int grau){
  
  for (int x = 0; x<(int (grau*1.09)); x++) {
      motor_direito.step(1);
      motor_esquerdo.step(-1);
  }

}

 



void para() {
  for (int x=4; x<12; x++) {
    digitalWrite(x, LOW);
  }
}
