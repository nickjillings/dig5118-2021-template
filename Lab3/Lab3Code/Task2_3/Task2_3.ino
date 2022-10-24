int buttonPin = 2;
void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Serial.println("Hello World");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  // Wait 5 seconds
  bool buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("Button Pressed!");
  } else {
    Serial.println("Button Not Pressed!");
  }
}
