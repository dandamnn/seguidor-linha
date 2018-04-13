#include <AFMotor.h>
 
AF_DCMotor motor_um(1); //Seleciona o motor 1
AF_DCMotor motor_dois(2); //Seleciona o motor 4
AF_DCMotor motor_tres(3); //Seleciona o motor 1
AF_DCMotor motor_quatro(4); //Seleciona o motor 4
 
int SENSOR1, SENSOR2, SENSOR3;
 
//deslocamentos de calibracao
int leftOffset = 0, rightOffset = 0, centre = 0;
//pinos para a velocidade e direcao do motor
int speed1 = 3, speed2 = 11, direction1 = 12, direction2 = 13;
//velocidade inicial e deslocamento de rotacao
int startSpeed = 70, rotate = 30;
//limiar do sensor
int threshold = 5;
//velocidades iniciais dos motores esquerdo e direito
int left = startSpeed, right = startSpeed;
 
//Rotina de calibracao do sensor
void calibrate()
{
 for (int x=0; x<10; x++) //Executa 10 vezes para obter uma media
 {
   delay(100);
   SENSOR1 = analogRead(0);
   SENSOR2 = analogRead(1);
   SENSOR3 = analogRead(2);
   leftOffset = leftOffset + SENSOR1;
   centre = centre + SENSOR2;
   rightOffset = rightOffset + SENSOR3;
   delay(100);
 }
 //obtem a media para cada sensor
 leftOffset = leftOffset /10;
 rightOffset = rightOffset /10;
 centre = centre / 10;
 //calcula os deslocamentos para os sensores esquerdo e direito
 leftOffset = centre - leftOffset;
 rightOffset = centre - rightOffset;
}
 
void setup()
{
  //calibrate();
  delay(3000);
}

void lerSensores(){
  SENSOR1 = analogRead(0) + leftOffset;
  SENSOR2 = analogRead(1);
  SENSOR3 = analogRead(2) + rightOffset;
}

//Essa função faz o robô virar a esquerda(vai para Cuba)
void vireEsquerda(){
  left = startSpeed + rotate;
  right = startSpeed - rotate;
}

//Vira o robô para a direita(Bolsonaro 2018)
void vireDireita(){
  left = startSpeed - rotate;
  right = startSpeed + rotate;
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

void loop()
{
  //utiliza a mesma velocidade em ambos os motores
  left = startSpeed;
  right = startSpeed;
 
  //le os sensores e adiciona os deslocamentos
  lerSensores();
  
  //Se SENSOR1 for maior do que o sensor do centro + limiar,
  //vire para a direita
  if (SENSOR1 > SENSOR2+threshold) {
    vireEsquerda();  
  }
 
  //Se SENSOR3 for maior do que o sensor do centro + limiar,
  //vire para a esquerda
  if (SENSOR3 > (SENSOR2+threshold)){
    vireDireita();
  }
 
  //Envia os valores de velocidade para os motores
  setVelocidadeMotores();
  
}
