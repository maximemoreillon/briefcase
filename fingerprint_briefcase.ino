#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

// Pin mapping
#define redLedPin 5
#define greenLedPin 6
#define lockPin 12
#define batteryPin A0

// parameters
#define UNLOCKTIME 3000 // [ms]
#define LOWBAT 9600 //  [mV] low battery threshold
#define FINGERPRINTPERIOD 100 // [ms]

SoftwareSerial scannerSerial(2, 3); // 2: Green, 3: White
Adafruit_Fingerprint scanner = Adafruit_Fingerprint(&scannerSerial);

long unlockStartTime, lastReadTime; // [ms]
int batteryLevel; // [mV]

void setup() {
  pinInit();
  bluetoothInit();
  scannerprintInit();
  unlockStartTime = -UNLOCKTIME;
  lastReadTime = -FINGERPRINTPERIOD;
}

void loop() {
  
  // Reading Fingerprint reader
  if(millis()-lastReadTime > FINGERPRINTPERIOD) {
    lastReadTime = millis();
    readFingerprint();
  }

  // Reading bluetooth
  readBluetooth();

  // Reading battery level
  readBattery();

  // Lock and LEDs management
  if(millis() - unlockStartTime < UNLOCKTIME) {

    // Unlocked    
    digitalWrite(greenLedPin,HIGH);
    digitalWrite(redLedPin,LOW);
    digitalWrite(lockPin,HIGH);
  }
  else {
    
    // Locked
    digitalWrite(greenLedPin,LOW);
    digitalWrite(lockPin,LOW);

    // Blink red LED when battery is low
    if(batteryLevel<LOWBAT && (millis()/500)%2) digitalWrite(redLedPin,LOW); // Blink red LED if low battery
    else digitalWrite(redLedPin,HIGH); // Otherwise 
  }
}
