// eeprom_writer.cpp
#include <Arduino.h>
#include <EEPROM.h>

String generateUUID(const String &prefix)
{
  String uuid = prefix;
  for (uint8_t i = 0; i < 8; i++)
  {
    int r = random(16);
    uuid += String(r, HEX);
  }
  uuid.toUpperCase();
  return uuid;
}

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  // Generate UUID-based device ID
  String prefix = "RX"; // Change to "RX" for receiver node
  String deviceId = generateUUID(prefix);

  // Generate random seed
  uint32_t seedValue = random(100000000, 999999999);

  // Store DEVICE_ID as a null-terminated string at address 0
  for (uint8_t i = 0; i < deviceId.length(); i++)
  {
    EEPROM.write(i, deviceId[i]);
  }
  EEPROM.write(deviceId.length(), '\0');

  // Store seed value starting at address 20 (make sure no overlap)
  EEPROM.put(20, seedValue);

  Serial.println("✅ EEPROM write complete.");
  Serial.println("Written DEVICE_ID: " + deviceId);
  Serial.println("Written Seed: " + String(seedValue));
}

void loop()
{
  // Nothing to do
}
