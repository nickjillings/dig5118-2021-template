int ledPin = 6;
int buttonPin = 2;
bool previousButtonState = LOW;
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
  // Have a transition detection here. If the button WAS low and is NOW high, it must have been pressed
  // But if we hold it, it Was High and is High, so will not blink again unless we release it
  // (bar any debouncing issues).
  
  if (previousButtonState == LOW && buttonState == HIGH) {
    blinkLed(ledPin, 300);
  }
  previousButtonState = buttonState;
}
