#include <WiFi.h>

int value = 0;
int valueMap = 0;

WiFiServer server(80);
String header;

unsigned long timeoutTime = 2000;

void setup() {
  Serial.begin(9600);

  pinMode(34, INPUT);
  pinMode(18, OUTPUT);

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
  WiFiClient client = server.available();
  if (!client) return;

  String header = "";
  unsigned long startTime = millis();

  while (client.connected() && millis() - startTime < 500) {
    if (client.available()) {
      char c = client.read();
      header += c;

      if (header.endsWith("\r\n\r\n")) {

        int value = analogRead(34);
        int valueMap = map(value, 0, 4095, 0, 100);

        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();

        client.println("<!DOCTYPE html><html><head>");
        client.println("<meta http-equiv='refresh' content='2'>");
        client.println("</head><body align='center'>");
        client.println("<h1>WEB POTENCIOMETER</h1>");
        client.println("<p>VALUE: <b>" + String(valueMap) + "</b></p>");
        client.println("</body></html>");

        break;
      }
    }
  }

  delay(1);
  client.stop();
}
