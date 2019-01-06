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
int FWSteps = 1200;
int BWSteps = -1200;
int stepperSpeed = 400;
int upVal = LOW;
int downVal = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(upPin, INPUT); 
  pinMode(downPin, INPUT);
  //pinMode(ledPin, OUTPUT);  
  pinMode(redPin, OUTPUT); //设置redPin对应的管脚11为输出
  pinMode(greenPin, OUTPUT); //设置greenPin,对应的管脚9为输出
  pinMode(bluePin, OUTPUT); //设置bluePin对应的管脚10为输出
  
  stepper1.setMaxSpeed(2000.0);
  stepper1.move(1);  // I found this necessary
  stepper1.setSpeed(stepperSpeed);

}//--(end setup )---

void loop() {
  if (steps1==0){
    lightDown(); 
    upVal = digitalRead(upPin);
    downVal= digitalRead(downPin);
    delay (200);
  }
  if (upVal == downVal && steps1==0){
    delay (500);
    return;
  }
  if (upVal == HIGH  && steps1==0){    
      cmdStep(FWSteps); 
  }
  if (downVal == HIGH && steps1==0) {  
     cmdStep(BWSteps); 
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
    Serial.println(steps1);
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
      color(0,255, 0); //绿色亮
      delay(100); 
      color(0, 0, 255); // 蓝色灯亮  
      delay(100); 
      color(255,255,0); // 黄色  
      delay(100); 
      color(255,255,255); // 白色  
      delay(100); 
      color(128,0,255); // 紫色  
      delay(100);   
      color(255, 0, 0); // 红色亮 
}
void lightDown(){
     // Basic colors:  
      color(0, 0, 0); // close 
}
