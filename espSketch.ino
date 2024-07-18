#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* pass = "";

const int greenLedPin = 2;
const int redLedPin = 4;

unsigned const long interval = 2000;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("WiFi Connected!");
  // Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() - previousMillis > interval) {
    previousMillis = millis();

    HTTPClient http;
    http.begin("https://32a81089-a19e-4c05-9326-1b3e981cef3b-00-3tj6ftixmct0m.pike.replit.dev/"); 
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {

      if (payload == "No command recorded yet") {
        digitalWrite(greenLedPin, LOW);
        digitalWrite(redLedPin, HIGH);
      } else {
        digitalWrite(greenLedPin, HIGH);
        digitalWrite(redLedPin, LOW);
      }
    } else {
      Serial.print("Error: ");
      Serial.println(httpResponseCode);
      digitalWrite(greenLedPin, LOW);
      digitalWrite(redLedPin, HIGH);
    }

    http.end();
  }
}
