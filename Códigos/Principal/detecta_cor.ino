int detecta_cor()
{
  int contador_esquerdo = 0;
  int contador_direito = 0;
  for(int x=0; x<leituras; x++) {   
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
      //Testa a cor vermelha nos dois sensores
      red_E = pulseIn(out_E, digitalRead(out_E) == HIGH ? LOW : HIGH);
      red_D = pulseIn(out_D, digitalRead(out_D) == HIGH ? LOW : HIGH);
      digitalWrite(s3, HIGH);
      //Testa a cor azul nos dois sensores
      blue_E = pulseIn(out_E, digitalRead(out_E) == HIGH ? LOW : HIGH);
      blue_D = pulseIn(out_D, digitalRead(out_D) == HIGH ? LOW : HIGH);
      digitalWrite(s2, HIGH);
      //Testa a cor verde nos dois sensores
      green_E = pulseIn(out_E, digitalRead(out_E) == HIGH ? LOW : HIGH);
      green_D = pulseIn(out_D, digitalRead(out_D) == HIGH ? LOW : HIGH);

      if (green_D < red_D and green_D < blue_D and green_E < red_E and green_E < blue_E) {
        contador_esquerdo = contador_esquerdo+1;
        contador_direito = contador_direito+1;
        }
    
      else if (green_D < red_D and green_D < blue_D) {
        contador_direito = contador_direito+1;
        }
      
      else if (green_E < red_E and green_E < blue_E) {
        contador_esquerdo = contador_esquerdo+1;
        }
        if (x<(leituras/2)) {
          girar_direita(1);
          }
        else {
          girar_esquerda(2);
        }
       
        }//fecha for
        girar_direita(leituras/2);
        
      if (contador_esquerdo>(leituras/10) and contador_direito>(leituras/10)) {
        return 3;
      }
      else if (contador_esquerdo>(leituras/10)) {
        return 2;
      }
      else if (contador_direito>(leituras/10)) {
        return 1;
      }
}



 void decisao() {
    int cor = 0;
    frente(1.5);
    //delay(3000);
    //Verifica se a cor verde foi detectada e informa qual o lado ou se foi em ambos.
    cor=detecta_cor();

    if (cor == 3) {
      girar_direita(170);
    }
    else if (cor == 2) {
      frente(4);
      girar_esquerda(80);
    }
    else if (cor == 1) {
      frente(4);
      girar_direita(80);
    }    
    else {
      frente(3);
    }

    
 }
