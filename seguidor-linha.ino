#include <AFMotor.h>
 
AF_DCMotor motor_um(1); //Seleciona o motor 1
AF_DCMotor motor_dois(2); //Seleciona o motor 4
AF_DCMotor motor_tres(3); //Seleciona o motor 1
AF_DCMotor motor_quatro(4); //Seleciona o motor 4
 
#define SENSORD A5
#define SENSORE A4

int SENSOR1, SENSOR3;
 
//deslocamentos de calibracao
int leftOffset = 0, rightOffset = 0, centre = 0;
//pinos para a velocidade e direcao do motor
int speed1 = 3, speed2 = 11, direction1 = 12, direction2 = 13;
//velocidade inicial e deslocamento de rotacao
int startSpeed = 200, rotate = 150;
//limiar do sensor
int threshold = 200, esq = 100, dir = 85;
//velocidades iniciais dos motores esquerdo e direito
int left = startSpeed, right = startSpeed;

//Rotina de calibracao do sensor
void calibrate(){
 for (int x=0; x<10; x++) //Executa 10 vezes para obter uma media
 {
   delay(100);
   SENSOR1 = analogRead(SENSORD);
   SENSOR3 = analogRead(SENSORE);
   leftOffset = leftOffset + SENSOR1;
   rightOffset = rightOffset + SENSOR3;
   delay(100);
 }
 //obtem a media para cada sensor
 leftOffset = leftOffset /10;
 rightOffset = rightOffset /10;
 //calcula os deslocamentos para os sensores esquerdo e direito
 //leftOffset = centre - leftOffset;
 //rightOffset = centre - rightOffset;
}
 
void setup(){
  Serial.begin(9600);
  //calibrate();
  Serial.print("Fora Temer");
  delay(3000);
}

void lerSensores(){
  SENSOR1 = analogRead(SENSORD) + leftOffset;
  SENSOR3 = analogRead(SENSORE) + rightOffset;
}

//Essa função faz o robô virar a esquerda
void vireEsquerda(){
  Serial.print("esquerda");
  left = startSpeed;
  right = startSpeed - rotate;
  setVelocidadeMotores();
}

//Vira o robô para a direita
void vireDireita(){
  Serial.print("direita");
  left = startSpeed - rotate;
  right = startSpeed;
  setVelocidadeMotores();
}


void seguirFrente(){
  Serial.print("frente");
  left = startSpeed;
  right = startSpeed;
  setVelocidadeMotores();
}

void setVelocidadeMotores(){
  motor_um.setSpeed(left);
  motor_um.run(FORWARD);
  motor_quatro.setSpeed(left);
  motor_quatro.run(FORWARD);
  motor_dois.setSpeed(right);
  motor_dois.run(FORWARD);
  motor_tres.setSpeed(right);
  motor_tres.run(FORWARD);      
}

void loop(){
  Serial.println(SENSOR1);
  Serial.println(SENSOR3);

  //utiliza a mesma velocidade em ambos os motores
  left = startSpeed;
  right = startSpeed;
 
  //le os sensores e adiciona os deslocamentos
  lerSensores();
  
  if(SENSOR1<dir){
  //Se SENSOR1 for maior do que a constante,
  //vire para a direita
    vireDireita(); 
  }
  else if(SENSOR3<esq){
  //Se SENSOR3 for maior do que a constante,
  //vire para a esquerda
    vireEsquerda();
  }
  else{
    //Se não satisfazer a nenhuma das duas condiçoes,
    //seguir em frente
    seguirFrente();
   }
}
