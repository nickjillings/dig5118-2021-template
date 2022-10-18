int ledPin = 6;
float sensorValue;
float PWMvalue; //to do the scaling you need to use float otherwise using map()
void setup() {
// put your setup code here, to run once:
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
}
void loop() {
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
}
