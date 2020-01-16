//Recebe a quantidade de centimetros que o robô deve se mover pra frente
void frente(float cm){

  for (int x = 0; x<(int(10*cm)); x++) {
      motor_direito.step(1);
      motor_esquerdo.step(1);
  }
}

//Recebe a quantidade de centimetros que o robô deve se mover pra trás
void tras(float cm){
    
  for (int x = 0; x<(int(10*cm)); x++) {
      motor_direito.step(-1);
      motor_esquerdo.step(-1);
  }
}

//Recebe a quantidade de graus que o robô deve girar pra direita
void girar_direita(int grau){
     
  for (int x = 0; x<(int (grau*1.09)); x++) {
      motor_direito.step(-1);
      motor_esquerdo.step(1);
  }    
}

//Recebe a quantidade de graus que o robô deve girar pra esquerda
void girar_esquerda(int grau){
  
  for (int x = 0; x<(int (grau*1.09)); x++) {
      motor_direito.step(1);
      motor_esquerdo.step(-1);
  }
}

void esquerda(){

     motor_direito.step(1);
     motor_esquerdo.step(0);
}

void direita(){
     
     motor_esquerdo.step(1);
     motor_direito.step(0);
}

//Desliga todos os motores e deixa as rodas livres.
void para() {
  for (int x=4; x<12; x++) {
    digitalWrite(x, LOW);
  }
}
