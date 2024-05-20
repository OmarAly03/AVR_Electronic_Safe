#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

const char* html =
"<!DOCTYPE html>"
"<html>"
"<head>"
"  <title>Electronic Safe</title>"
"  <style>"
"    button {"
"      font-size: 20px;"
"      padding: 10px;"
"    }"
"  </style>"
"</head>"
"<body>"
"  <h1>Electronic Safe</h1>"
"  <button onclick=\"fetch('/unlock')\">Unlock</button>"
"  <button onclick=\"fetch('/lock')\">Lock</button>"
"</body>"
"</html>";

void setup() {
  Serial.begin(9600);
  WiFi.begin("{Your Network SSID}", "{Your Network Password}");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", html);
  });
  server.on("/unlock", []() {
    Serial.write('U');
    server.send(200, "text/plain", "Safe unlocked");
  });
  server.on("/lock", []() {
    Serial.write('L');
    server.send(200, "text/plain", "Safe locked");
  });
  server.begin();
}

void loop() {
  server.handleClient();
}