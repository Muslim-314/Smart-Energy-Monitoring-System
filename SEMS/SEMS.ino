#include "thingProperties.h"
#include "EmonLib.h"
#define VOLT_CAL 97.837
#define CURRENT_CAL 0.567
EnergyMonitor emon1; // Create an instance
unsigned long lastmillis = millis();
void setup() {
  Serial.begin(9600); // Initialize serial and wait for port to open:
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  emon1.current(34, CURRENT_CAL);       // Current: input pin, calibration.
  emon1.voltage(35, VOLT_CAL, 1.7);
}
void loop() {
  ArduinoCloud.update();
  emon1.calcVI(20, 2000);        // Calculate all. No.of half wavelengths (crossings), time-out
  float currentDraw = emon1.Irms;//extract Irms into Variable
  float voltagedraw = emon1.Vrms;
  float apparentPower = emon1.apparentPower;
  kWh = kWh + apparentPower * (millis() - lastmillis) / 3600000000.0;
  Serial.print("Current:");    Serial.print(currentDraw);
  Serial.print("  Voltage:");  Serial.print(voltagedraw);
  Serial.print("  apparentPower:"); Serial.print(apparentpower);
  Serial.print("  kWh:"); Serial.println(kWh);
  lastmillis = millis();
  current = currentDraw;
  voltage = voltagedraw;
  apparentpower = apparentPower;   kWh = kWh;
}
