#include <AFMotor.h>
 
AF_DCMotor motor_um(1); //Seleciona o motor 1
AF_DCMotor motor_dois(2); //Seleciona o motor 2
AF_DCMotor motor_tres(3); //Seleciona o motor 3
AF_DCMotor motor_quatro(4); //Seleciona o motor 4

#define PIN_SE A4
#define PIN_SD A5

int SENSOR_E, SENSOR_D;

//velocidade inicial e deslocamento de rotacao
int startSpeed = 30, rotate = 40;
//velocidades iniciais dos motores esquerdo e direito
int left = startSpeed, right = startSpeed;
boolean andar = true;
int motor1=50, motor2=50, motor3=70, motor4=70;
int limite_se = 130, limite_sd = 100; 

boolean isBlackLeft(){
  lerSensores();
  return SENSOR_E <= limite_se;  
} 

boolean isBlackRight(){
  lerSensores();
  return SENSOR_D <= limite_sd;
}
  
void setup(){
  Serial.begin(9600);
}

void lerSensores(){
  SENSOR_E = analogRead(PIN_SE);
  SENSOR_D = analogRead(PIN_SD);
}

void vireEsquerdaParado(){
  left = 0;
  right = startSpeed + rotate;
  setVelocidadeMotores();
}

void vireDireitaParado(){
  left = startSpeed + rotate;
  right = 0;
  setVelocidadeMotores();
}

void seguirFrente(){
  left = startSpeed;
  right = startSpeed;
  setVelocidadeAndar();
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

void setVelocidadeAndar(){
  motor_um.setSpeed(motor1);
  motor_um.run(FORWARD);
  motor_quatro.setSpeed(motor4);
  motor_quatro.run(FORWARD);
  motor_dois.setSpeed(motor2);
  motor_dois.run(FORWARD);
  motor_tres.setSpeed(motor3);
  motor_tres.run(FORWARD);      
}

void setVelocidadeStop(){
  andar = false;
  motor_um.setSpeed(0);
  motor_um.run(BACKWARD);
  motor_quatro.setSpeed(0);
  motor_quatro.run(BACKWARD);
  motor_dois.setSpeed(0);
  motor_dois.run(FORWARD);
  motor_tres.setSpeed(0);
  motor_tres.run(FORWARD);     
}

void loop(){
  //utiliza a mesma velocidade em ambos os motores
  left = startSpeed;
  right = startSpeed;
  lerSensores();
  
  if(isBlackRight()){
    setVelocidadeStop();
    while(!isBlackLeft()){
      vireEsquerdaParado();
    }
    andar=true;
    }
    else if(andar){
      seguirFrente();
    }
    
 if(isBlackLeft()){
    setVelocidadeStop();
    while(!isBlackRight()){ 
      vireDireitaParado();
    }
    andar=true;
    }
    else if(andar){
      seguirFrente();
    }  
 
 if(isBlackRight() && isBlackLeft()){
    seguirFrente();
  } 
}
