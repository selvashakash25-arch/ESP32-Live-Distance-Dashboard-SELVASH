#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

WebServer server(80);

#define TRIG_PIN 5
#define ECHO_PIN 18

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0)
    return -1;

  return duration * 0.0343 / 2.0;
}

void handleRoot() {
  float distance = getDistance();

  String html = "<!DOCTYPE html><html><head>";
  html += "<meta http-equiv='refresh' content='1'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>ESP32 Live Distance Dashboard</title>";
  html += "</head><body>";

  html += "<h1>ESP32 Live Distance Dashboard</h1>";

  if (distance >= 0) {
    html += "<h2>Distance: ";
    html += String(distance, 1);
    html += " cm</h2>";
  } else {
    html += "<h2>Distance: No Echo</h2>";
  }

  html += "<p>Page refreshes every 1 second.</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);

  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();

  Serial.println("Web server started");
}

void loop() {
  server.handleClient();

  float distance = getDistance();

  if (distance >= 0) {
    Serial.print("Distance: ");
    Serial.print(distance, 1);
    Serial.println(" cm");
  } else {
    Serial.println("Distance: No Echo");
  }

  delay(1000);
}
