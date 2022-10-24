float Fs = 800; // 8Hz sampling rate
float f0 = 10; //1Hz frequency
float ts = 1/Fs;
float w = 0;
float angle = 0;

void setup() {
  // put your setup code here, to run once:
 // pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

float sineWave() {
  float a = sin(angle);
  angle = angle + w;
  if (angle > TWO_PI){
    angle=angle-TWO_PI;
  }
  return a;
}

void loop() {
  // put your main code here, to run repeatedly
  w = TWO_PI * f0 / Fs;
  float sample = sineWave();
  //Serial.print(angle);
  //Serial.print("\t");
  Serial.println(sample); //scaling to integer
  delay(ts*1000);
}
