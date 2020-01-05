void segue_linha() {
  
//Frente
if(analogRead(sensor_direito) < corteD and analogRead(sensor_esquerdo) < corteE){
   verifica_obstaculo();
   frente(0.1);
}

//Sensor da extrema esquerda
if(analogRead(sensor_extrema_esquerda) > corteEE){
     verifica_obstaculo();
     if (direcao_automatica) {direcao_inicial = HIGH;}
     while(analogRead(sensor_esquerdo) < corteE) {motor_direito.step(5);}
     decisao();
     girar_esquerda(90); 
} 

//Sensor da extrema direita
if(analogRead(sensor_extrema_direita) > corteED){
    verifica_obstaculo();
    if (direcao_automatica) {direcao_inicial = LOW;}
    while(analogRead(sensor_direito) < corteD) {motor_esquerdo.step(5);}
    decisao();
    girar_direita(90);                
}

//Esquerda
else if(analogRead(sensor_esquerdo) > corteE) {
   verifica_obstaculo();       
   esquerda();
   }

////direita
else if(analogRead(sensor_direito) > corteD){
   verifica_obstaculo(); 
   direita();
   }
}
