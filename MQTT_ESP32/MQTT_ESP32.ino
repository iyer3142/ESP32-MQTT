#include <PubSubClient.h>
#include <WiFi.h>                                     // Include the Wi-Fi library

const char* ssid     = "Iyer";                        // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "Aroma@2021";                  // The password of the Wi-Fi network
const char* mqtt_server = "192.31.42.116";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);                               // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);                         // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(500);
    Serial.print('.');
    Serial.println('\n');
    Serial.println("Connection established!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());                     // Send the IP address of the ESP8266 to the computer  
  }

  client.setServer(mqtt_server, 1883);                  //Setup MQTT Client
  
  if (client.connect("espClient", "dave", "9999")) {
  client.publish("test","ESP bola gaand marane ko");
  client.subscribe("test");
  }
}

void reconnect()  {
  while(!client.connected())  {
    Serial.print("/nConnecting to: ");
    Serial.println(mqtt_server);
    if(client.connect("espClient", "dave", "9999")) {
      Serial.print("/nConnected to MQTT: ");
      Serial.println(mqtt_server);
    } else  {
      Serial.println("/nConnection Failed! Trying to reconnect...");
      delay(5000);
    }
  }
}

void loop() { 
  if (!client.connected())  {
    reconnect();
  }
}
