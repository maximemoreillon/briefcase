void pinInit()
{
  pinMode(greenLedPin,OUTPUT);
  pinMode(redLedPin,OUTPUT);
  pinMode(lockPin,OUTPUT);
}

void readBattery()
{
  batteryLevel = map(analogRead(batteryPin),0,734,0,11710);
}

