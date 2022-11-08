// #define PI 3.1415926535897932384626433832795
// #define HALF_PI 1.5707963267948966192313216916398
// #define TWO_PI 6.283185307179586476925286766559
// #define DEG_TO_RAD 0.017453292519943295769236907684886
// #define RAD_TO_DEG 57.295779513082320876798154814105
// #define EULER 2.718281828459045235360287471352
//all Available constants are here: 
// https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Arduino.h
// Sine Wave online Version 1

const float Fs = 8000; // 8000Hz sampling rate
const float f0 = 100; //100Hz frequency
float ts = 1/Fs;
float w = TWO_PI * f0 ;
float angle = 0;

void setup() {
  // put your setup code here, to run once:
 // pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

float sineWave() {
  float a = sin(angle);  // sin⁡(2𝜋𝑓 N/𝐹𝑠) = sin⁡(2𝜋𝑓 * ts)
  angle = angle + w*ts;
  if (angle > TWO_PI){
    angle=angle-TWO_PI;
  }
  return a;
}

void loop() {
  // put your main code here, to run repeatedly
  unsigned long ts_delay=ts*1000;
  float sample = sineWave();
  //Serial.print(angle);
  //Serial.print("\t");
  Serial.println(sample); //scaling to integer
  delay(ts_delay);
}
