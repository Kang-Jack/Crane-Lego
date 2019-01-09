#include <AccelStepper.h>
#define FULLSTEP 4
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  8     // IN1 on the ULN2003 driver 1
#define motorPin2  9     // IN2 on the ULN2003 driver 1
#define motorPin3  10     // IN3 on the ULN2003 driver 1
#define motorPin4  11     // IN4 on the ULN2003 driver 1

#define upPin 6
#define downPin 7


//#define ledPin 5

int redPin = A0;  // Nano 3 ,R 红色LED 控制引脚 连接到Arduino的 11脚
int bluePin = A1;  //Nano5, B蓝色LED 控制引脚 连接到Arduino的 11脚 
int greenPin = A2;  //Nano6, G绿色LED 控制引脚 连接到Arduino的 9脚


// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(FULLSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
int steps1 = 0;
int FWSteps = 248000;
int BWSteps = -248000;
int stepperSpeed = 200;
int upVal = LOW;
int downVal = LOW;
bool isFW =false;
void setup() {
  Serial.begin(9600);
  pinMode(upPin, INPUT); 
  pinMode(downPin, INPUT);
  //pinMode(ledPin, OUTPUT);  
  pinMode(redPin, OUTPUT); //11
  pinMode(greenPin, OUTPUT); //9
  pinMode(bluePin, OUTPUT); //10
  
  stepper1.setMaxSpeed(1600.0);
  stepper1.setAcceleration(100.0);
  stepper1.move(1);  // I found this necessary
  stepper1.setSpeed(stepperSpeed);

}//--(end setup )---

void loop() {
  if (steps1%9 == 0){
    upVal = digitalRead(upPin);
    downVal= digitalRead(downPin);
  }
  if (upVal == downVal){
    steps1 = stepper1.distanceToGo();
    //Serial.println(steps1);
    if(steps1 != 0)
    {
      stepper1.move(1);  // I found this necessary
      stepper1.setSpeed(stepperSpeed);
      stepper1.runSpeedToPosition();
    }
    lightDown(); 
    isFW =false;
    delay (50);
    return;
  }
  if (upVal == HIGH ){   
      if (isFW)
      {
         if  (steps1==0)
            cmdStep(FWSteps); 
         else
            cmdStep(0); 
      }
      else
      {
        steps1 = 0;
        cmdStep(FWSteps); 
      }
      isFW=true;
  }
  if (downVal == HIGH) {  
      if (!isFW)
      {
         if  (steps1==0)
            cmdStep(BWSteps); 
         else
            cmdStep(0); 
      }
      else
      {
        steps1 = 0;
        cmdStep(BWSteps); 
      }
      isFW=false;
   }
   if (steps1 != 0){
    cmdStep(0); 
   }  
 }

void cmdStep(int steps){
    if (steps1==0){
      lightUp();  
      stepper1.move(steps);
      stepper1.setSpeed(stepperSpeed);
    }
    steps1 = stepper1.distanceToGo();
    //Serial.println(steps1);
    stepper1.runSpeedToPosition();   
}
void color (unsigned char red, unsigned char green, unsigned char blue) 
{    
    analogWrite(redPin, 255-red);   
    analogWrite(bluePin, 255-blue); 
    analogWrite(greenPin, 255-green); 
}  
void lightUp(){
      // Basic colors:  
      color(0,255, 0); //green
      delay(50); 
      color(0, 0, 255); // blue
      delay(50); 
      color(255,255,0); //yellow
      delay(50); 
      color(255,255,255); // white
      delay(50); 
      color(128,0,255); // purple
      delay(50);   
      color(255, 0, 0); // red
}
void lightDown(){
     // Basic colors:  
      color(0, 0, 0); // close 
}

