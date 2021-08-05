#include <Arduino.h>
#include <VofaPlus.h>

VofaPlus logger;

void setup() {
  Serial.begin(115200);
  logger.mode(VofaPlus::JUSTFLOAT);
}

int f = 0;
void loop() {
  f++;
  logger.writeSamples("test",f,sin((float)f/90*PI),1.0f);
  if (f >= 360)
    f = 0;
  delay(30);
}
