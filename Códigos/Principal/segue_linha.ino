void segue_linha() {
  
//Frente se os dois estiverem no branco
if(analogRead(sensor_direito) < corteD and analogRead(sensor_esquerdo) < corteE){
   verifica_obstaculo();
   frente(0.1);
}

//Sensor da extrema esquerda
if(analogRead(sensor_extrema_esquerda) > corteEE){
     verifica_obstaculo();
<<<<<<< HEAD
     while(analogRead(sensor_esquerdo) < corteE) {motor_direito.step(5);}
=======
     if (direcao_automatica) {direcao_inicial = HIGH;}
     while(analogRead(sensor_esquerdo) < corteE) {
      motor_direito.step(5);
      }
>>>>>>> parent of 2525037... Alpha 1.31
     decisao();
     frente(3);
     while(analogRead(sensor_meio)<corte_meio) {  
        girar_esquerda(1);
        } 
} 

//Sensor da extrema direita
if(analogRead(sensor_extrema_direita) > corteED){
    verifica_obstaculo();
<<<<<<< HEAD
    while(analogRead(sensor_direito) < corteD) {motor_esquerdo.step(5);}
=======
    if (direcao_automatica) {direcao_inicial = LOW;}
    while(analogRead(sensor_direito) < corteD) {
      motor_esquerdo.step(5);
      }
>>>>>>> parent of 2525037... Alpha 1.31
    decisao();
    frente(3);
    while(analogRead(sensor_meio)<corte_meio) {  
      girar_direita(1);
      }                
}

//virar pra esquerda se o sensor da esquerda perceber a linha
else if(analogRead(sensor_esquerdo) > corteE) {
   verifica_obstaculo();       
   esquerda();
   }

////virar pra direita se o sensor da direita perceber a linha
else if(analogRead(sensor_direito) > corteD){
   verifica_obstaculo(); 
   direita();
   }
}
