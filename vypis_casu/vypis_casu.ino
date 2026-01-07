#include <WiFi.h>
#include <time.h>

const char* ssid       = "wifi_net-cool";
const char* password   = "povina401" ;

// NTP server
const char* ntpServer = "pool.ntp.org";

// GMT +1 (Slovensko) = 3600 sekúnd
const long  gmtOffset_sec = 3600;

// Letný čas = +1 hodina
const int   daylightOffset_sec = 3600;

#define LED_PIN 2

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);




  // Pripojenie na WiFi
  WiFi.begin(ssid, password);
  Serial.print("Pripájam sa na WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi pripojené.");

  // NTP konfigurácia
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // Skúsime načítať čas
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Nepodarilo sa načítať čas z NTP");
    return;
  }

  Serial.println("Aktuálny čas:");
  Serial.println(&timeinfo, "%d.%m.%Y %H:%M:%S");
}

void loop() {
  // Každú sekundu vypíš aktuálny čas
  delay(1000);
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    Serial.println("Aktuálny čas:");
    Serial.println(&timeinfo, "%H:%M:%S");
  }

  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);


}