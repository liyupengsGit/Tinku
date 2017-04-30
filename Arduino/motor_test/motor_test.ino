// Motor Pins
const int EN1 = 42;
const int m11 = 44;
const int m12 = 46;
const int m21 = 48;
const int m22 = 50;
const int EN2 = 52;

// Functions
void forward();
void backward();
void leftTurn();
void rightTurn();
void stopM();

void setup() {
  Serial.begin(9600);

  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, HIGH);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  delay(1000);
}

void loop() {
  if (Serial.available() > 0) {
    char ch = Serial.read();
    if (ch == '2')            // Forward
      forward();
    else if (ch == '8')       // Backword
      backward();
    else if (ch == '4')       // Left Turn
      leftTurn();
    else if (ch == '6')       // Right Turn
      rightTurn();
    else if (ch == '5')
      stopM();
  }
}

void backward() {
  digitalWrite(m12, HIGH);
  digitalWrite(m11, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}

void forward() {
  digitalWrite(m12, LOW);
  digitalWrite(m11, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
}

void leftTurn() {
  digitalWrite(m12, LOW);
  digitalWrite(m11, HIGH);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}

void rightTurn() {
  digitalWrite(m12, HIGH);
  digitalWrite(m11, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
}

void stopM() {
  digitalWrite(m12, LOW);
  digitalWrite(m11, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}

