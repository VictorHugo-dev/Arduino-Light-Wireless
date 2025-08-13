#include <WiFi.h>

// ======== Wi-Fi Credentials ========
const char* ssid = "Victor Hugo";
const char* password = "12345678";

// ======== GPIO Setup ========
const int lampPin = 5; // GPIO connected to transistor base resistor
bool lampState = false; // false = off, true = on

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(lampPin, OUTPUT);
  digitalWrite(lampPin, LOW);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  // Toggle request
  if (request.indexOf("/toggle") != -1) {
    lampState = !lampState;
    digitalWrite(lampPin, lampState ? HIGH : LOW);
  }

  // ======== HTML with Modern Styling ========
  String html = 
    "<!DOCTYPE html><html lang='en'>"
    "<head>"
    "<meta charset='UTF-8'>"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "<title>Lampada Wireless</title>"
    "<style>"
    "body {"
    "  margin:0; padding:0; font-family:Arial, sans-serif;"
    "  background:linear-gradient(135deg, #2c3e50, #4ca1af);"
    "  height:100vh; display:flex; justify-content:center; align-items:center;"
    "  color:white;"
    "}"
    ".container { text-align:center; }"
    "h1 { font-size:2.5em; margin-bottom:30px; }"
    ".button {"
    "  padding:20px 60px; font-size:1.5em; border:none; border-radius:50px;"
    "  background:" + String(lampState ? "#e74c3c" : "#2ecc71") + ";"
    "  color:white; cursor:pointer; box-shadow:0 4px 15px rgba(0,0,0,0.3);"
    "  transition: all 0.3s ease;"
    "}"
    ".button:hover { transform:scale(1.05); opacity:0.9; }"
    "</style>"
    "</head>"
    "<body>"
    "<div class='container'>"
    "<h1>Lampada está " + String(lampState ? "Ligada" : "Desligada") + "</h1>"
    "<form action='/toggle' method='GET'>"
    "<button class='button'>" + String(lampState ? "Desligar" : "Ligar") + "</button>"
    "</form>"
    "</div>"
    "</body></html>";

  // Send HTTP response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.print(html);
  client.println();
}
