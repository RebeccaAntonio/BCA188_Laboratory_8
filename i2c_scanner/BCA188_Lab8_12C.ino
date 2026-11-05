#include <Wire.h>
#define I2C_SDA 21
#define I2C_SCL 20

void setup() {
  Serial.begin(115200);
  delay(2000);  // gives the Serial Monitor time to open before the one-time scan
  Wire.begin(I2C_SDA, I2C_SCL);
  int count = 0;
  for (uint8_t addr = 0x01; addr <= 0x7E; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.printf("Found device at 0x%02X\n", addr);
      count++;
    }
  }
  if (count == 0) Serial.println("No I2C devices found");
}

void loop() {}