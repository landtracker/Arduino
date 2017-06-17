#include <Wire.h>
#include "Pinagem.h"
#include <Servo.h>
#include"ServoMotor.h"

#define SLAVE_ADDRESS 0x04


int servo = 0;
int angulo = 0;
bool instFlag = false;
int instruction = 0;


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
  pinMode(SIGPIN_PI_S, OUTPUT);
  digitalWrite(SIGPIN_PI_S, LOW);
  
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
  //Serial.println(SIGPIN_PI_R);
  
  while (SIGPIN_PI_R){
    digitalWrite(SIGPIN_PI_S,not SIGPIN_PI_R);
    Serial.println(servo);
    Serial.println(Tdistance);
    delay(1000);
  }
  
  delay(10);
  Serial.println((int)velocity);
  Serial.println(duration);

  if ((millis() - lastInterruptTime) > 1000)
    duration = 0;
  else
    duration = millis() - lastInterruptTime;

  if(Tdistance<0){
    Tdistance = 0;
    digitalWrite(SIGPIN_PI_S, HIGH);
  }
   

}

unsigned long calcVelocity (unsigned long dur)
{
  if (duration != 0)
    return (2*PI)/dur*1000;
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
      Tdistance = Wire.read();
     
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

  velocity = calcVelocity(duration);

  Wire.write((int)velocity);





}



void count() 
{
  c++;
  Tdistance-=(2*PI);
  lastInterruptTime = millis();

}




