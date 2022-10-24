int buttonPin = 2;
bool previousButtonState = LOW;
void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool state = digitalRead(buttonPin);
  if (previousButtonState == LOW && state == HIGH) {
    Serial.println(1);
  } else if (previousButtonState == HIGH && state == LOW){
    Serial.println(0);
  }
  previousButtonState = state;
  delay(10);
}
