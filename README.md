
# 🌡️ Smart Laboratory Temperature Monitoring System Using IoT

## 📌 Project Overview

The **Smart Laboratory Temperature Monitoring System** is an IoT-based project designed to monitor laboratory temperature in real time using a DS18B20 temperature sensor and NodeMCU ESP8266.

The system collects temperature readings and transmits them to the **KiwisIoT platform** through Wi-Fi. Users can monitor the temperature remotely using an IoT dashboard.

When the temperature reaches or exceeds a predefined threshold, an LED and buzzer are activated to provide a local alert. This project offers a simple and cost-effective solution for laboratory temperature monitoring.

---

## 🎯 Objectives

- Monitor laboratory temperature in real time.
- Measure temperature using the DS18B20 sensor.
- Transmit temperature data to the KiwisIoT platform.
- Display temperature readings through an IoT dashboard.
- Activate an LED and buzzer during high-temperature conditions.
- Enable remote temperature monitoring through Wi-Fi.

---

## 🛠️ Components Required

| S.No | Component Name | Quantity |
|---|---|---|
| 1 | NodeMCU ESP8266 | 1 |
| 2 | DS18B20 Temperature Sensor | 1 |
| 3 | LED | 1 |
| 4 | Buzzer | 1 |
| 5 | 4.7KΩ Resistor | 1 |
| 6 | 220Ω Resistor | 1 |
| 7 | Jumper Wires | As required |
| 8 | USB Cable | 1 |

---

## 🔌 Hardware Connections

### DS18B20 Temperature Sensor

| DS18B20 Pin | NodeMCU Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DATA | D2 (GPIO4) |

A **4.7KΩ pull-up resistor** must be connected between the DATA pin and 3.3V.

### LED Connection

| LED Pin | NodeMCU Pin |
|---|---|
| Anode (+) | D5 (GPIO14) through 220Ω resistor |
| Cathode (-) | GND |

### Buzzer Connection

| Buzzer Pin | NodeMCU Pin |
|---|---|
| Positive (+) | D6 (GPIO12) |
| Negative (-) | GND |

---

## 📷 Circuit Diagram

Upload your circuit diagram to the repository and add it here.

```markdown
![Circuit Diagram](images/circuit-diagram.png)
```

---

## 💻 Software Requirements

- Arduino IDE
- ESP8266 Board Package
- KiwisIoT Arduino Library
- OneWire Library
- DallasTemperature Library

---

## 📚 Libraries Required

Install the following libraries in Arduino IDE:

- `KiwisIoT`
- `OneWire`
- `DallasTemperature`

### KiwisIoT Library

GitHub Repository:

https://github.com/Kiwistron/KiwisIoT

---

## ⚙️ Arduino IDE Setup

### Step 1: Install Arduino IDE

Download Arduino IDE:

https://www.arduino.cc/en/software

### Step 2: Install ESP8266 Board Package

Add the following URL to the Additional Boards Manager URLs section:

```text
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```

1. Open Arduino IDE.
2. Go to Preferences or Settings.
3. Add the ESP8266 Board Manager URL.
4. Open Boards Manager.
5. Search for ESP8266.
6. Install the ESP8266 board package.

### Step 3: Select the Board

Select the following board:

**NodeMCU 1.0 (ESP-12E Module)**

### Step 4: Install Libraries

Open Library Manager and install:

- OneWire
- DallasTemperature

Install the KiwisIoT library using the official repository instructions.

---

## ☁️ KiwisIoT Platform Setup

1. Log in to the KiwisIoT platform.
2. Create a new panel.
3. Name the panel **Smart Laboratory Temperature Monitoring**.
4. Configure the required Topic ID.
5. Create the temperature monitoring widgets.
6. Configure the temperature channel.
7. Configure the alert status channel.

### Dashboard Channel Configuration

| Channel ID | Data | Description |
|---|---|---|
| 0 | Temperature | Displays live temperature readings |
| 1 | Alert Status | Displays the alert condition |

### Recommended Widgets

| Widget | Purpose |
|---|---|
| Temperature Gauge | Displays current temperature |
| Temperature Line Chart | Displays temperature history |
| Alert Indicator | Displays alert status |

---

## 🚀 Step-by-Step Procedure

1. Connect the DS18B20 temperature sensor to the NodeMCU ESP8266.
2. Connect a 4.7KΩ pull-up resistor between the DATA pin and 3.3V.
3. Connect the LED to D5 through a 220Ω resistor.
4. Connect the buzzer to D6 and GND.
5. Connect all the components using jumper wires.
6. Install Arduino IDE on your computer.
7. Install the ESP8266 board package.
8. Install the KiwisIoT, OneWire and DallasTemperature libraries.
9. Create a dashboard on KiwisIoT and configure the required channels.
10. Write and configure the Arduino code with Wi-Fi credentials and Topic ID.
11. Upload the code to NodeMCU.
12. Monitor temperature readings and verify the alerts on the KiwisIoT dashboard.

---

## 🧠 Working Principle

1. The DS18B20 temperature sensor measures the laboratory temperature.
2. The NodeMCU ESP8266 reads the temperature data from the sensor.
3. The NodeMCU processes the temperature reading.
4. The temperature data is transmitted to KiwisIoT through Wi-Fi.
5. The KiwisIoT dashboard displays the temperature in real time.
6. The system compares the temperature with a predefined threshold.
7. When the temperature reaches or exceeds the threshold, the LED and buzzer are activated.
8. The alert status is transmitted to the KiwisIoT dashboard.

