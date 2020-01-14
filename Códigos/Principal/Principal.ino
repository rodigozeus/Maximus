/*
==============================================================================================================
BIBLIOTECAS:
==============================================================================================================*/
  //Biblioteca para controle do motor de passo
  #include <Stepper.h>

/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
  
  //Motores de passo
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
  #define s2 2 //s2 direito e esquerdo
  #define s3 3 //s3 direito e esquerdo
  #define out_E 14 //Out esquerdo
  #define out_D 15 //Out direito

/*
==============================================================================================================
CONSTANTES:
==============================================================================================================*/
  
  //Velocidade de movimento
  #define velocidade 50

  //Leitura do verde  
  #define leituras 50 //número de leituras no verde
  #define fator_verde 0.05 //percentual de leituras positivas necessárias
  #define amplitude 60 //Amplitude do movimento para tentar achar a linha após não achar verde
    
  //cortes dos sensores de linha
  #define corteD 180
  #define corteE 180
  #define corte_meio 150
  #define corteED 350
  #define corteEE 350


/*
==============================================================================================================
VARIÁVEIS:
==============================================================================================================*/

  //Variaveis para cores
  int red_E = 0;
  int green_E = 0;
  int blue_E = 0;
  int red_D = 0;
  int green_D = 0;
  int blue_D = 0;
  
  //Pra que lado o robô desvia do obstáculo:
  bool direcao_inicial = HIGH; //HIGH para esquerda, LOW para Direita

/*
==============================================================================================================
CONFIGURAÇÃO:
==============================================================================================================*/
void setup() {

  //Inicializa os motores
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

  //Comunicação com o computador
  Serial.begin(9600);
 
}


/*
==============================================================================================================
PROGRAMA PRINCIPAL:
==============================================================================================================*/
void loop() {

  segue_linha();

}
