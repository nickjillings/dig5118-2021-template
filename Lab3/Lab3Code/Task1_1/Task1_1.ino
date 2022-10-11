int ledPin = 6;
int buttonPin = 2;
bool previousButtonState = LOW;
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
//  Serial.begin(115200);
}

void loop() {
  bool buttonState = digitalRead(buttonPin);
  
  if (previousButtonState == LOW && buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
//    Serial.print(buttonState);
  } else if (previousButtonState == HIGH && buttonState == LOW)  {
    digitalWrite(ledPin, LOW);
//    Serial.print(buttonState);
  }
  previousButtonState = buttonState;
  delay(10);
}
