// #define PI 3.1415926535897932384626433832795
// #define HALF_PI 1.5707963267948966192313216916398
// #define TWO_PI 6.283185307179586476925286766559
// #define DEG_TO_RAD 0.017453292519943295769236907684886
// #define RAD_TO_DEG 57.295779513082320876798154814105
// #define EULER 2.718281828459045235360287471352
//all Available constants are here: 
// https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Arduino.h
// Sine Wave Offline Verison 1
const float Fs = 1000; // 1000Hz sampling rate
const float f0 = 40; //40Hz frequency
const float ts = 1/Fs;
int nn = 0;
const float time = 0.4; //2 second time period of the sound
//const int TotalNSamples = (time/ts); //total number of samples 
const int TotalNSamples = round(time/ts);
unsigned long ts_delay=round(ts*1000); //Playback time as Delay
float SineWaveSig[TotalNSamples];
//allocate some memory for sine wave

void setup() {
  //put your setup code here, to run once:
 // pinMode(buttonPin, INPUT);
  
  Serial.begin(9600);
  Serial.print("Number of samples:"); Serial.print("\t"); Serial.println(TotalNSamples);
  Serial.print("Time Delay in ms:"); Serial.print("\t"); Serial.println(ts_delay);
  make_sinewave();
}
void make_sinewave()
{//wirte a for loop to fill all the samples 
  for (int n = 0; n <= TotalNSamples; n++) {
   SineWaveSig[n]=sin(TWO_PI*f0*n/Fs); //𝐴  sin⁡(2𝜋𝑓𝑛/𝐹𝑠)
  }
}

void loop() {
  // put your main code here, to run repeatedly
  float sample = SineWaveSig[nn];
  Serial.println(sample); //scaling to integer/output
  delay(ts_delay);
  nn=nn+1;
  if (nn>2000)
    nn=0;      
  }
