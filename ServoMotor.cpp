
    #include "ServoMotor.h"


    ServoMotor::ServoMotor(const int pin)
    {
      setPin(pin);
      pinMode(pin, OUTPUT);     
      
     }
  

    
    void ServoMotor::setPin(int pinIn){
    _pinIn = pinIn;
    //attach DEVE ser feito na main
    }
   
    void ServoMotor::setAngle(int angleIn){
       myservo.write(angleIn);
    }

    void ServoMotor::Test()
    {
      for(int i = 0; i <= 18; i++)
      {
        myservo.write(10*i);
        //Serial.println(i);
        delay(150);
      }
  
      for(int i = 18; i >= 0; i--)
      {
        myservo.write(10*i);
        //Serial.println(i);
        delay(150);
      }
    }