---

## 🌡️ Temperature Alert System

The default temperature threshold is **35°C**.

| Temperature Condition | LED | Buzzer | Alert Status |
|---|---|---|---|
| Below 35°C | OFF | OFF | 0 - Normal |
| 35°C or Above | ON | ON | 1 - Alert |

The temperature threshold can be modified in the Arduino code.

---

## 📜 Arduino Code

```cpp
#include <ESP8266WiFi.h>
#include <KiwisIoT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Wi-Fi Configuration
const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";

// KiwisIoT Configuration
const char* topic = "YOUR_KIWISIOT_TOPIC_ID";

KiwisIoT kiwisiot(ssid, pass, topic);

// Hardware Connections
#define DS18B20_PIN D2
#define LED_PIN D5
#define BUZZER_PIN D6

// Temperature Threshold
const float TEMP_LIMIT = 35.0;

// Data Transmission Interval
const unsigned long SEND_INTERVAL = 5000;

// DS18B20 Configuration
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
```

---

## 🔧 Code Configuration

### Wi-Fi Configuration

Replace the placeholders with your Wi-Fi credentials:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";
```

### KiwisIoT Configuration

Replace the placeholder with the Topic ID configured on your platform:

```cpp
const char* topic = "YOUR_KIWISIOT_TOPIC_ID";
```

### Temperature Threshold

```cpp
const float TEMP_LIMIT = 35.0;
```

The default threshold is 35°C. The LED and buzzer activate when the temperature reaches or exceeds this value.

---

## 📤 Uploading the Code

1. Connect NodeMCU to your computer using a USB cable.
2. Open Arduino IDE.
3. Select NodeMCU 1.0 (ESP-12E Module).
4. Select the correct COM port.
5. Paste the Arduino code.
6. Enter Wi-Fi credentials.
7. Enter your KiwisIoT Topic ID.
8. Click Verify to compile the code.
9. Click Upload.
10. Open Serial Monitor.
11. Set the baud rate to 115200.

---

## 📊 KiwisIoT Monitoring

### Channel 0 - Temperature

The temperature data is sent to Channel 0.

Example:

```text
29.50
```

Use this channel for:

- Temperature Gauge
- Temperature Line Chart

### Channel 1 - Alert Status

| Value | Meaning |
|---|---|
| 0 | Normal |
| 1 | High Temperature Alert |

Use Channel 1 for an alert indicator widget.

---

## 🧪 Testing Procedure

### Temperature Sensor Testing

- Power on the NodeMCU.
- Open the Serial Monitor.
- Check the temperature readings.
- Verify that the readings change when the temperature changes.

### Dashboard Testing

- Open the KiwisIoT dashboard.
- Check the Temperature Gauge.
- Check the Temperature History Chart.
- Verify that data is received.

### LED Testing

- Perform a controlled temperature increase.
- Verify that the LED activates when the threshold is reached.

### Buzzer Testing

- Verify that the buzzer activates during the alert condition.
- Verify that the buzzer turns OFF when the temperature falls below the threshold.

### Alert Status Testing

- Check the Alert Indicator on KiwisIoT.
- Verify that the status changes from 0 to 1 during the alert condition.

---

## 📈 Expected Results

- Real-time temperature monitoring.
- Temperature data displayed on the KiwisIoT platform.
- Temperature history visualization.
- LED activation during high-temperature conditions.
- Buzzer activation during high-temperature conditions.
- Remote monitoring through an IoT dashboard.

---

## 🏫 Applications

- Electronics Laboratories
- Computer Laboratories
- Research Laboratories
- Equipment Storage Rooms
- Educational Institutions
- Server Rooms
- Environmental Monitoring

---

## 🔮 Future Enhancements

- Add multiple temperature sensors.
- Implement automatic fan control.
- Add mobile notifications.
- Implement email alerts.
- Store historical temperature data for analysis.
- Add battery backup.
- Integrate humidity monitoring.

---

## 📝 Conclusion

The Smart Laboratory Temperature Monitoring System provides an IoT-based solution for monitoring laboratory temperature in real time. Using the DS18B20 temperature sensor and NodeMCU ESP8266, the system collects temperature readings and transmits them to the KiwisIoT platform through Wi-Fi.

The dashboard enables remote monitoring, while the LED and buzzer provide local alerts during high-temperature conditions. This project demonstrates the integration of sensor technology, microcontrollers, Wi-Fi connectivity and cloud-based IoT monitoring for laboratory environmental monitoring.

---

## 🧰 Technologies Used

- **Hardware:** NodeMCU ESP8266, DS18B20, LED, Buzzer
- **Programming:** Arduino C++
- **IoT Platform:** KiwisIoT
- **Communication:** Wi-Fi
- **Libraries:** KiwisIoT, OneWire, DallasTemperature

---

## 📌 Project Information

| Category | Details |
|---|---|
| Project Name | Smart Laboratory Temperature Monitoring System |
| Controller | NodeMCU ESP8266 |
| Sensor | DS18B20 |
| IoT Platform | KiwisIoT |
| Alert Components | LED and Buzzer |
| Communication | Wi-Fi |
| Programming Language | Arduino C++ |
| Project Type | IoT / Environmental Monitoring |

---

⭐ **Smart Laboratory Temperature Monitoring System Using NodeMCU ESP8266 and KiwisIoT**


