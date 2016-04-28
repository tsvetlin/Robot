#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);

char commandDirection[1];
int commandSpeed;
boolean commandBool;

void setup() {
  Serial.begin(9600);

  AFMS.begin();
}

void loop() {

  if (Serial.available() > 0) {
    String command = Serial.readString();
    Serial.println("CommandString " + command);

    command.substring(0,1).toCharArray(commandDirection,1);
    Serial.println("CommandDirection " + commandDirection[0]);
    commandSpeed = command.substring(1,3).toInt();
    Serial.println("CommandSpeed " + commandSpeed);
    
    
      if (commandDirection[0] == 'F') {
      moveForward(commandSpeed, true);
      } else if (commandDirection[0] == 'R') {
      turn(commandSpeed, true);
      } else if (commandDirection[0] == 'L') {
      turn(commandSpeed, false);
      } else if (commandDirection[0] == 'B') {
      moveForward(commandSpeed, false);
      }else if (commandDirection[0] == 'S') {
      moveForward(0, true);
      }/*
    while (command == 'F') {
      moveForward(255, true);
    }
    while (command == 'S') {
      moveForward(0, true);
    }*/
  }

  /*
      switch (command) {
        case 'F':
          moveForward(255, true);
          break;
        case 'R':
          turn(255, true);
          break;
        case 'L':
          turn(255, false);
          break;
        case 'B':
          moveForward(255, false);
          break;
        case 'S':
          moveForward(0, true);
          break;
        default:
          // if nothing matches, do nothing
          break;
      }
    }
  */

}

void moveForward(int speedBot, boolean forward) {

  

  motor1->setSpeed (speedBot);
  motor2->setSpeed (speedBot);
  motor3->setSpeed (speedBot);
  motor4->setSpeed (speedBot);

  if (forward) {
    Serial.println("Moved forward");
    motor1->run(FORWARD);
    motor2->run(FORWARD);
    motor3->run(FORWARD);
    motor4->run(FORWARD);
  } else {
    motor1->run(BACKWARD);
    motor2->run(BACKWARD);
    motor3->run(BACKWARD);
    motor4->run(BACKWARD);
  }
}

void turn(int speedBot, boolean right) {

  motor1->setSpeed (speedBot);
  motor2->setSpeed (speedBot);
  motor3->setSpeed (speedBot);
  motor4->setSpeed (speedBot);

  if (right) {
    motor1->run(FORWARD);
    motor4->run(FORWARD);
    motor2->run (BACKWARD);
    motor3->run (BACKWARD);
  } else {
    motor1->run(BACKWARD);
    motor4->run(BACKWARD);
    motor2->run (FORWARD);
    motor3->run (FORWARD);
  }
}

