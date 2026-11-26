#include <ESP8266WiFi.h>
#include <KiwisIoT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// WiFi Configuration
const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";

// KiwisIoT Configuration
const char* topic = "YOUR_KIWISIOT_TOPIC_ID";

KiwisIoT kiwisiot(ssid, pass, topic);

// Hardware Pins
#define DS18B20_PIN D2
#define LED_PIN D5
#define BUZZER_PIN D6

// Temperature Threshold
const float TEMP_LIMIT = 35.0;

// Data Transmission Interval
const unsigned long SEND_INTERVAL = 5000;

// Sensor Configuration
OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  sensors.begin();

  Serial.println();
  Serial.println("Smart Laboratory Temperature Monitoring");
  Serial.println("Initializing KiwisIoT...");

  kiwisiot.begin();

  Serial.println("System Initialized");
}

void loop() {
  kiwisiot.run();

  if (millis() - previousMillis >= SEND_INTERVAL) {
    previousMillis = millis();

    sensors.requestTemperatures();

    float temperature = sensors.getTempCByIndex(0);

    if (temperature == DEVICE_DISCONNECTED_C) {
      Serial.println("DS18B20 Sensor Error!");

      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);

      return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    int alertStatus = 0;

    // Temperature Alert
    if (temperature >= TEMP_LIMIT) {
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);

      alertStatus = 1;

      Serial.println("HIGH TEMPERATURE ALERT!");
    }
    else {
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);

      alertStatus = 0;

      Serial.println("Temperature Normal");
    }

    // Send Temperature to KiwisIoT
    kiwisiot.send("0", String(temperature, 2));

    // Send Alert Status to KiwisIoT
    kiwisiot.send("1", String(alertStatus));

    Serial.println("Data Sent to KiwisIoT");
    Serial.println("------------------------------");
  }
} 
