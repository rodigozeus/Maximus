/*
==============================================================================================================
Função base de Decisão no Verde:
*/
void decisao() {
    
    //um pouco pra frente, pra posicionar os sensores em cima da linha.
    frente(1);
    
    //Variável que recebe a resposta sobre a cor. 1 - Verde na Direita, 2 - verde na Esquerda, 3 - Verde nos dois lados, 0 - Não detectado.
    int cor = 0;
    cor=detecta_cor();
      
      
      //Verde em ambos:
      if (cor == 3) {
        girar_direita(170);
        while(true) {segue_linha();}
        }
      
      //Verde na Esquerda:  
      else if (cor == 2) {
        frente(4);
        girar_esquerda(80);
        while(true) {segue_linha();}
        }
      
      //Verde na Direita:
      else if (cor == 1) {
        frente(4);
        girar_direita(80);
        while(true) {segue_linha();}
        }    
      
      //Verde não detectado:
      else {
        frente(3);
        //testa se tem linha a frente:
        verifica_meio();
      } 
 
}


/*
==============================================================================================================
Função para informar onde estão as marcas verdes:
*/
int detecta_cor() {
  
  //Variáveis para contar quantas vezes o sensor detectou a cor verde
  int contador_esquerdo = 0;
  int contador_direito = 0;
  
  //Repete a leitura o tanto de vezes definido no início do código
  for(int x=0; x<leituras; x++) {   

      //Efetua a leitura dos sensores.
      ler_sensores();

      //Verde na Direita.
      if (green_D < red_D and green_D < blue_D) {
        contador_direito = contador_direito+1;
        }

      //Verde na Esquerda.
      else if (green_E < red_E and green_E < blue_E) {
        contador_esquerdo = contador_esquerdo+1;
        }

      //Balança pra tentar várias posições diferentes para o sensor.
      //Gira pra direita
      if (x<(leituras/2)) {
        girar_direita(1);
        }
  
      //Gira pra esquerda
      else {
        girar_esquerda(1.8);
        }
       
   }

  //Endireita depois de balançar
  girar_direita(leituras/2.15);
  
  //Verifica a contagem e responde de acordo com o resultado.
  //1 - Verde na Direita, 2 - verde na Esquerda, 3 - Verde nos dois lados, 0 - Não detectado.
        
  if (contador_esquerdo>(leituras*fator_verde) and contador_direito>(leituras*fator_verde)) {return 3;}
  else if (contador_esquerdo>(leituras*fator_verde)) {return 2;}
  else if (contador_direito>(leituras*fator_verde)) {return 1;}
  else {return 0;}
}


/*
==============================================================================================================
Função de leitura propriamente dita dos sensores (Retirado da internet, igual em vários sites)
*/
void ler_sensores() {
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
}

/*
==============================================================================================================
Verifica se tem linha a frente
*/
void verifica_meio() {
        
        int conta_meio = 0;
         
        //Balança e conta:
        for (int x=0; x<(amplitude/2); x++)  {     
            girar_direita(1);
            if (analogRead(sensor_meio)>corte_meio){
                conta_meio=conta_meio+1;         
             }
        }
        for (int x=0; x<amplitude; x++)  {     
            girar_esquerda(1);
            if (analogRead(sensor_meio)>corte_meio){
                conta_meio=conta_meio+1;         
             }
        }

        //Endireita:
        girar_direita((amplitude/2));
        
        //Se tiver linha, segue em frente e volta a seguir linha.
        if (conta_meio>2) {
          frente(4);
          while(true) {segue_linha();}
        }
}
