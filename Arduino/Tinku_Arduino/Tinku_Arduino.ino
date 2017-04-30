/*******************************************************************************************
  Main Arduino program for "Tinku: A personal robot"
  BOARD     : Arduino Mega(1280)
  Written By: Swapnil Verma
*******************************************************************************************/
#include <DynamixelSerial1.h>
// Servo Connections
const int baseServo = 3;
const int midServo = 4;
const int endServo = 5;

//Default Positions
const int baseDefault = 512;
const int midDefault = 512;
const int endDefault = 740;
const int defSpeed = 100;

// Motor Pins
const int EN1 = 42;
const int m11 = 44;
const int m12 = 46;
const int m21 = 48;
const int m22 = 50;
const int EN2 = 52;

// Sonar sensors
const int sensor[6] = {9, 10, 11, 12, 13, 8};

// Serial communication commands
byte command = 0;
/*
   command = 1 : expression
   command = 2 : sonar sensor
   command = 3 : motor
*/
byte expression = 0;
byte collision = 0;
byte motor = 0;

void setup()
{
  Serial.begin(115200);
  // Activate Servos
  Dynamixel.begin(1000000, 40); // Inicialize the servo at 1Mbps and Pin Control 40
  Serial.println("Connected");
  defaultPos();                 // Move servos to the default position

  pinMode(EN1, OUTPUT);         // Set motor pins as output
  pinMode(EN2, OUTPUT);
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, HIGH);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  
  for (int i = 0; i < 6; i++)
    pinMode(sensor[i], OUTPUT);
  delay(1000);
}

/*******************************************************************************************
  Function :loop
  Description:This function loops continuously
*******************************************************************************************/
void loop()
{
  if (Serial.available() > 0) {
    command = Serial.read();
    if (command == 1) {
      expression = Serial.read();
      switch (expression) {
        case 1: yes(); break;
        case 2: no(); break;
        case 3: think(); break;
        case 4: sad(); break;
        default: defaultPos(); break;
      }
    }
    else if (command == 2) {
      collisionCheck();
      Serial.println(collision);
    }
    else if (command == 3) {
      motor = Serial.read();
      switch (motor) {
        case 1: forward(); break;
        case 2: backward(); break;
        case 3: leftTurn(); break;
        case 4: rightTurn(); break;
        case 5: stopM(); break;
      }
    }
  }
}

/*******************************************************************************************
  Function :collisionCheck
  Description:This function is used to detect collision using the sonar sensor
*******************************************************************************************/
void collisionCheck()
{
  float distance[6];
  delay(5);
  for (int i = 0; i < 6; i++) {
    distance[i] = Triger(sensor[i]);
    delay(5);
  }
  for (int i = 0; i < 6; i++) {
    if (distance[i] <= 10)
      bitSet(collision, i);
    else
      bitClear(collision, i);
  }
}

/*******************************************************************************************
  Function  :Triger
  Description:This function is used to control Ultrasonic sensor
*******************************************************************************************/
float Triger(int sensor)
{
  digitalWrite(sensor, LOW);                     //signal pin is set as Low
  pinMode(sensor, OUTPUT);       //signal pin is set as output
  delayMicroseconds(2);        //generate smallest delay
  digitalWrite(sensor, HIGH);      // signal pin is set as High
  delayMicroseconds(5);
  digitalWrite(sensor, LOW);       // signal pin is set as low
  pinMode(sensor, INPUT);      //signal pin is set as input
  long echo = pulseIn(sensor, HIGH);
  float distance  = (echo / 58.138);     //Calculate distance in cm
  return distance;
}

/**********************************************************************************************************
  Function: defaultPos()
  Description: default position of the head
 *********************************************************************************************************/
void defaultPos()
{
  Dynamixel.moveSpeed(baseServo, baseDefault, defSpeed);
  delay(200);
  Dynamixel.moveSpeed(midServo, midDefault, defSpeed);
  delay(200);
  Dynamixel.moveSpeed(endServo, endDefault, defSpeed);
  delay(200);
}

/**********************************************************************************************************
  Function: yes()
  Description: provide "yes" nod to the head
 *********************************************************************************************************/
void yes()
{
  defaultPos();
  delay(200);
  for (int i = 0; i < 2; i++) {
    Dynamixel.moveSpeed(endServo, 810, 100);
    delay(420);
    Dynamixel.moveSpeed(endServo, 740, 100);
    delay(420);
  }
}

/**********************************************************************************************************
  Function: no()
  Description: provide "no" nod to the head
 *********************************************************************************************************/
void no()
{
  defaultPos();
  Dynamixel.moveSpeed(baseServo, 482, 100);
  delay(250);
  Dynamixel.moveSpeed(baseServo, 542, 100);
  delay(400);
  Dynamixel.moveSpeed(baseServo, 482, 100);
  delay(400);
  Dynamixel.moveSpeed(baseServo, baseDefault, 100);
  delay(200);
}

/**********************************************************************************************************
  Function: think()
  Description: provide "think" nod to the head
 *********************************************************************************************************/
void think()
{
  defaultPos();
  Dynamixel.moveSpeed(midServo, 452, 100);
  delay(3000);
  Dynamixel.moveSpeed(midServo, midDefault, 100);
}

/**********************************************************************************************************
  Function: sad()
  Description: provide "sad" nod to the head
 *********************************************************************************************************/
void sad()
{
  defaultPos();
  Dynamixel.moveSpeed(endServo, 840, 100);
  delay(3000);
  Dynamixel.moveSpeed(endServo, endDefault, 100);
}

/**********************************************************************************************************
  Function: backward()
  Description: move robot in backward direction
 *********************************************************************************************************/
void backward() {
  digitalWrite(m12, HIGH);
  digitalWrite(m11, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}
/**********************************************************************************************************
  Function: forward()
  Description: move robot in forward direction
 *********************************************************************************************************/
void forward() {
  digitalWrite(m12, LOW);
  digitalWrite(m11, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
}
/**********************************************************************************************************
  Function: leftTurn()
  Description: move robot in left direction
 *********************************************************************************************************/
void leftTurn() {
  digitalWrite(m12, LOW);
  digitalWrite(m11, HIGH);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}
/**********************************************************************************************************
  Function: rightTurn()
  Description: move robot in right direction
 *********************************************************************************************************/
void rightTurn() {
  digitalWrite(m12, HIGH);
  digitalWrite(m11, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
}
/**********************************************************************************************************
  Function: stopM()
  Description: stop the robot
 *********************************************************************************************************/
void stopM() {
  digitalWrite(m12, LOW);
  digitalWrite(m11, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}
