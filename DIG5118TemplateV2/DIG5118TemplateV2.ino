/*
 * TEMPLATE FOR DIG5118
 * 
 * SKIP TO THE END!!
 * 
 * If you REALLY want to know what this top stuff does though, here we go!
 */

#define FASTADC 1

// defines for a low level function for setting and clearing register bits
// Some compilers may not expose by default so we expose this
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// Since we are mapping over the normal TX/RX ports, we may need a switch to indicate if we want to
// bind to the programming port on pins 0 and 1
// If your programmer doesn't respond in circuit, you'll need to place a switch on PIN 12
// and the internal LED on pin 13 will give a visual indicator of the current arduino mode.

int PROG_PIN = 12; // Which pin is our programming switch on?
int PROG_LED = 13; // Which pin is our programming LED on?

void setup() {
  // Define the roles for our programming switch and LED pins.
  pinMode(PROG_PIN, INPUT);
  pinMode(PROG_LED, OUTPUT);
  
  if (digitalRead(PROG_PIN) == HIGH) {
    // We are in programming mode!
    // Don't do anything else except programming functions
    digitalWrite(PROG_LED, HIGH);
  } else {
    // We are in runtime mode! Run as normal.
    
    // Set the port mappings. This allows us to write to PORTD
    // PORTD is the output register for pins 0-7. It's an 8-bit input that directly
    // maps onto the pins. So an output of 0000 0011 would have all pins off except 0 and 1
    // which would be outputting 5V. A mapping of 1010 1010 would have all odd pins off
    // and even pins on.
    
    DDRD = B11111111;
    PORTD = B00000000;

    cli();//stop interrupts to allow us to reconfigure the interrupts safely.

    //set timer1 interrupt at 62.5kHz
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    
    TCNT1  = 0;//initialize counter value to 0
    
    // set compare match register for 50kHz increments.
    // Basically this counts from 0 and adds 1 at the rate of timer1.
    // When the counter matches this register value, we trigger the callback.
    // At the value of 319 for a timer1 of 16MHz we get 50kHz.
    // 16000000 / (1 * 50000) - 1 (must be <65536)
    // So we are sampling at 50kHz.
    // If we want to increase our sampling rate, we decrease this value!
    OCR1A = 319;

    // This sets timer1 to 62.5kHz, turns on the timer to compare.
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12, CS11 and CS10 bits for 1 prescaler
    TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    sei(); // allow interrupts


    #if FASTADC
     // set prescale to 8
     // This basically makes our DAC less accurate but significantly decreases the sampling time!
     // Brilliant for us, but the bottom bit may be less accurate.
     // Control signals especially should drop the last bit!
     cbi(ADCSRA,ADPS2) ;
     sbi(ADCSRA,ADPS1) ;
     sbi(ADCSRA,ADPS0) ;
    #endif
  }

  // We've done our parts, so now we do the user space setups.
  userSetup();

  /*
   * DON'T ADD YOUR OWN CODE HERE
   * 
   * ADD YOU'RE OWN SETUP CODE TO THE FUNCTION userSetup BELOW!!!!
   */
}

ISR(TIMER1_COMPA_vect) {
  // This is the callback function triggered by timer1
  // Using the configuration by default above, this is called at 50kHz sample rate.
  // We call updateAudio to actually run our code for us
  PORTD = updateAudio();
  /*
   * DO NOT ADD YOU'RE OWN CODE HERE
   * 
   * Use updateAudio to perform your audio effects functions
   */
}

void loop() {
  // Control signals do not need to operate at sampling rate
  // You can't change the gain 50,0000 times a second.
  // But 10 times a second seems reasonable.
  // We use loop to set a 'promisy' update loop.
  // We will not update faster than 10 times a second
  updateControl();
  delay(100); // Set to 100ms or 10Hz
  /*
   * DO NOT ADD YOU'RE OWN CODE HERE
   * 
   * Use updateControl to perform your control functions
   */
}

/*
 *  IGNORE ALL OF THE ABOVE AND MODIFY FROM HERE ON IN!
 */
//#define TWO_PI 6.283185307179586476925286766559
// ===== GLOBAL VARIABLES =====
const float Fs = 50000;
float f0 = 500;
float ts = 1/Fs;
float w = TWO_PI*f0;
float dw = w*ts;
float angle = 0;

int Amp=1;
uint8_t sample = 0;
int16_t counter = 0;

// ===== GLOBAL VARIABLES =====

void userSetup()
{
  Serial.begin(115200);
  /*
   * Our Setup function
   * 
   * Specify any pin modes here that you may need for your digital controller
   * 
   * Remember only pins 8-12 are available for digital in/out
   * and pins A1-A5 for analogue.
   */
}

uint8_t updateAudio()
{
  /*
   * Our audio processing function
   * Get's called at 50kHz sampling rate.
   * Return the next sample to be played at 8-bit resolution
   */
   int AudioValue;
   float sig = sin(angle)*Amp;
   angle = angle + dw;
   if (angle > TWO_PI){
      angle=angle-TWO_PI;
    }
   AudioValue=sig;
   //YW debug using Serail
   Serial.println(sig);
   return AudioValue;
}

void updateControl()
{
  /*
   * Update control loop.
   * Use this to update any non-audio signals, such as reading from a pot or calculating
   * filter coefficients.
   * This gets called at a frequency of 10Hz.
   */
  //f0 = 0.5;
  //w = TWO_PI*f0/Fs;
  Amp = analogRead(A0);
}
