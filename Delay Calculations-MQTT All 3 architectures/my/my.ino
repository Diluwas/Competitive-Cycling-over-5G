#include <SPIFFS.h>

void setup() {
  Serial.begin(115200);
  delay(2000);

  if (!SPIFFS.begin(true)) {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }

  File file = SPIFFS.open("G:\FYP\Delay Calculations\my\output.txt", "a");
  if (!file) {
    Serial.println("Failed to create file");
    return;
  }

  while (Serial.available()) {
    char c = Serial.read();
    file.write(c);
  }

  file.close();
  Serial.println("Output saved to file");
}

void loop() {
  Serial.println("hi");
  delay(5000);
}
