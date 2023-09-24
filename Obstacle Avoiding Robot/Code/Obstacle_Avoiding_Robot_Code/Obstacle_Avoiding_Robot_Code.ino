#include <Servo.h>
#include <NewPing.h>

// Define motor driver pins
#define motorA1 3
#define motorA2 5
#define motorB1 6
#define motorB2 9

// Define ultrasonic sensor pins
#define trigPin 11
#define echoPin A2

// Define servo motor pin
#define servoPin 10

// Set motor speed
int motorSpeed = 100;  // Adjust this value for desired motor speed (0-255)

//our L298N control pins
const int LeftMotorForward = motorA1;
const int LeftMotorBackward = motorA2;
const int RightMotorForward = motorB1;
const int RightMotorBackward = motorB2;

//sensor pins
#define trig_pin trigPin
#define echo_pin echoPin

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name

void setup() {
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  servo_motor.attach(servoPin);

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 35) {
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft) {
      turnRight();
      delay(800);
      moveStop();
    } else {
      turnLeft();
      delay(800);
      moveStop();
    }
  }
  else {
    moveForward();
  }
  delay(70); // Wait before the next ultrasonic measurement
  distance = readPing();
}

int lookRight() {
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft() {
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int readPing() {
  delay(70); // Delay to prevent interference between measurements
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward() {
  if (!goesForward) {
    goesForward = true;

    analogWrite(LeftMotorForward, motorSpeed);
    analogWrite(RightMotorForward, motorSpeed);

    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
  }
}

void moveBackward() {
  goesForward = false;

  analogWrite(LeftMotorBackward, motorSpeed);
  analogWrite(RightMotorBackward, motorSpeed);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void turnRight() {
  analogWrite(LeftMotorForward, motorSpeed);
  analogWrite(RightMotorBackward, motorSpeed);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);

  delay(250);

  analogWrite(LeftMotorForward, motorSpeed);
  analogWrite(RightMotorForward, motorSpeed);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void turnLeft() {
  analogWrite(LeftMotorBackward, motorSpeed);
  analogWrite(RightMotorForward, motorSpeed);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(250);

  analogWrite(LeftMotorForward, motorSpeed);
  analogWrite(RightMotorForward, motorSpeed);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
