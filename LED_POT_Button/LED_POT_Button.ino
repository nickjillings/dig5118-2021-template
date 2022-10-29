int ledPin = 6;
int buttonPin = 2;

bool previousButtonState = LOW;
bool ledState = LOW;

float sensorValue;
float PWMvalue; //to do the scaling you need to use float otherwise using map()

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}
void loop() {
  bool buttonState = digitalRead(buttonPin);

  if (previousButtonState == LOW && buttonState == HIGH) {
    // Invert the ledState. Can also do ledState = !ledState.
    if (ledState == HIGH) {
      ledState = LOW;
    } else {
      ledState = HIGH;
    }
  }
  previousButtonState = buttonState;
  //digitalWrite(ledPin, ledState);
  //delay(10); // rudimentary debouncing here
if (ledState == HIGH){
    sensorValue = analogRead(A0);
    PWMvalue = sensorValue*255; 
    PWMvalue = int(PWMvalue/1023);
    //PWMvalue = map(sensorValue, 0, 1023, 0, 255);
    analogWrite(ledPin, PWMvalue);
    //check from the serail monitor and serial plotter
    Serial.print("InputPotValue:");
    Serial.print(sensorValue);
    Serial.print(",");
    Serial.print("PWM Value:");
    Serial.print(PWMvalue);
    Serial.println();
  } else{
  digitalWrite(ledPin, ledState);
  }
}
