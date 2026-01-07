#include <WiFi.h>

WiFiServer server(80);
String header;

// STAV SYSTEMU
String stavSystemu = "vypnuty";   // vypnuty / zapnuty
int aktivnaLED = 18;              // 18 alebo 19

unsigned long timeoutTime = 2000;

void setup() {
  Serial.begin(9600);

  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);

  digitalWrite(18, LOW);
  digitalWrite(19, LOW);

  Serial.println("Spustam system...");

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

        // ---- SPRACOVANIE POZIADAVIEK ----
        if (header.indexOf("GET /zapnut") >= 0) {
          stavSystemu = "zapnuty";
          digitalWrite(aktivnaLED, HIGH);
          Serial.println("LED ZAPNUTA");
        }

        if (header.indexOf("GET /vypnut") >= 0) {
          stavSystemu = "vypnuty";
          digitalWrite(aktivnaLED, LOW);
          Serial.println("LED VYPNUTA");
        }

        if (header.indexOf("GET /led18") >= 0) {
          aktivnaLED = 18;
          Serial.println("Zvolena LED 18");
        }

        if (header.indexOf("GET /led19") >= 0) {
          aktivnaLED = 19;
          Serial.println("Zvolena LED 19");
        }

        // ---- HTTP ODPOVEĎ ----
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();

        client.println("<!DOCTYPE html><html><head>");
        client.println("<style>");
        client.println("button { padding: 20px 40px; font-size: 18px; margin: 10px; }");
        client.println("</style></head><body align='center'>");

        client.println("<h1>Ovladanie LED</h1>");
        client.println("<p>Aktivna LED: <b>" + String(aktivnaLED) + "</b></p>");
        client.println("<p>Stav: <b>" + stavSystemu + "</b></p>");

        client.println("<a href='/led18'><button>LED 18</button></a>");
        client.println("<a href='/led19'><button>LED 19</button></a><br>");

        client.println("<a href='/zapnut'><button>ZAPNUT</button></a>");
        client.println("<a href='/vypnut'><button>VYPNUT</button></a>");

        client.println("</body></html>");
        break;
      }
    }
  }
  client.stop();
}
