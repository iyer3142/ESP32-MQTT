#include <PubSubClient.h>                               //MQTT Library
#include <WiFi.h>                                       // Include the Wi-Fi library
int ALRM=2;
int D1=13;
int D2=12;
int D3=14;
int D4=27;
int D5=26;
int D6=25;
int D7=33;
int D8=32;
int D9=35;
int D10=34;
int D11=21;
bool state[11];
bool alrmTrig = 1;

//------------------------------------------WI-FI NETWORK CONFIG---------------------------------------------//

        const char* ssid     =    "Iyer";
        const char* password =    "Aroma@2021";
        // it wil set the static IP address 
        IPAddress local_IP(192, 31, 42, 4);
        //it wil set the gateway static IP address
        IPAddress gateway(192, 31, 42, 1);
        IPAddress subnet(255, 255, 255, 0);
        IPAddress primaryDNS(0, 0, 0, 0); 
        IPAddress secondaryDNS(0, 0, 0, 0);


//------------------------------------------MQTT BROKER CONFIG---------------------------------------------//
const char* mqtt_server = "192.31.42.3";               // IPV4 of MQTT Broker

                        //    MQTT-Broker terminal command for Linux systems:
                        //    mosquitto_sub -t "topic" -u "username" -P "password"

//------------------------------------ESTABLISHING WI-FI CONNECTION---------------------------------------//
WiFiClient espClient;

//------------------------------------ESTABLISHING MQTT CLIENT---------------------------------------//
PubSubClient client(espClient);

//------------------------------------SETUP FUNCTION---------------------------------------//

