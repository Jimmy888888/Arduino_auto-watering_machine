#include <Servo.h>

bool one=true;


Servo myservo_1;
int angle_1=60;

Servo myservo_2;
int angle_2=100;

Servo myservo_3;
int angle_3=135;

Servo myservo_4;
int angle_4=75;


bool control = false;
bool stay = false;
int sensor=0;
int M_0=12;
int M_1=2;
int M_2=4;
int M_3=7;
int M_4=8;


int GLED =13;

int RLED = 10;
int Rwet = 0;
bool Rdrive = false;
bool RNoWater = false;
int BLED = 11;
int Bwet = 0;
bool Bdrive = false;
bool BNoWater = false;
int Astageangle =40;
int Bstageangle =0;
int Cstageangle =20;
bool Astage = false;
bool Bstage = false;
bool Cstage = false;



void setup() {
  myservo_1.attach(3);
  myservo_2.attach(5);
  myservo_3.attach(6);
  myservo_4.attach(9);
  pinMode(M_1,INPUT);
  pinMode(M_2,INPUT);
  pinMode(M_3,INPUT);
  pinMode(M_4,INPUT);
  pinMode(M_0,INPUT);
    
    
  myservo_3.write(150);
  delay(2000);
  myservo_1.write(0);
  delay(2000);
  myservo_2.write(30);
  delay(2000);
  myservo_4.write(90);
  delay(2000);

  pinMode(RLED, OUTPUT);    
  pinMode(A5,INPUT);
  pinMode(BLED, OUTPUT);    
  pinMode(A4,INPUT);
    
  pinMode(GLED, OUTPUT);
}


