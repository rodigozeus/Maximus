void obstaculo() {
      if (digitalRead(botao) == LOW) {
          if (direcao) {
            desvia_esquerda();
          }
          else {
            desvia_direita();
          }

      }
}

void desvia_direita() {
  tras(3);
  girar_direita(90);
  frente(20);
  girar_esquerda(90);
  frente(30);
  girar_esquerda(90);
  while(analogRead(sensor_meio)<corte_meio) {  
    frente(0.1);
  }
  frente(2);
  girar_direita(70);
 }
 
void desvia_esquerda() {
  tras(3);
  girar_esquerda(90);
  frente(20);
  girar_direita(90);
  frente(30);
  girar_direita(90);
  while(analogRead(sensor_meio)<corte_meio) {  
    frente(0.1);
  }
  frente(2);
  girar_esquerda(70);
 }
