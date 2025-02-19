#define BLYNK_TEMPLATE_ID "TMPL68eTyOR2x"
#define BLYNK_TEMPLATE_NAME "New Project"
#define BLYNK_AUTH_TOKEN "tNjHavWxLJ_dMv1LUyKkzBv5NgzeHQYN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <BH1750.h>

BH1750 lightMeter;
DHT dht(26, DHT22);

char auth[] = "tNjHavWxLJ_dMv1LUyKkzBv5NgzeHQYN";
char ssid[] = "K@H";
char pass[] = "*******";

BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float light = lightMeter.readLightLevel();
  int l = map(light, 0, 6550, 0, 100);
  
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, l);

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" Humidity: ");
  Serial.println(h);
 
  Serial.print("Light Intensity: ");
  Serial.print(l);
  Serial.println(" %");
  
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  Wire.begin();
  lightMeter.begin();
  timer.setInterval(100L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
