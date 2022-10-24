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
    //https://www.arduino.cc/reference/en/language/functions/random-numbers/random/
    Serial.println(random(0, 255));
  }
  previousButtonState = state;
  delay(10);
}