void loop() {
  Bwet = analogRead(A4);
  Rwet = analogRead(A5);
  delay(20);
  if(Bwet > 800)
  {
    if(BNoWater!=true)
    {
      Bdrive = true;
      stay = false;
      digitalWrite(BLED, HIGH);
    }
  }
  else
  {
    BNoWater = false;
    Bdrive = false;
    stay = true;
  }
  
  if(Rwet > 800) 
  {
    if(RNoWater!=true)
    {
      Rdrive = true;
      stay = false;
      digitalWrite(RLED, HIGH);
    }
  }
  else
  {
    RNoWater = false;
    Rdrive = false;
    stay = true;
  }

  
  while( Bdrive|| Rdrive)
  {
    if(Bdrive)
    {
      myservo_4.write(112);//left
      delay(1000);
    }
    else if(Rdrive)
    {
      myservo_4.write(80);//right
      delay(1000);
    }
    myservo_3.write(90);
    delay(1000);
    myservo_1.write(70);
    delay(1000);
    myservo_2.write(80);
    delay(1000);
    myservo_1.write(80);
    delay(1000);
    myservo_2.write(100);
    delay(1000);
    myservo_3.write(10);
    delay(1000);
    for(int i=0; i<=40; i=i+1)///////////////////Astage
    {
      myservo_3.write(20+i*2);
      delay(100);
      myservo_2.write(100+i);
      delay(100);
      if(Bdrive)
      {
        Bwet = analogRead(A4);
        delay(10);
        if(Bwet > 800)
        {
          Bdrive = true;
        }
        else
        {
          Bdrive = false;
          digitalWrite(BLED, LOW);
          Astageangle = i;
          Astage = true;
          break;
        }
      }
      else if(Rdrive)
      {
        Rwet = analogRead(A5); 
        delay(10);
        if(Rwet > 800) 
        {
          Rdrive = true;
        }
        else
        {
          Rdrive = false;
          digitalWrite(RLED, LOW);
          Astageangle = i;
          Astage = true;
          break;
        }
      }
    }
    
    if(!Astage)//////////////////////////////////Batage
    {
      for(int i=80; i>=0; i=i-1)
      {
        myservo_1.write(i);
        delay(100);
        
        if(Bdrive)
        {
          Bwet = analogRead(A4);
          delay(10);
          if(Bwet > 800)
          {
            Bdrive = true;
          }
          else
          {
            Bdrive = false;
            digitalWrite(BLED, LOW);
            Bstageangle = i;
            Bstage = true;
            Astage = true;
            break;
          }
        }
        else if(Rdrive)
        {
          Rwet = analogRead(A5); 
          delay(10);
          if(Rwet > 800) 
          {
            Rdrive = true;
          }
          else
          {
            Rdrive = false;
            digitalWrite(RLED, LOW);
            Bstageangle = i;
            Bstage = true;
            Astage = true;
            break;
          }
        }
      }
      
      if(!Bstage)///////////////////////////Cstage
      {
        for(int i=100; i>=20; i=i-1)
        {
          myservo_3.write(i);
          delay(100);

          if(Bdrive)
          {
            Bwet = analogRead(A4);
            delay(10);
            if(Bwet > 800)
            {
              Bdrive = true;
            }
            else
            {
              Bdrive = false;
              digitalWrite(BLED, LOW);
              Cstageangle = i;
              Cstage = true;
              Bstage = true;
              Astage = true;
              break;
            }
          }
          else if(Rdrive)
          {
            Rwet = analogRead(A5); 
            delay(10);
            if(Rwet > 800) 
            {
              Rdrive = true;
            }
            else
            {
              Rdrive = false;
              digitalWrite(RLED, LOW);
              Cstageangle = i;
              Cstage = true;
              Bstage = true;
              Astage = true;
              break;
            }
          }
        }
        Cstage = true;
        Bstage = true;
        Astage = true;
      }
    }
    

    /////////////////////////////////////////////////////////////////////////////////
    if(Cstage)
    {
      for(int i=Cstageangle; i<=90; i=i+1)
      {
        myservo_3.write(i);
        delay(100);
      }
    }

    if(Bstage)
    {
      for(int i=Bstageangle; i<=80; i=i+1)
      {
        myservo_1.write(i);
        delay(100);
      }
    }

    if(Astage)
    {
      for(int i=Astageangle; i<=40; i=i+1)
      {
        myservo_3.write(100-i*2);
        delay(100);
        myservo_2.write(140-i);
        delay(100);
      }
    }
    delay(1000);
    myservo_3.write(90);
    delay(1000);
    myservo_1.write(80);
    delay(1000);
    myservo_2.write(80);
    delay(1000);
    myservo_1.write(70);
    delay(1000);
    myservo_3.write(150);
    delay(1000);
    myservo_1.write(0);
    delay(1000);
    myservo_2.write(30);
    delay(1000);
    myservo_4.write(95);
    delay(2000);
    

    if(Bdrive)
    {
      Bdrive=false;
      BNoWater = true;
    }
    else if(Rdrive)
    {
      Rdrive=false;
      RNoWater = true;
    }
    Astageangle =40;
    Bstageangle =0;
    Cstageangle =20;
    Astage = false;
    Bstage = false;
    Cstage = false;
  }


  if(digitalRead(M_0)==HIGH)
  {
    control = true;
    digitalWrite(GLED, HIGH);
    delay(1000);
  }

  
  while(control)
  {
    if(stay)
    {
      if(digitalRead(M_1)==HIGH)
      {
        sensor = analogRead(A0);            // reads the value of the potentiometer (value between 0 and 1023)
        angle_1 = map(sensor, 0, 684, 0, 75);     // scale it to use it with the servo (value between 0 and 180)
        myservo_1.write(angle_1);
        delay(15);                           // waits for the servo to get there
      }
      else
      {
        delay(15);  
      }
    
      if(digitalRead(M_2)==HIGH)
      {
        sensor = analogRead(A0);            // reads the value of the potentiometer (value between 0 and 1023)
        angle_2 = map(sensor, 0, 684, 5, 95);     // scale it to use it with the servo (value between 0 and 180)
        myservo_2.write(angle_2);
        delay(15);                           // waits for the servo to get there
      }
      else
      {
        delay(15);  
      }
    
      if(digitalRead(M_3)==HIGH)
      {
        sensor = analogRead(A0);            // reads the value of the potentiometer (value between 0 and 1023)
        angle_3 = map(sensor, 0, 684, 0, 110);     // scale it to use it with the servo (value between 0 and 180)
        myservo_3.write(angle_3);
        delay(15);                           // waits for the servo to get there
      }
      else
      {
        delay(15);  
      }
    
      if(digitalRead(M_4)==HIGH)
      {
        sensor = analogRead(A0);            // reads the value of the potentiometer (value between 0 and 1023)
        angle_4 = map(sensor, 0, 684, 20, 180);     // scale it to use it with the servo (value between 0 and 180)
        myservo_4.write(angle_4);
        delay(15);                           // waits for the servo to get there
      }
      else
      {
        delay(15);  
      }
      
    }
    else
    {
      control = false;
      digitalWrite(GLED, LOW);
      delay(1000);
      break;
    }


    if(digitalRead(M_0)==HIGH)
    {
      control = false;
      digitalWrite(GLED, LOW);
      delay(1000);
      break;
    }
  }
}
