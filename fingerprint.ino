void scannerprintInit(){

  scanner.begin(57600);

  if (scanner.verifyPassword()) {
    for(int i=0; i<2; i++) {
      digitalWrite(greenLedPin,HIGH);
      delay(50);
      digitalWrite(greenLedPin,LOW);
      delay(50);
    }
  }
  else {
    while (1){
      digitalWrite(redLedPin,HIGH);
      delay(100);
      digitalWrite(redLedPin,LOW);
      delay(100);
    }
  }
}



void readFingerprint() {
  if (scanner.getImage() == FINGERPRINT_OK){
    if(scanner.image2Tz() == FINGERPRINT_OK) {
      if(scanner.scannerFastSearch() == FINGERPRINT_OK) {
        unlockStartTime = millis();
      }
    }
  }
}