void setup() {
  pinMode(ALRM,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
  pinMode(D9,OUTPUT);
  pinMode(D10,OUTPUT);
  pinMode(D11,OUTPUT);
  
  for (int i=0; i<21; i++) {
  state[i] = 0;                                                           // Set all appliances to OFF at initialization
  }

  Serial.begin(115200);                                                   // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
 
  WiFi.begin(ssid, password);                                             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {                                // Wait for the Wi-Fi to connect
    delay(500);
    Serial.print('.');
    Serial.println('\n');
    Serial.println("Connection established!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());                                       // Send the IP address of the ESP32 to the computer  
  }

  client.setServer(mqtt_server, 1883);                                    //Setup MQTT Client
  
  
  Serial.println("\n\nConnecting to MQTT...");                            //Connecting to MQTT
  client.connect("espClient");
  Serial.print("Connection established with MQTT Server to IP:\t");
  Serial.print(mqtt_server);
  client.subscribe("toESP");                                              // Topic for sending messages from Broker to ESP
  client.subscribe("fromESP");                                            // Topic for sending messages from ESP to broker
  Serial.println("\nMQTT State: ");
  Serial.print(client.state());
  client.publish("fromESP", "ESP Handshake!");                            // Testing communication by Publishing a message
  client.setCallback(callback);                                           // Function call - to display stuff        
  
  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,HIGH);
  digitalWrite(D5,HIGH);
  digitalWrite(D6,HIGH);
  digitalWrite(D7,HIGH);
  digitalWrite(D8,HIGH);
  digitalWrite(D9,HIGH);
  digitalWrite(D10,HIGH);
  digitalWrite(D11,HIGH);
}

//------------------------------------reconnect() for MQTT connection failure---------------------------------------//

void reconnect()  {
  while(!client.connected())  {
    Serial.print("\nConnecting to: ");
    Serial.println(mqtt_server);
    if(client.connect("espClient")) {
      Serial.print("\nConnection established with MQTT Server to IP:\t");
      Serial.println(mqtt_server);
    } else  {
      Serial.println("/nConnection Failed! Trying to reconnect...");
      delay(5000);
    }
  }
}

//------------------------------------callback() for MQTT to display stuff---------------------------------------//

void callback(char* topic, byte *payload, unsigned int length) {
  Serial.print("\n\nMessage sent [");
  Serial.print(topic);
  Serial.print("] : ");
  
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }

  if (!strncmp((char *)payload, "D1", length)) {                                        // D1
    client.publish("toESP", "\nRequesing ESP to toggle: D1");
    client.publish("fromESP", "\nRequest received to toggle: D1");
    for (int i=0; i<21; i++) {
      if (state[1] == 0) {
        digitalWrite(D1, LOW);
        client.publish("fromESP", "\nState Change from HIGH to LOW");
        state[1] = 1;  
      }
      else {
        digitalWrite(D1, HIGH);
        client.publish("fromESP","\nState Change from LOW to HIGH");
        state[1] = 0;
      } break;
    }   
    client.publish("fromESP", "\nToggle request satisfied: D1");  
  }

  else if (!strncmp((char *)payload, "D2", length)) {                                    // D2
    client.publish("toESP", "\nRequesing ESP to toggle: D2");
    client.publish("fromESP", "\nRequest received to toggle: D2");
    for (int i=0; i<21; i++) {
      if (state[2] == 0) {
        digitalWrite(D2, LOW);
        client.publish("fromESP", "\nState Change from HIGH to LOW");
        state[2] = 1;  
      }
      else {
        digitalWrite(D2, HIGH);
        client.publish("fromESP","\nState Change from LOW to HIGH");
        state[2] = 0;
      } break;
    } 
      client.publish("fromESP", "\nToggle request satisfied: D2");
  }

  else if (!strncmp((char *)payload, "D3", length)) {                                    // D3
    client.publish("toESP", "\nRequesing ESP to toggle: D3");
    client.publish("fromESP", "\nRequest received to toggle: D3");
    for (int i=0; i<21; i++) {
      if (state[3] == 0) {
        digitalWrite(D3, LOW);
        client.publish("fromESP", "\nState Change from HIGH to LOW");
        state[3] = 1;  
      }
      else {
        digitalWrite(D3, HIGH);
        client.publish("fromESP","\nState Change from LOW to HIGH");
        state[3] = 0;
      } break;
    } 
    client.publish("fromESP", "\nToggle request satisfied: D3");  
  }

  else if (!strncmp((char *)payload, "D4", length)) {                                    // D4
    client.publish("toESP", "\nRequesing ESP to toggle: D4");
    client.publish("fromESP", "\nRequest received to toggle: D4");
    for (int i=0; i<21; i++) {
      if (state[4] == 0) {
      digitalWrite(D4, LOW);
      client.publish("fromESP", "\nState Change from HIGH to LOW");
      state[4] = 1;  
      }
      else {
        digitalWrite(D4, HIGH);
        client.publish("fromESP","\nState Change from LOW to HIGH");
        state[4] = 0;
      } break;
    } 
    client.publish("fromESP", "\nToggle request satisfied: D4");  
  }

  else if (!strncmp((char *)payload, "D5", length)) {                                    // D5
    client.publish("toESP", "\nRequesing ESP to toggle: D5");
    client.publish("fromESP", "\nRequest received to toggle: D5");
    for (int i=0; i<21; i++) {  
      if (state[5] == 0) {
        digitalWrite(D5, LOW);
        client.publish("fromESP", "\nState Change from HIGH to LOW");
        state[5] = 1;  
      }
      else {
        digitalWrite(D5, HIGH);
        client.publish("fromESP","\nState Change from LOW to HIGH");
        state[5] = 0;
      } break;
    } 
    client.publish("fromESP", "\nToggle request satisfied: D5");  
  }

  else if (!strncmp((char *)payload, "D6", length)) {                                    // D6
    client.publish("toESP", "\nRequesing ESP to toggle: D6");
    client.publish("fromESP", "\nRequest received to toggle: D6");
    for (int i=0; i<21; i++) {
      if (state[6] == 0) {
        digitalWrite(D6, LOW);
        client.publish("fromESP", "\nState Change from HIGH to LOW");
        state[6]=1;  
      }
      else {
        digitalWrite(D6, HIGH);
        client.publish("fromESP","\nState Change from LOW to HIGH");
        state[6]=0;
      } break;
    } 
    client.publish("fromESP", "\nToggle request satisfied: D6");  
  }

  else if (!strncmp((char *)payload, "D7", length)) {                                    // D7
    client.publish("toESP", "\nRequesing ESP to toggle: D7");
    client.publish("fromESP", "\nRequest received to toggle: D7");
    for (int i=0; i<21; i++) {
      if (state[7] == 0) {
        digitalWrite(D7, LOW);
        client.publish("fromESP", "\nState Change from HIGH to LOW");
        state[7] = 1;  
      }
      else {
        digitalWrite(D7, HIGH);
        client.publish("fromESP","\nState Change from LOW to HIGH");
        state[7] = 0;
      } break;
    } 
    client.publish("fromESP", "\nToggle request satisfied: D7");
  }

  else if (!strncmp((char *)payload, "D8", length)) {                                    // D8
    client.publish("toESP", "\nRequesing ESP to toggle: D8");
    client.publish("fromESP", "\nRequest received to toggle: D8");
    for (int i=0; i<21; i++) {
      if (state[8] == 0) {
        digitalWrite(D8, LOW);
        client.publish("fromESP", "\nState Change from HIGH to LOW");
        state[8] = 1;  
      }
      else {
        digitalWrite(D8, HIGH);
        client.publish("fromESP","\nState Change from LOW to HIGH");
        state[8] = 0;
      } break;
    } 
    client.publish("fromESP", "\nToggle request satisfied: D8");  
  }

  else if (!strncmp((char *)payload, "D9", length)) {                                    // D9
    client.publish("toESP", "\nRequesing ESP to toggle: D9");
    client.publish("fromESP", "\nRequest received to toggle: D9");
    for (int i=0; i<21; i++) {
      if (state[9] == 0) {
        digitalWrite(D9, LOW);
        client.publish("fromESP", "\nState Change from HIGH to LOW");
        state[9] = 1;  
      }
      else {
        digitalWrite(D9, HIGH);
        client.publish("fromESP","\nState Change from LOW to HIGH");
        state[9] = 0;
      } break;
    } 
    client.publish("fromESP", "\nToggle request satisfied: D9");  
  }

  else if (!strncmp((char *)payload, "D10", length)) {                                   // D10
    client.publish("toESP", "\nRequesting ESP to toggle: D10");
    client.publish("fromESP", "\nRequest received to toggle: D10");
    for (int i=0; i<21; i++) {
      if (state[10] == 0) {
      digitalWrite(D10, LOW);
      client.publish("fromESP", "\nState Change from HIGH to LOW");
      state[10] = 1;  
      }
      else {
        digitalWrite(D10, HIGH);
        client.publish("fromESP","\nState Change from LOW to HIGH");
        state[10] = 0;
      } break;
    } 
    client.publish("fromESP", "\nToggle request satisfied: D10"); 
  }

  else if (!strncmp((char *)payload, "D11", length)) {                                   // D11
    client.publish("toESP", "\nRequesting ESP to toggle: D11");
    client.publish("fromESP", "\nRequest received to toggle: D11");
    for (int i=0; i<21; i++) {  
      if (state[11] == 0) {
        digitalWrite(D11, LOW);
        client.publish("fromESP", "\nState Change from HIGH to LOW");
        state[11] = 1;  
      }
      else {
        digitalWrite(D11, HIGH);
        client.publish("fromESP","\nState Change from LOW to HIGH");
        state[11] = 0;
      } break;
    } 
    client.publish("fromESP", "\nToggle request satisfied: D11");  
  }
  
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();  
}

//------------------------------------LOOP FUNCTION---------------------------------------//

void loop() { 
  if (!client.connected())  {
    reconnect();
  }
  client.loop();
  if (alrmTrig == 1)  {
    digitalWrite(ALRM, HIGH);
    delay(500);
    digitalWrite(ALRM, LOW);
    delay(500);
  }
}
