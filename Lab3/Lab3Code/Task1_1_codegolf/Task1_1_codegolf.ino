int ledPin = 6;
int buttonPin = 2;
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  digitalWrite(ledPin, digitalRead(buttonPin));
}
