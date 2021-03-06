    /*
==============================================================================================================
BIBLIOTECAS:
==============================================================================================================*/


/*
==============================================================================================================
MAPEAMENTO DE HARDWARE:
==============================================================================================================*/
  
  //Motores de passo
  #define step_esquerdo 2
  #define step_direito 3
  #define direcao_esquerdo 5
  #define direcao_direito 6
  #define enable_pin 8
  
  //Sensores de linha
  #define sensor_extrema_direita A11
  #define sensor_direito A13
  #define sensor_meio A15
  #define sensor_esquerdo A12
  #define sensor_extrema_esquerda A14
  
  //Sensor de toque
  #define botao 53
  
  //Pinos de conexao dos sensores de cor
  const int s2 = 15; //s2 direito e esquerdo
  const int s3 = 14; //s3 direito e esquerdo
  
  const int out_E = 16; //Out esquerdo
  const int out_D = 17; //Out direito

/*
==============================================================================================================
CONSTANTES:
==============================================================================================================*/

  #define tempo_passo 6
  #define leituras 50 //número de leituras no verde
  
  //cortes dos sensores de linha
  #define corteD 180
  #define corteE 180
  #define corte_meio 100
  #define corteED 350
  #define corteEE 350


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
  
  //Pra que lado o robô desvia do obstáculo:
  bool direcao_inicial = HIGH; //HIGH para esquerda, LOW para Direita
  bool direcao_automatica = LOW;

/*
==============================================================================================================
CONFIGURAÇÃO:
==============================================================================================================*/
void setup() {

  //Motores
  pinMode(step_esquerdo, OUTPUT);
  pinMode(step_direito, OUTPUT);
  pinMode(direcao_esquerdo, OUTPUT);
  pinMode(direcao_direito, OUTPUT);
  pinMode(enable_pin, OUTPUT);
  digitalWrite(8, LOW);

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
