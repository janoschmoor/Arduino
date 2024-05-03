#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Create an ESP8266WebServer object on port 80
ESP8266WebServer server(80);
// const char* ssid = "iPhone von Janosch";
// const char* password = "eifach123";
const char* ssid = "yallo_09591D";
const char* password = "8gCrydC744r8wu34";

const int ledPin = 5; // D1 pin on ESP8266 (GPIO5)

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
  // Connect to WiFi
  connectToWiFi();

  // Start the web server
  startWebServer();
}

void loop() {
  
  server.handleClient();
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to WiFi!");
  Serial.print("Local IP address: ");
  Serial.println(WiFi.localIP());
}

void startWebServer() {
  // Route for root URL
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", "<html><body><h1>Toggle LED</h1><form action='/toggle' method='POST'><button type='submit'>Toggle LED</button></form></body></html>");
  });

  // Route for toggling LED
  server.on("/toggle", HTTP_POST, []() {
    digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle LED state
    server.send(200, "text/plain", "LED toggled"); // Send response
  });

  // Start the server
  server.begin();
  Serial.println("Web server started");
}

