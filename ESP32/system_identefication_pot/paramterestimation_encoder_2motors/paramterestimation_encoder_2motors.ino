#include <Servo.h>

Servo ESC1;
Servo ESC2;




int value = 0;
int value2 = 0;
volatile int posi   = 0; //current  angular
long         prevT  =  0 ; //previous time
float bias = 0 ;
volatile float  angle    = 0;

 


#define ENCA 2
#define ENCB 3
#define ESC1_PIN 9
#define ESC2_PIN 5

void setup()
{

  //Encoder
  pinMode(ENCA, INPUT_PULLUP);
  pinMode(ENCB, INPUT_PULLUP);
  pinMode(ESC1_PIN, OUTPUT);
  pinMode(ESC2_PIN, OUTPUT);
  

  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder1, RISING);
  Serial.begin(9600);
  ESC1.attach(ESC1_PIN);
  ESC2.attach(ESC2_PIN);
  delay(1000);
  ESC1.writeMicroseconds(1000);
  ESC2.writeMicroseconds(1000);
  delay(2000);
  for (int i = 0;i<51;i++)
  {
    ESC2.writeMicroseconds(1030);
    //delay(4000);
    ESC1.writeMicroseconds(1030);
    delay(10);
  }
  
  delay(4000);

}

void loop()
{

  // time difference
  long currT = micros();
  int pot = analogRead(A0);
  


  if ( angle > 43.2)
  {
    bias  = (angle - 43.2)  + bias;
    angle = angle - (angle - 43.2);
  }

  if (angle < -43.2 )
  {
    bias = bias  +  (angle + 43.2 );
    angle = angle - (angle + 43.2 );
  }



  if (pot>=512)
  {
    ESC1.writeMicroseconds(1030);
    ESC2.writeMicroseconds(1030+fabs(pot-512));
  }
  else
  {
    ESC2.writeMicroseconds(1030);
    ESC1.writeMicroseconds(1030+fabs(pot-512));
  }
  
  
  Serial.print(currT);
  Serial.print("  ");
  Serial.print(angle);
  Serial.print("  ");
  Serial.println(pot-512);
  delay(10);
  
  
  
}
void readEncoder1()
{
  int b = digitalRead(ENCB);
  if (b > 0)
    posi++;

  else
    posi--;

  angle = posi * 0.6 - bias;

}
