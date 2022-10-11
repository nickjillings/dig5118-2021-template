int buttonPin = 2;
bool previousButtonState = LOW;
int counter = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool state = digitalRead(buttonPin);
  if (previousButtonState == LOW && state == HIGH) {
    counter++;
    Serial.println(counter);
  }
  previousButtonState = state;
  delay(10);
}
