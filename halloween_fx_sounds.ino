// Uses a PIR sensor to detect movement, triggers fx sound board
 /*
 * HARDWARE:
 * - adafruit qtpy 
 *  https://learn.adafruit.com/adafruit-qt-py?view=all#pinouts
 * - Adafruit Audio FX Mini Sound Board -
 *   https://learn.adafruit.com/adafruit-audio-fx-sound-board
 * - PIR Sensor  
 * - powered speaker
 * 
 */
 
const byte pirPin = 3;          // input pin (PIR sensor)
const byte fxPin0 = 7;          // connects to fx board pin 0
const byte fxPin1 = 8;          // connects to fx board pin 1
volatile byte pirState = LOW;   // we start, assuming no motion detected
volatile bool toggle = false;   // used to toggle between fxPins

void setup() {
  Serial.begin(115200);
  pinMode(fxPin0, OUTPUT);
  pinMode(fxPin1, OUTPUT);
  digitalWrite(fxPin0, HIGH);    // set the pin HIGH as default status, 1 = no_sound
  digitalWrite(fxPin1, HIGH);    // set the pin HIGH as default status, 1 = no_sound
  attachInterrupt(digitalPinToInterrupt(pirPin), motion, RISING);
  delay(10000);                 // don't immediately trigger at power on, wait a bit
  Serial.println("\nIf motion detected --> play sound effects");  
}

void loop() {
  //Serial.print("pirPin state: "); Serial.println(digitalRead(pirPin));
  if (pirState == HIGH){
    Serial.print("Toggle: "); Serial.println(toggle);
    Serial.print("Motion detected: ");
    if (toggle) {
      Serial.println("fxPin0 sound effect triggered");
      digitalWrite(fxPin0, LOW);
    }
    else {
      Serial.println("fxPin1 sound effect triggered");
      digitalWrite(fxPin1, LOW);
    }
    delay(500);
    pirState = LOW;               // reset the pirState, no motion
    Serial.println("Reset pirState");
  }
  digitalWrite(fxPin0, HIGH);     // default fx pin state, no sound
  digitalWrite(fxPin1, HIGH);     // default fx pin state, no sound
}

void motion(){
  pirState = HIGH;        // motion is detected
  toggle = !toggle;       // toggle the toggle
}
