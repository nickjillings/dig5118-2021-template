int buttonPin = 2;
bool wasButtonPressed = false;
unsigned long lastMessageSent = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Serial.println("Hello World");
}

void loop() {
  // put your main code here, to run repeatedly:
  bool buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    wasButtonPressed = true;
  }

  unsigned long currentTime = millis();
  if (currentTime - lastMessageSent > 5000) {
    if (wasButtonPressed == true) {
      Serial.println("Button has been pressed");
    } else {
      Serial.println("Button has NOT been pressed");
    }
    lastMessageSent = currentTime;
    wasButtonPressed = false;
  }
}
