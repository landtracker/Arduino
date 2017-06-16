#include <Wire.h>
#include "Pinagem.h"
#include <Servo.h>
#include"ServoMotor.h"

#define SLAVE_ADDRESS 0x04


int servo = 0;
int angulo = 0;
bool flag = true;


int c = 0;
unsigned long Rdistance = 0;
unsigned long Tdistance = 0;

unsigned long lastInterruptTime = 0;
unsigned long duration = 0;
unsigned long velocity = 0;



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
  pinMode(SIGPIN_PI_S, INPUT_PULLUP);


  Wire.begin(SLAVE_ADDRESS);


  // define callbacks for i2c communication
  //Wire.onReceive(receiveData);
  Wire.onReceive(receiveData);

  Wire.onRequest(sendData);
  Serial.println("Ready!");

  pinMode(INTPIN, INPUT_PULLUP);
  attachInterrupt(INTPIN - 2, count, FALLING);


}

void loop()
{

  while (SIGPIN_PI_R){
    
  }
  
  delay(10);
  Serial.println((int)velocity);
  Serial.println(duration);

  if ((millis() - lastInterruptTime) > 1000)
    duration = 0;
  else
    duration = millis() - lastInterruptTime;
    
   velocity = calcVelocity(duration);

}

unsigned long calcVelocity (unsigned long dur)
{
  if (duration != 0)
    return (2*PI*6)/dur*1000;
  else
    return 0;
}

void receiveData(int byteCount) {



  Serial.println("Entrando na receiveData");
  


  while (Wire.available()) {
    Serial.println("Entrando no while da receiveData");

    if (flag)
    {

      servo = Wire.read();


      Serial.println("Servo requerido");
      Serial.println(servo);

      if (servo > 0 & servo < 4)
      {
        flag = false;
      }

      else {
        flag = true;
      }

    }

    else
    {


      angulo = Wire.read();

      Serial.println("Angulo Selecionado");
      Serial.println(angulo);

      if (angulo >= 0 & angulo <= 180)
      {
        flag = true;
        setServo();
      }

      else
      {
        flag = false;
      }
    }

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


  Wire.write((int)velocity);





}



void count() 
{
  c++;
  Rdistance++;
  lastInterruptTime = millis();

}




