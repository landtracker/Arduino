#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_
  
#include <Arduino.h>
#include <Servo.h> 

class ServoMotor{
    private:
    

    int _pinIn;


    
    public:

    Servo myservo;
    ServoMotor(const int pin);
    ~ServoMotor(){};
        
   void setAngle(int angleIn);  //escreve angulo
   void setPin(int pinIn);
   void Test();
    };
    
#endif
