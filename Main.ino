#include <WiFi.h>

// ======== Wi-Fi Credentials ========
const char* ssid = "ssid";
const char* password = "password";

// ======== GPIO Setup ========
const int lampPin = 5; 
bool lampState = false; 

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(lampPin, OUTPUT);
  digitalWrite(lampPin, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  if (request.indexOf("/toggle") != -1) {
    lampState = !lampState;
    digitalWrite(lampPin, lampState ? HIGH : LOW);
  }

  // ======== HTML ========
  String html =
"<!DOCTYPE html>"
"<html lang='pt-BR'>"
"<head>"
"<meta charset='UTF-8'>"
"<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
"<title>Controle de Lâmpada ESP32</title>"
"<link href='https://fonts.googleapis.com/css2?family=Roboto:wght@700&display=swap' rel='stylesheet'>"
"<style>"
"body {margin:0;padding:0;font-family:'Roboto',sans-serif;font-weight:700;background:linear-gradient(145deg,#1e293b,#0f172a);height:100vh;display:flex;flex-direction:column;justify-content:center;align-items:center;color:#fff;}"
"h1 {font-size:2em;margin-bottom:40px;text-align:center;}"
".switch {position:relative;width:60px;height:120px;background:#555;border-radius:50px;cursor:pointer;transition:background 0.3s ease;box-shadow:inset -4px -4px 10px rgba(0,0,0,0.3),inset 4px 4px 10px rgba(255,255,255,0.05);}"
".switch::before {content:'';position:absolute;top:6px;left:6px;width:48px;height:48px;background:#ccc;border-radius:50%;transition:all 0.3s ease;box-shadow:0 4px 10px rgba(0,0,0,0.3);}"
".switch.on {background:#4ade80;box-shadow:0 0 20px rgba(74,222,128,0.5);}"
".switch.on::before {top:66px;background:#fff;}"
".switch:active::before {transform:scale(0.9);}"
"</style>"
"</head>"
"<body>"
"<h1 id='lamp-status'>" + String(lampState ? "Lâmpada ligada" : "Lâmpada desligada") + "</h1>"
"<form id='lamp-form' action='/toggle' method='GET'>"
"<div id='lamp-switch' class='switch" + String(lampState ? " on" : "") + "'></div>"
"</form>"
"<script>"
"const switchBtn=document.getElementById('lamp-switch');"
"const statusText=document.getElementById('lamp-status');"
"const form=document.getElementById('lamp-form');"
"switchBtn.addEventListener('click',(e)=>{e.preventDefault();switchBtn.classList.toggle('on');"
"if(switchBtn.classList.contains('on')){statusText.textContent='Lâmpada ligada';}else{statusText.textContent='Lâmpada desligada';}"
"form.submit();});"
"</script>"
"</body>"
"</html>";

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.print(html);
  client.println();
}
