/*
Test Thingsboard device: 
  curl -v -X POST http://demo.thingsboard.io/api/v1/tic0iv4wh04e1bqwpxn3/telemetry --header Content-Type:application/json --data "{temperature:25}"
Public dashboard: 
  https://demo.thingsboard.io/dashboard/e9387d10-b3c4-11ef-b5a8-ed1aed9a651f?publicId=ae632450-214f-11ee-9079-75f587c23e37
*/
#include <Arduino.h>
#include <WiFi.h>
#include "ThingsBoard.h"
#include "DHTesp.h"

#define LED_GREEN 4
#define LED_RED 5
#define DHT_PIN 6
#define SWITCH_PIN 9

#define THINGSBOARD_SERVER "demo.thingsboard.io"
#define THINGSBOARD_ACCESS_TOKEN "tic0iv4wh04e1bqwpxn3"
DHTesp dht;
WiFiClient espClient;
ThingsBoard tb(espClient);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  dht.setup(DHT_PIN, DHTesp::DHT22);
  Serial.println("Booting...");
  WiFi.mode(WIFI_STA);
  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.print("System connected with IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("RSSI: %d\n", WiFi.RSSI());

  if (tb.connect(THINGSBOARD_SERVER, THINGSBOARD_ACCESS_TOKEN)) {
    Serial.println("Connected to ThingsBoard");
  } else {
    Serial.println("Failed to connect to ThingsBoard");
  }
}

long nCurrentMillis = 0;
void loop() {
  if (millis() - nCurrentMillis > 3000)
  {
    nCurrentMillis = millis();
    float fTemperature = dht.getTemperature();
    float fHumidity = dht.getHumidity();
    Serial.printf("Temperature: %.2f\r\n", fTemperature);
    Serial.printf("Humidity: %.2f\r\n", fHumidity);
    if (tb.connected())
    {
      tb.sendTelemetryFloat("temperature", fTemperature);
      tb.sendTelemetryFloat("humidity", fHumidity);
    }
  }
  tb.loop();
}
