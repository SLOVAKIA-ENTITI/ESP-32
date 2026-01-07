#include <WiFi.h>

WiFiServer server(80);
String header;

#define LED_PIN 2
// STAV SYSTEMU
String stavSystemu = "deaktivovany";   // deaktivovany / aktivovany

unsigned long currentTime = millis();
const long timeoutTime = 2000;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Spustam system...");

  // WiFi
  WiFi.begin("wifi_net-cool", "povina401");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi pripojene");
  Serial.print("IP adresa: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  handleWiFi();
}

// ================= WIFI =================
void handleWiFi() {
  WiFiClient client = server.available();
  if (!client) return;

  header = "";
  unsigned long startTime = millis();

  while (client.connected() && millis() - startTime <= timeoutTime) {
    if (client.available()) {
      char c = client.read();
      header += c;

      if (c == '\n') {

        // ---- SPRACOVANIE STLAČENIA TLAČIDLA ----
        if (header.indexOf("GET /aktivovat") >= 0) {
          stavSystemu = "aktivovany";
          Serial.println("SYSTEM AKTIVOVANY");
        }

        if (header.indexOf("GET /deaktivovat") >= 0) {
          stavSystemu = "deaktivovany";
          Serial.println("SYSTEM DEAKTIVOVANY");
        }

        // ---- HTTP ODPOVEĎ ----
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();

        client.println("<!DOCTYPE html><html><head>");
        client.println("<meta http-equiv='refresh' content='2'>");
        client.println("<style>");
        client.println("button { padding: 24px 48px; font-size: 18px; }");
        client.println("</style></head><body align='center'>");

        client.println("<h1>Ovladanie systemu</h1>");
        client.println("<p>STAV SYSTEMU: <b>" + stavSystemu + "</b></p>");

        if (stavSystemu == "deaktivovany"){
          client.println("<a href='/aktivovat'><button>AKTIVOVAT</button></a>");
          digitalWrite(LED_PIN, LOW);
        }
        else{
          client.println("<a href='/deaktivovat'><button>DEAKTIVOVAT</button></a>");
          digitalWrite(LED_PIN, HIGH);
        }

        client.println("</body></html>");
        break;
      }
    }
  }

  client.stop();
}
