/*
==============================================================================================================
BIBLIOTECAS:
==============================================================================================================*/

#include <Stepper.h>

/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
Stepper motor_direito(200, 11, 9, 10, 8);
Stepper motor_esquerdo(200, 4, 7, 6, 5);

//Sensores de linha
#define sensor_extrema_direita A0
#define sensor_direito A1
#define sensor_meio A2
#define sensor_esquerdo A3
#define sensor_extrema_esquerda A4

//Sensor de toque
#define botao 53

//Pinos de conexao dos modulos
const int s2 = 2; //s2 direito e esquerdo
const int s3 = 3; //s3 direito e esquerdo

const int out_E = 14; //Out esquerdo
const int out_D = 15; //Out direito

/*
==============================================================================================================
CONSTANTES:
==============================================================================================================*/

#define velocidade 50
#define leituras 50 //número de leituras no verde

//cortes dos sensores de linha
#define corteD 100
#define corteE 100
#define corte_meio 100
#define corteED 200
#define corteEE 200


/*
==============================================================================================================
VARIÁVEIS:
==============================================================================================================*/

//Variaveis cores
int red_E = 0;
int green_E = 0;
int blue_E = 0;
int red_D = 0;
int green_D = 0;
int blue_D = 0;
bool direcao = HIGH;

/*
==============================================================================================================
CONFIGURAÇÃO:
==============================================================================================================*/
void setup() {

  motor_direito.setSpeed(velocidade);
  motor_esquerdo.setSpeed(velocidade);

  //Pinos dos sensores
  pinMode(sensor_direito, INPUT);
  pinMode(sensor_esquerdo, INPUT);
  pinMode(sensor_extrema_direita, INPUT);
  pinMode(sensor_extrema_esquerda, INPUT);
  pinMode(sensor_meio, INPUT);
  pinMode(botao, INPUT_PULLUP);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out_D, INPUT);
  pinMode(out_E, INPUT);

  Serial.begin(9600);
 
}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {

segue_linha();

} //fecha loop



/*
==============================================================================================================
DEFININDO CADA FUNÇÃO:
==============================================================================================================*/
void segue_linha() {
  
//Frente se os dois estiverem no branco
if(analogRead(sensor_direito) < corteD and analogRead(sensor_esquerdo) < corteE){
   obstaculo();
   frente(0.1);
 
}//fecha frente
//Sensor da extrema esquerda
if(analogRead(sensor_extrema_esquerda) > corteEE){
     direcao = HIGH;
     decisao();               
    //Anda pra frente até que o sensor deixe de perceber a linha
    while(true) {
       obstaculo();
       if (analogRead(sensor_esquerdo)<corteE) {
          break;
          }
          else {
             frente(0.1);
             }
        }//fecha while
                
     //Girar pra esquerda até o sensor do meio perceber a linha
     while(true){ 
        obstaculo();
        left:
        girar_esquerda(1);
        
        if (analogRead(sensor_meio)>corte_meio){
           meio:
           break;
           }
                    
        //Caso o sensor da direita perceba a linha, volta um pouco e tenta centralizar de novo
        if (analogRead(sensor_extrema_direita)>corteED) {
           while(true) {
              obstaculo();
              girar_direita(1);
              if (analogRead(sensor_meio)>corte_meio){
                goto meio;
                }
              if (analogRead(sensor_extrema_esquerda)>corteEE) {
                 goto left;
                 }
              }
           }
           
        } //fecha while 
} //fecha extrema esquerda  

//virar pra esquerda se o sensor da esquerda perceber a linha
else if(analogRead(sensor_esquerdo) > corteE) {
   obstaculo();       
   esquerda();
      
}//fecha esquerda

//Sensor da extrema direita
if(analogRead(sensor_extrema_direita) > corteED){
    direcao = LOW;
    decisao();                
    //Anda pra frente até que o sensor deixe de perceber a linha
    while(true) {
       obstaculo();
       if (analogRead(sensor_direito)<corteD) {
          break;
          }
          else {
             frente(0.1);
             }
        }//fecha while
                
     //Girar pra direita até o sensor do meio perceber a linha
     while(true){ 
        obstaculo();
        girar_direita(1);
        
        if (analogRead(sensor_meio)>corte_meio){
           break;
           }
                    
        //Caso o sensor da esquerda perceba a linha, volta um pouco e tenta centralizar de novo
        if (analogRead(sensor_esquerdo)>corteE) {
           girar_esquerda(1);
           delay(500);
           }
        } //fecha while 
} //fecha extrema direita


////virar pra direita se o sensor da direita perceber a linha
else if(analogRead(sensor_direito) > corteD){
   obstaculo(); 
   direita();

}//fecha direita

                   
//Quando esquerda e direita estiverem na linha, ponto de decisão  
if (analogRead(sensor_direito) > corteD and analogRead(sensor_esquerdo) > corteE){
    
   
}//fecha ponto de decisão
}

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

void para() {
  for (int x=4; x<12; x++) {
    digitalWrite(x, LOW);
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
