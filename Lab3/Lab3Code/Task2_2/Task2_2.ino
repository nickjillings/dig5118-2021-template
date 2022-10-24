int buttonPin = 2;
bool previousButtonState = LOW;
void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Serial.println("Hello World");
}

void loop() {
  // put your main code here, to run repeatedly:
  bool buttonState = digitalRead(buttonPin);
  if (previousButtonState == LOW && buttonState == HIGH) {
    Serial.println("Button Pressed!");
  }
  previousButtonState = buttonState;
  delay(10); // rudimentary debouncing
}
