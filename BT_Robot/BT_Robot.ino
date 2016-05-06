#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(1); //left back
Adafruit_DCMotor *motor2 = AFMS.getMotor(2); //right back
Adafruit_DCMotor *motor3 = AFMS.getMotor(3); //right front
Adafruit_DCMotor *motor4 = AFMS.getMotor(4); //left front

const int trigPin = 3;
const int echoPin = 2;

long duration;
int distance;

void setup() {
  Serial.begin(9600);

  AFMS.begin();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    String leftSpeedString = command.substring(0, 4);
    String rightSpeedString = command.substring(4, 8);
    int left = leftSpeedString.toInt();
    int right = rightSpeedString.toInt();
    if (left > 0 && right > 0) {
      distance = calculateDistance();
      if (distance > 10) {
        move(left, right);
      } else {
        move(0, 0);
      }
    } else {
      move(left, right);
    }
  }
}

void move(int leftSpeed, int rightSpeed) {

  //MOTOR 1,4 LEFT
  //MOTOR 2,3 RIGHT
  boolean left, right;

  if (leftSpeed <= 0) {
    left = true;
  } else {
    left = false;
  }
  if (rightSpeed <= 0) {
    right = true;
  } else {
    right = false;
  }

  leftSpeed = abs(leftSpeed);
  rightSpeed = abs(rightSpeed);

  motor1->setSpeed (leftSpeed);
  motor2->setSpeed (rightSpeed);
  motor3->setSpeed (rightSpeed);
  motor4->setSpeed (leftSpeed);

  if (left) {
    motor1->run(BACKWARD);
    motor4->run(BACKWARD);
  } else {
    motor1->run(FORWARD);
    motor4->run(FORWARD);
  }

  if (right) {
    motor2->run(BACKWARD);
    motor3->run(BACKWARD);
  } else {
    motor2->run(FORWARD);
    motor3->run(FORWARD);
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}

