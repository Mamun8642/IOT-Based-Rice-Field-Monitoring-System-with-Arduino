#define SoilMoisturePin 15
#include <WiFi.h>
#include <DHT.h>
#include <BH1750.h>

BH1750 lightMeter;
DHT dht(26, DHT22);

void setup() {
  Serial.begin(115200);
  dht.begin();
  Wire.begin();
  lightMeter.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float l = lightMeter.readLightLevel();
  int moisture = getSoilMoisture();

  if (!isnan(h) && !isnan(t) && moisture != -1) {
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" Humidity: ");
    Serial.println(h);
    Serial.print("Light Intensity: ");
    Serial.print(l);
    Serial.println(" lx");
    Serial.print("Soil Moisture: ");
    Serial.print(moisture);
    Serial.println("%");
  } else {
    Serial.println("Failed to read from sensors!");
  }

  delay(1000);
}

int getSoilMoisture() {
  int moisture = analogRead(SoilMoisturePin);
  if (moisture == -1) {
    Serial.println("Failed to read soil moisture!");
    return -1;
  }
  moisture = map(moisture, 95, 4000, 0, 100); // Adjust the mapping according to your sensor
  return moisture;
}
