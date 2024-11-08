#include <DHT.h>
#include <ESP8266WiFi.h>
#include <Losant.h>

#define DHT_SENSOR_PIN  5 // The ESP8266 pin D7 connected to DHT22 sensor
#define DHT_SENSOR_TYPE DHT22
#define PHOTORESISTOR_PIN A0 // The ESP8266 pin A0 connected to photoresistor

const char* WIFI_SSID = "DVC AA (password 12345678)";
const char* WIFI_PASSWORD = "12345678";

const char* LOSANT_DEVICE_ID = "66b65f8a767346f825c179c8";
const char* LOSANT_ACCESS_KEY = "0b3e8b56-34ef-4efc-b1c7-36e05da926d3";
const char* LOSANT_ACCESS_SECRET = "d32926ac936e178f5d521336662ce7b2225bb930c7daab7181d056f4a663a759";

DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

// Losant client instance
WiFiClient wifiClient;
LosantDevice device(LOSANT_DEVICE_ID);

void connectWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");
}

void connectLosant() {
  while (!device.connected()) {
    Serial.println("Connecting to Losant...");
    device.connect(wifiClient, LOSANT_ACCESS_KEY, LOSANT_ACCESS_SECRET);

    if (!device.connected()) {
      Serial.println("Failed to connect to Losant. Retrying in 2 seconds...");
      delay(2000);
    }
  }
  Serial.println("Connected to Losant!");
}

void reconnect() {
  // Check WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Reconnecting...");
    connectWiFi();
  }

  // Check Losant connection
  if (!device.connected()) {
    Serial.println("Losant connection lost. Reconnecting...");
    connectLosant();
  }
}

void setup() {
  Serial.begin(115200);
  dht_sensor.begin(); // initialize the DHT sensor

  connectWiFi();
  connectLosant();
}

void loop() {
  reconnect(); // Ensure WiFi and Losant connections are active

  // read humidity
  float humi  = dht_sensor.readHumidity();
  // read temperature in Celsius
  float temperature_C = dht_sensor.readTemperature();
  // read temperature in Fahrenheit
  float temperature_F = dht_sensor.readTemperature(true);
  // read the value from the photoresistor
  int lightLevel = analogRead(PHOTORESISTOR_PIN);

  // check whether the reading is successful or not
  if (isnan(temperature_C) || isnan(temperature_F) || isnan(humi)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");

    Serial.print("  |  ");

    Serial.print("Temperature: ");
    Serial.print(temperature_C);
    Serial.print("°C  ~  ");
    Serial.print(temperature_F);
    Serial.println("°F");

    Serial.print("Light Level: ");
    Serial.println(lightLevel);

    // Report state to Losant
    StaticJsonDocument<200> jsonBuffer;
    JsonObject root = jsonBuffer.to<JsonObject>();
    root["humidity"] = humi;
    root["tempC"] = temperature_C;
    root["tempF"] = temperature_F;
    root["lightIntensity"] = lightLevel; // Add the light level to the payload

    device.sendState(root);
  }

  device.loop();

  // wait 2 seconds between readings
  delay(2000);
}
