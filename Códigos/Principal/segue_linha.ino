void segue_linha() {
  
//Frente se os dois estiverem no branco
if(analogRead(sensor_direito) < corteD and analogRead(sensor_esquerdo) < corteE){
   verifica_obstaculo();
   frente(0.1);
}

//Sensor da extrema esquerda
if(analogRead(sensor_extrema_esquerda) > corteEE){
     verifica_obstaculo();
     direcao = HIGH;
     while(analogRead(sensor_esquerdo) < corteE) {
      motor_direito.step(5);
      }
     decisao();
     girar_esquerda(90); 
} 

//Sensor da extrema direita
if(analogRead(sensor_extrema_direita) > corteED){
    verifica_obstaculo();
    direcao = LOW;
    while(analogRead(sensor_direito) < corteD) {
      motor_esquerdo.step(5);
      }
    decisao();
    girar_direita(90);                
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
