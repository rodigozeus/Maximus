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

//Sensores de cor
#define s2 10
#define s3 11
#define out_E 9
#define out_D 8

/*
==============================================================================================================
CONSTANTES:
==============================================================================================================*/

#define velocidade 40

//cortes dos sensores de linha
#define corteD 100
#define corteE 100
#define corte_meio 100
#define corteED 100
#define corteEE 100


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


void para(){
    
     delay(500);
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

 void detecta_cor()
{
      //Rotina que le o valor das cores
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
      //count OUT, pRed, RED
      red_E = pulseIn(out_E, digitalRead(out_E) == HIGH ? LOW : HIGH);
      red_D = pulseIn(out_D, digitalRead(out_D) == HIGH ? LOW : HIGH);
      digitalWrite(s3, HIGH);
      //count OUT, pBLUE, BLUE
      blue_E = pulseIn(out_E, digitalRead(out_E) == HIGH ? LOW : HIGH);
      blue_D = pulseIn(out_D, digitalRead(out_D) == HIGH ? LOW : HIGH);
      digitalWrite(s2, HIGH);
      //count OUT, pGreen, GREEN
      green_E = pulseIn(out_E, digitalRead(out_E) == HIGH ? LOW : HIGH);
      green_D = pulseIn(out_D, digitalRead(out_D) == HIGH ? LOW : HIGH);
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
  tras(5);
  girar_direita(90);
  frente(20);
  girar_esquerda(90);
  frente(30);
  girar_esquerda(80);
  while(analogRead(sensor_meio)<corte_meio) {  
    frente(0.1);
  }
  girar_direita(50);
 }
 
void desvia_esquerda() {
  tras(5);
  girar_esquerda(90);
  frente(20);
  girar_direita(90);
  frente(30);
  girar_direita(80);
  while(analogRead(sensor_meio)<corte_meio) {  
    frente(0.1);
  }
  girar_esquerda(50);
 }
