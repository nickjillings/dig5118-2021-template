int ledPin = 6;
int buttonPin = 2;
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void blinkLed(int ledPin, int delayTime) {
  digitalWrite(ledPin, HIGH);
  delay(delayTime);
  digitalWrite(ledPin, LOW);
  delay(delayTime);
}

void loop() {
  bool buttonState = digitalRead(buttonPin);
  // Not great as we can hold our button down and it keeps blinking
  if (buttonState == HIGH) {
    blinkLed(ledPin, 300);
  }
}