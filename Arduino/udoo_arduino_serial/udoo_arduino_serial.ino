char ch;
void setup() {
  Serial.begin(115200);
  Serial.println("Port open");
}

void loop() {
  //Serial.println("Communicating");
  if (Serial.available() > 0) {
    ch = Serial.read();
    if (ch == '2')
      Serial.println("2 passed");
    if (ch == '3')
      Serial.println("3 passed");
    if (ch == '4')
      Serial.println("4 passed");
  }
}
