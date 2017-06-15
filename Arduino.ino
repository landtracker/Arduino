#include <Wire.h>
#include "Pinagem.h"
#include <Servo.h>
#include"ServoMotor.h"

#define SLAVE_ADDRESS 0x04


int servo = 0;
int angulo = 0;
bool flag = true;


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


  Wire.begin(SLAVE_ADDRESS);


  // define callbacks for i2c communication
  //Wire.onReceive(receiveData);
  Wire.onReceive(receiveData);

  Wire.onRequest(sendData);
  Serial.println("Ready!");


}

void loop()
{

  delay(10);
}

void receiveData(int byteCount) {



  Serial.println("Entrando na receiveData");



  while (Wire.available()) {
    Serial.println("Entrando no while da receiveData");

    if(flag)
    {

          servo = Wire.read();     
           
      
          Serial.println("Servo requerido");
          Serial.println(servo);

          if(servo > 0 & servo <4)
          {
             flag = false;
          }

          else{flag = true;}
      
    }

    else 
    {


            angulo = Wire.read();             
        
            Serial.println("Angulo Selecionado");
            Serial.println(angulo);
            
            if(angulo >= 0 & angulo <= 180)
              {
                 flag = true;
                 setServo();
              }
    
              else
              {flag = false;}      
    }

  }
}


void setServo() {


   if (servo > 0 & servo < 4)
    {

      if (servo == 1)
      {

        if (angulo >= 0 & angulo <=180)
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

  if(!flag)
  {
      Wire.write(servo);

  }

  else 
  {

    Wire.write(angulo);
  }

}
