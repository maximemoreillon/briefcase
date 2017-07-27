void bluetoothInit()
{
  Serial.begin(9600);
}

void readBluetooth()
{
  if(Serial.available() > 0)
  {
    String message = Serial.readStringUntil('\n');
    if(message == "help") displayHelp();
    else if(message == "unlock")
    {
      Serial.println("Unlocking briefcase...");
      unlockStartTime = millis();
    }
    else if(message == "battery") displayBatteryV();
    else if(message == "adc") displayAdc();
    else displayError(message);
  }
}

void displayHelp()
{
  Serial.println("Fingerprint reader briefcase");
  Serial.println("Maxime MOREILLON");
  Serial.println("Firmware version: 7.0");
  Serial.println("Commands:");
  Serial.println("\"unlock\" : unlocks briefcase");
  Serial.println("\"battery\" : displays battery level");
  Serial.println("\"adc\" : displays battery adc raw value");
  Serial.println("\"help\" : displays this message");
}

void displayBatteryV()
{
  String message = "";
  message += "Battery level: ";
  message += double(batteryLevel/1000.00);
  message += " V";
  Serial.println(message);
}

void displayAdc()
{
  String message = "";
  message += "Battery ADC reading: ";
  message += analogRead(batteryPin);
  Serial.println(message);
}

void displayError(String command)
{
    String message = "Invalid command: \"";
  message += command;
  message += "\"";
  Serial.println(message);
}

