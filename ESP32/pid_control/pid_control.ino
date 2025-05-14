#define ENCA 2
#define ENCB 3

#include <Servo.h>
Servo ESC1;
Servo ESC2;

//kp=0.1331
//ki=0.94
//kd=0.084
 
//hany
float kp = 0.1331*2;
float ki = 0.94/2 ;
float kd = 0.042 ;


//float kp = 1.8/9.93;
//float ki = 7.5/9.93 ;
//float kd = 0.31/9.93 ;



long        prevT = 0;

volatile int posi = 0;
volatile float encoder_angle = 0;

double target_pitch = 0;

volatile double error = 0;
volatile double error_prev = 0;
volatile double delta_error = 0;


float  eintegral   = 0;


float ControlSignal = 0;


void setup() {
  pinMode(ENCA, INPUT_PULLUP);
  pinMode(ENCB, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder1, RISING);
  Serial.begin(9600);

   
 
  ESC1.attach(5);
  ESC2.attach(9);
  ESC1.writeMicroseconds(1000);
  ESC2.writeMicroseconds(1000);
  delay(2000);


  for (int i=0;i<=70;i++)
  {
    ESC1.writeMicroseconds(1030);
    ESC2.writeMicroseconds(1030);
    delay(100);
  }
 delay(5000);

  prevT = micros();
  delay(20);

}

void loop()

{

  int pot = analogRead(A0);
  target_pitch = map(pot,0,1024,-25,25);
  // time difference
  long currT = micros();
  double deltaT = ((double) (currT - prevT))/( 1.0e6 );
  prevT = currT;
  
  noInterrupts(); 
  error = target_pitch  - encoder_angle ;
  interrupts();

  
  eintegral= eintegral + error * deltaT;
  

  delta_error = (error - error_prev) /deltaT;
  error_prev  = error;

  ControlSignal =  kp *  error  +   ki * eintegral  +   kd * delta_error ;




Serial.print(ControlSignal);
Serial.print(" ");
Serial.print(encoder_angle);
Serial.print(" ");
Serial.println(target_pitch);


//if (delta_error == 0 && error == 0 )eintegral-= error * deltaT; //antiWindup

if( ControlSignal >= 300 || ControlSignal <= -300)  eintegral-= error * deltaT; //antiWindup

if (ControlSignal >= 0)
 {
   ControlSignal = constrain(ControlSignal + 1070, 1070, 1300);
   ESC1.writeMicroseconds(ControlSignal+1070);
   ESC2.writeMicroseconds(1070);
 }

 else 
 {
     ControlSignal = constrain(-1*ControlSignal + 1070 , 1070, 1300);
     ESC2.writeMicroseconds(-1*ControlSignal+1070);
     ESC1.writeMicroseconds(1070);
 }
  
 
  
   
   
   
   
}

void readEncoder1()
{
  int b = digitalRead(ENCB);
  if (b > 0) posi++;
  else posi--;
  encoder_angle = posi * 0.6; // Adjust scaling if necessary
}
