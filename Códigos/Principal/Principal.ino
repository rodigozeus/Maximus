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

}
