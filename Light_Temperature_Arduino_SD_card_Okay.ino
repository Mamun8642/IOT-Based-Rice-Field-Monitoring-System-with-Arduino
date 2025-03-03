#include <SPI.h>        // Include SPI library (needed for the SD card)
#include <SD.h>         // Include SD library
#include <DHT.h>        // Include DHT sensor library
#include <BH1750.h>     // Include BH1750 sensor library
#include <waterlevelsensor.h>
#include <Wire.h>

WaterLevelSensor sensor = WaterLevelSensor();
#define SoilMoisturePin A0
#define DHTPIN A1            // DHT22 data pin is connected to Arduino pin A0
#define DHTTYPE DHT22        // DHT22 sensor is used
DHT dht(DHTPIN, DHTTYPE);
    // Initialize DHT library
BH1750 lightMeter;           // Initialize BH1750 library
File dataFile;
bool sdCardInitialized = false;  // Variable to track if SD card is initialized

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB port only

  if (SD.begin()) 
  {
    sdCardInitialized = true;
    Serial.println("SD card initialized successfully.");
  }
  else 
  {
    Serial.println("Failed to initialize SD card!");
  }
  
  delay(2000);
  dht.begin();
  lightMeter.begin();
}

uint16_t line = 1;

void loop() {
  delay(1000);
  // Read humidity
  byte RH = dht.readHumidity();
  // Read temperature in degree Celsius
  byte Temp = dht.readTemperature();
  // Read light intensity in lux
  float light = lightMeter.readLightLevel();
  int Waterlevel = sensor.readPercentage();
  int moisture = analogRead(SoilMoisturePin);

  if (sdCardInitialized) 
  {
    dataFile = SD.open("SensorLog.txt", FILE_WRITE);
  
    // if the file opened okay, write to it:
    if (dataFile) 
    {
      Serial.print(line);
      Serial.print(":    Temperature = ");
      Serial.print(Temp);
      Serial.print("°C,    Humidity = ");
      Serial.print(RH);
      Serial.println("%");

      Serial.print("Light Intensity: ");
      Serial.print(light);
      Serial.println(" lux");

      Serial.print(moisture);
      Serial.print(",");

      Serial.print(Waterlevel);
      Serial.println("mm");

      // Write data to SD card file (SensorLog.txt)
      dataFile.print(line++);
      dataFile.print(":    Temperature = ");
      dataFile.print(Temp);
      dataFile.print("°C,    Humidity = ");
      dataFile.print(RH);
      dataFile.println("%");

      dataFile.print("Light Intensity: ");
      dataFile.print(light);
      dataFile.println(" lux");

      
      Serial.print(moisture);
      Serial.print(",");

      Serial.print(Waterlevel);
      Serial.println("mm");


      dataFile.close();
    }
    // if the file didn't open, print an error:
    else
      Serial.println("Error opening SensorLog.txt");
  }
  else // If SD card is not initialized
  {
    // Print sensor values to serial monitor
    Serial.print("Temperature = ");
    Serial.print(Temp);
    Serial.print("°C,    Humidity = ");
    Serial.print(RH);
    Serial.println("%");
    
    Serial.print("Light Intensity: ");
    Serial.print(light);
    Serial.println(" lux");

    
    Serial.print(moisture);
    Serial.print(",");

    Serial.print(Waterlevel);
    Serial.println("mm");

  }
}
