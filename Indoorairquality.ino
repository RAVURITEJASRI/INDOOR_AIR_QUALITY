#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define WIFI_SSID "Varshitha"
#define WIFI_PASS "varshitha"

#define DHTPIN 4
#define DHTTYPE DHT11
#define MQ135_PIN 34
#define BUZZER_PIN 15

DHT dht(DHTPIN, DHTTYPE);

// ThingSpeak details
String writeApiKey = "XVEBCTFTJP8CWRIX";
String readApiKey = "6UW6KIFNBVY4FY72";
String channelID = "3000756";

const char* server = "http://api.thingspeak.com/update";

unsigned long lastPostTime = 0;
unsigned long postInterval = 10000;  // 20 seconds (minimum ThingSpeak limit)
unsigned long lastCheckTime = 0;
unsigned long checkInterval = 15000; // check remote buzzer command every 15 sec

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  unsigned long currentTime = millis();

  // Send data to ThingSpeak every 20 sec
  if (currentTime - lastPostTime >= postInterval) {
    sendSensorData();
    lastPostTime = currentTime;
  }

  // Check remote buzzer control from ThingSpeak every 15 sec
  if (currentTime - lastCheckTime >= checkInterval) {
    checkBuzzerControlFromThingSpeak();
    lastCheckTime = currentTime;
  }
}

void sendSensorData() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int rawValue = analogRead(MQ135_PIN);

  // Normalize air quality from 0–4095 to 0–100
  float air_quality = (rawValue / 4095.0) * 100.0;

  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" °C, Hum: "); Serial.print(hum);
  Serial.print(" %, AQ: "); Serial.println(air_quality);

  // Automatic buzzer trigger if air quality is poor
  if (air_quality > 70) {
    digitalWrite(BUZZER_PIN, HIGH);
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = server;
    url += "?api_key=" + writeApiKey;
    url += "&field1=" + String(temp);
    url += "&field2=" + String(hum);
    url += "&field3=" + String(air_quality,1);

    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.println("Data sent to ThingSpeak.");
    } else {
      Serial.println("Failed to send data.");
    }
    http.end();
  }
}

void checkBuzzerControlFromThingSpeak() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://api.thingspeak.com/channels/" + channelID + "/fields/4/last.txt?api_key=" + readApiKey;

    http.begin(url);
    int httpCode = http.GET();
    if (httpCode == 200) {
      String response = http.getString();
      int buzzerControl = response.toInt();
      Serial.println("Remote Buzzer Control Value: " + String(buzzerControl));

      if (buzzerControl == 1) {
        digitalWrite(BUZZER_PIN, HIGH);
      } else if (buzzerControl == 0) {
        digitalWrite(BUZZER_PIN, LOW);
      }
    } else {
      Serial.println("Error getting Field 4 value.");
    }
    http.end();
  }
}
