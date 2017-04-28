/*
 * For end servo the last limit is 840. Do not increase than that.
 */
#include <DynamixelSerial1.h>
// Servo Connections
const int baseServo = 3;
const int midServo = 4;
const int endServo = 5;

//Functions
/*void yes();
void no();
void think();
void sad();
void defaultPos();
*/
//Default Positions
const int baseDefault = 512;
const int midDefault = 512;
const int endDefault = 740;
const int defSpeed = 100;

void setup() {
  Serial.begin(115200);
  Dynamixel.begin(1000000, 40); // Inicialize the servo at 1Mbps and Pin Control 42
  Serial.println("Connected");
  defaultPos();                 // Move servos to the default position
  delay(1000);
}

void loop() {
  if (Serial.available() > 0) {
    char ch = Serial.read();
    if (ch == '1')
      yes();
    else if (ch == '0')
      no();
    else if (ch == '2')
      think();
    else if (ch == '3')
      defaultPos();
    else if (ch == '4')
      sad();
    else if (ch == '5')
      kFace();
  }
}
/**********************************************************************************************************
 *Function: defaultPos()
 *Description: default position of the head
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
 *Function: yes()
 *Description: provide "yes" nod to the head
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
 *Function: no()
 *Description: provide "no" nod to the head
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
 *Function: think()
 *Description: provide "think" nod to the head
 *********************************************************************************************************/
 void think()
{
  defaultPos();
  Dynamixel.moveSpeed(midServo, 452, 100);
  delay(3000);
  Dynamixel.moveSpeed(midServo, midDefault, 100);
}

/**********************************************************************************************************
 *Function: sad()
 *Description: provide "sad" nod to the head
 *********************************************************************************************************/
void sad()
{
  defaultPos();
  Dynamixel.moveSpeed(endServo, 840, 100);
  delay(3000);
  Dynamixel.moveSpeed(endServo, endDefault, 100);
}

/**********************************************************************************************************
 *Function: kFace()
 *Description: provide expression for krishna's face
 *********************************************************************************************************/
void kFace()
{
  defaultPos();
  Dynamixel.moveSpeed(midServo, 452, 100);
  delay(200);
  Dynamixel.moveSpeed(endServo, 820, 100);
  delay(3000);
  defaultPos();
}

/**********************************************************************************************************
 *Function: sleepy()
 *Description: provide expression for sleepy face
 *********************************************************************************************************/
