// Motor Pins
const int m11 = 50;
const int m12 = 51;
const int m21 = 52;
const int m22 = 53;

// Functions
void forward();
void backward();
void leftTurn();
void rightTurn();
void stopM();

void setup() {
  Serial.begin(9600);

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

