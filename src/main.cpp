#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Decode";
const char* password = "1z2x3c4v";

const int ledPin = 2; 

ESP8266WebServer server(80);

String htmlPage = "<html>\
  <head>\
    <title>LED Control</title>\
    <meta charset='utf-8'>\
  </head>\
  <body>\
    <h1>Керування світлодіодом</h1>\
    <button onclick=\"location.href='/on'\">Ввімкнути</button>\
    <button onclick=\"location.href='/off'\">Вимкнути</button>\
  </body>\
</html>";

void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleLedOn() {
  digitalWrite(ledPin, LOW);  // Світлодіод вмикається на LOW (залежить від плати)
  server.send(200, "text/html", htmlPage);
}

void handleLedOff() {
  digitalWrite(ledPin, HIGH);  
  server.send(200, "text/html", htmlPage);
}

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); 

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleLedOn);
  server.on("/off", handleLedOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
