#include <Servo.h>

Servo servo[4][3];
//define servos' ports
const int servoPin[4][3] = { {2, 3, 4}, {5, 6, 7}, {8, 9, 10}, {11, 12, 13} };
Servo headServo;

#define trigPin 15
#define echoPin 16

bool pathR = false, pathL = false;

long measureDistance(){
  long duration;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  return (duration / 58);
}

void lookingForPath(){
  int distanceL, distanceR;

  headServo.write(90);
  distanceR = measureDistance();
  headServo.write(-90);
  distanceL = measureDistance();

  if (distanceR > distanceL){
    pathR = true;
    pathL = false;
  }
  if (distanceR < distanceL){
    pathR = false;
    pathL = true;
  }
  else{
    pathR = true;
    pathL = false;
  }
}

void moveForward(){
  //the robot moves forward normally
}
void moveBackwards(){
  //the robot moves backwards normally
}
void spinLeft(){
  //the robot looks to the left and then moves forwards
}
void spinRight(){
  //the robot looks to the right and then moves forwards
}
void setup() {
  //pins from 2 to 13 are for servos
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 3; j++){
      servo[i][j].attach(servo_pin[i][j]);
    }
  }
  //pin 13 is head servo
  headServo.attach(14);

  //ultrasonic sensory
  Serial.begin(9600);
  pinMode (echoPin, INPUT);
  pinMode (trigPin, OUTPUT);
}

void loop() {
  int distance;

  distance = measureDistance();

  if (distance < 5)
  {
    lookingForPath();
  }

  if (pathR){
    spinRight();
    pathR = false;
    pathL = false;
  }

  if (pathR){
    spinLeft();
    pathR = false;
    pathL = false;
  }
}



