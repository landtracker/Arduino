#include <Wire.h>
#include "Pinagem.h"
#include <Servo.h>
#include"ServoMotor.h"

#define SLAVE_ADDRESS 0x04


int servo = 0;
int angulo = 0;
bool instFlag = false;
int instruction = 0;


int cE = 0;
unsigned long lastInterruptTimeE = 0;
unsigned long durationE = 0;
unsigned long velocityE = 0;
int cD = 0;
unsigned long lastInterruptTimeD = 0;
unsigned long durationD = 0;
unsigned long velocityD = 0;

unsigned long distanceE = 0;
unsigned long distanceD = 0;
unsigned long velocity_real = 0;





//Objeto Sonar
ServoMotor servo1(SERVOPIN_01);
ServoMotor servo2(SERVOPIN_02);
ServoMotor servo3(SERVOPIN_03);


void setup() {

  //servomotor e Sonar
  Serial.begin(9600);
  servo1.myservo.attach(SERVOPIN_01);
  servo2.myservo.attach(SERVOPIN_02);
  servo3.myservo.attach(SERVOPIN_03);
  pinMode(SIGPIN_PI_R, INPUT_PULLUP);
  pinMode(SIGPIN_PI_S, OUTPUT);
  digitalWrite(SIGPIN_PI_S, LOW);
  
  Wire.begin(SLAVE_ADDRESS);


  // define callbacks for i2c communication
  //Wire.onReceive(receiveData);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  Serial.println("Ready!");

  pinMode(ENCODER1, INPUT_PULLUP);
  pinMode(ENCODER2, INPUT_PULLUP);
  attachInterrupt(ENCODER1 - 2, countE, FALLING);
  attachInterrupt(ENCODER2 - 2, countD, FALLING);


}

void loop()
{
  //Serial.println(SIGPIN_PI_R);
  
  while (SIGPIN_PI_R){
    digitalWrite(SIGPIN_PI_S,not SIGPIN_PI_R);
    //Serial.println(c);
    //Serial.println(velocity);
    ///delay(1000);
  }
  
  //delay(10);
  //Serial.println((int)velocity);
  //Serial.println(duration);

  if ((millis() - lastInterruptTimeD) > 1000)
    durationD = 0;
  else
    durationD = millis() - lastInterruptTimeD;

    
  if ((millis() - lastInterruptTimeE) > 1000)
    durationE = 0;
  else
    durationE = millis() - lastInterruptTimeE;

  if(((distanceE+distanceD)/2)<0){
    distanceE = 0;
    distanceD = 0;
    digitalWrite(SIGPIN_PI_S, HIGH);
  }
   

}

unsigned long calcVelocity (unsigned long dur)
{
  if (dur != 0)
    return (2000*PI)/dur;
  else
    return 0;
}

void receiveData(int byteCount) {

 
  while (Wire.available()) {
     Serial.println("Entrando no while da receiveData");
     instruction = Wire.read();
     if (instruction == 0 )
      servo = Wire.read();
    else if (instruction == 1){
      angulo = Wire.read();
      setServo();
    } 
     else if (instruction == 2)
      distanceE = Wire.read();
      distanceD = Wire.read();
     
    }

    
}


void setServo() {


  if (servo > 0 & servo < 4)
  {

    if (servo == 1)
    {

      if (angulo >= 0 & angulo <= 180)
      {
        servo1.setAngle(angulo);
        Serial.println("Servo 1 selecionado");
      }

      else
      {
        angulo = -1;
      }
    }

    else if (servo == 2)
    {

      if (angulo >= 0 & angulo <= 180)
      {
        servo2.setAngle(angulo);
        Serial.println("Servo 2 selecionado");
      }

      else
      {
        angulo = -1;
      }
    }

    else if (servo == 3)
    {

      if (angulo >= 0 & angulo <= 180)
      {
        servo3.setAngle(angulo);
        Serial.println("Servo 3 selecionado");

      }

      else
      {
        angulo = -1;
      }
    }
  }

  else
  {
    servo = -1;
  }
}



// callback for sending data
void sendData() {

  velocity_real = (calcVelocity(durationD) + calcVelocity(durationE))/2;

  Wire.write((int)velocity_real);





}



void countE() 
{
  cE++;
  distanceE-=(2*PI);
  lastInterruptTimeE = millis();
  velocityE = calcVelocity(durationE);
  Serial.println("E");
  Serial.println(distanceE);

}


void countD() 
{
  cD++;
  distanceD-=(2*PI);
  lastInterruptTimeD = millis();
  velocityD = calcVelocity(durationD);
  Serial.println("D");
  Serial.println(distanceD);

}




