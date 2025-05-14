#define ENCA 2
#define ENCB 3

#include <Servo.h>

Servo ESC1;
Servo ESC2;

float ki = 0.2774;

volatile int posi = 0; // Current angular position
volatile float encoder_angle = 0;
volatile float encoder_prev_angle = 0;
volatile float encoder_velocity = 0;
volatile float encoder_acc = 0;
volatile float filtered_encoder_velocity = 0;
volatile float encoder_prev_vel = 0;
volatile float filtered_encoder_acc = 0;



long prevTime = 0;

//
float K[3]     = {3.0817  ,  0.8418  ,  0.1263};                 // State feedback gain matrix
//kol ma tany rkm ykbr kol ma el amplitute of oscillations yzed , kol ma ys8r aggresive controller with no oscillations
//kol ma talt rkm ys8r kol ma el oscillations tzed 

// States and control input
float x[3] = {0, 0, 0};  // States: [angle, angular velocity, acceleration]
float u    = 0;          // Control input
float r    = 10.8;         // Reference (desired pitch angle)

#define FILTER_ALPHA 0.85  // Low-pass filter smoothing factor

void setup() {
  pinMode(ENCA, INPUT_PULLUP);
  pinMode(ENCB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder1, RISING);


  Serial.begin(9600);


  ESC1.attach(5);
 //ESC2.attach(9);
  ESC1.writeMicroseconds(1000); // Initialize ESC
  //ESC2.writeMicroseconds(1000); // Initialize ESC
  delay(2000);
  //ESC1.writeMicroseconds(1030); // Initialize ESC
  //ESC2.writeMicroseconds(1030); // Initialize ESC
  delay(1000);
  prevTime = micros();
}

void loop() {
  unsigned long currentTime = micros();
  float dt = (currentTime - prevTime) / 1.0e6; // Time in seconds
  prevTime = currentTime;

  // Calculate encoder velocity and acceleration
  encoder_velocity = (encoder_angle - encoder_prev_angle) / dt;
  encoder_prev_angle = encoder_angle;
  filtered_encoder_velocity = FILTER_ALPHA * filtered_encoder_velocity + (1 - FILTER_ALPHA) * encoder_velocity;

  encoder_acc = (filtered_encoder_velocity - encoder_prev_vel) / dt;
  encoder_prev_vel = filtered_encoder_velocity;
  filtered_encoder_acc =FILTER_ALPHA * filtered_encoder_acc + (1 - FILTER_ALPHA) * encoder_acc;


  // Read system states (example: encoder, IMU)
  x[0] = encoder_angle ;
  x[1] = filtered_encoder_velocity;
  x[2] = filtered_encoder_acc;

  static float integral = 0;
  integral += (r - x[0]) * dt;
  u = -K[0] * x[0] - K[1] * x[1] - K[2] * x[2] + r + ki * integral;


  if (u >= 0)
  {
    u = constrain(u + 1000, 1000, 1300);
    ESC1.writeMicroseconds((int)u);
    //ESC2.writeMicroseconds(1030);
  }

  else
  {
    //u = constrain(-u + 1000 , 1000, 1300);
    //ESC2.writeMicroseconds(u);
    ESC1.writeMicroseconds(1000);
  }






  // Debugging output
  Serial.print(u); Serial.print("  "); Serial.println(encoder_angle);
}

void readEncoder1()
{
  int b = digitalRead(ENCB);
  if (b > 0) posi++;
  else posi--;
  encoder_angle = posi * 0.6; // Adjust scaling if necessary
}
