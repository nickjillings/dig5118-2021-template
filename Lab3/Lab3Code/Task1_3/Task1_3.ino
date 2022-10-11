int ledPin = 6;
int buttonPin = 2;
bool previousButtonState = LOW;
bool ledState = LOW;
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  bool buttonState = digitalRead(buttonPin);
  // Have a transition detection here. If the button WAS low and is NOW high, it must have been pressed
  // But if we hold it, it Was High and is High, so will not blink again unless we release it
  // (bar any debouncing issues).
  
  if (previousButtonState == LOW && buttonState == HIGH) {
    // Invert the ledState. Can also do ledState = !ledState.
    if (ledState == HIGH) {
      ledState = LOW;
    } else {
      ledState = HIGH;
    }
  }
  
  previousButtonState = buttonState;
  digitalWrite(ledPin, ledState);
  delay(10); // rudimentary debouncing here
}
