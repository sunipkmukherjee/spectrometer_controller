/* 
 * The interrupts here are software interrupts because the adafruit shield itself interacts with the motor using
 * hardware interrups
 */

void check_irq1() //limitswitch 1
{
  if ( digitalRead(irPin1) == HIGH && limitsw1 ) //if the pin is set AND it has been hit the first time (to get rid of the multiple change direction problem)
  { 
    Serial.println(33);//(F("Hit limit switch 1 on irPin 1")); //let us know
    limitsw1 = 0 ; //so that doesn't enter the function even if the switch is high for quite a few loops
    state = FORWARD ; //move towards ls2 only
    stepMot = 0 ; //stop motor
    motStop = 1 ; //indicate that motor has stopped
    dispCount = 0 ; //recalibrate yourself at this opportunity
    dest = -1 ;
    unsigned long pos = 1000 ;
    do {
      Serial.println(34);//(F("Enter number of steps away from Limit Switch 1 (must be between 1000 and 10000 (6 digits): ")) ;
      while(Serial.available()<1);
      pos = Serial.parseInt();//readInt(6) ;
    } while ( pos < 1000 || pos > 10000 ) ;
    myMotor -> step ( pos , state , DOUBLE ) ;
  }
  else 
    return ;
}


void check_irq2() //limitswitch 2
{
  if ( digitalRead(irPin2) == HIGH && limitsw2 ) //if the pin is set AND it has been hit the first time (to get rid of the multiple change direction problem)
  { 
    Serial.println(35);//(F("Hit limit switch 2 on irPin 2")); //let us know
    limitsw2 = 0 ; //so that doesn't enter the function even if the switch is high for quite a few loops
    state = BACKWARD ; //move towards ls1 only
    stepMot = 0 ; //stop motor
    motStop = 1 ; //indicate that motor has stopped
    dispCount = MAX_DISP_BOUND ;
    dest = -1 ;
    unsigned long pos = 1000 ;
    do {
      Serial.println(36);//(F("Enter number of steps away from Limit Switch 2 (must be between 1000 and 10000 (6 digits): ")) ;
      while(Serial.available()<1);
      pos = Serial.parseInt();//readInt(6) ;
    } while ( pos < 1000 || pos > 10000 ) ;
    myMotor -> step ( pos , state , DOUBLE ) ;
  }
  else
    return ;
}

void check_irq3() //limitswitch 2
{
  if ( digitalRead(irPin3) == HIGH && limitsw3 ) //if the pin is set AND it has been hit the first time (to get rid of the multiple change direction problem)
  { 
    Serial.println(37);//(F("Hit stop switch on irPin 3")); //let us know
    limitsw3 = 0 ; //so that doesn't enter the function even if the switch is high for quite a few loops
    stepMot = 0 ; //stop motor
    motStop = 1 ; //indicate that motor has stopped
    Serial.print(38);Serial.print("_");//("Displacement: " ) ;
    Serial.println(dispCount);
    dest = -1 ;
  }
  else
    return ;
}

void check_irq4() //serial
{
  if ( Serial.available() > 0 )
  {
    stepMot = 0 ;
    motStop = 1 ;
    while ( Serial.available() > 0 )
      Serial.read() ; //discard the input
  }
  else
    return ;
}

