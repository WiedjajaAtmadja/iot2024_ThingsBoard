#include <Arduino.h>
#include <WiFi.h>

#define LED_GREEN 4
#define LED_RED 5
#define DHT_PIN 6
#define SWITCH_PIN 9

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
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
}

void loop() {

}
