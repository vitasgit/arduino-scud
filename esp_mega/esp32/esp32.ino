#include "WiFi.h"

// данные сети Wi-Fi
const char* ssid = "vitaly";
const char* password = "123456";

WiFiServer server(80);  // порт 80

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String request = client.readString();

    if (request.indexOf("GET /?command=1") != -1) {
      Serial.write('1');
      client.println("HTTP/1.1 200 OK");
      client.println();
    } 
    else if (request.indexOf("GET /?command=0") != -1) {
      Serial.write('0');
      client.println("HTTP/1.1 200 OK");
      client.println();
    }

    client.stop();
  }
}
