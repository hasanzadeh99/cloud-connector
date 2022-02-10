
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h>

WiFiManager wifiManager;

const char* mqttServer = "****";
const int mqttPort = 0000;
const char* mqttUser = "****";
const char* mqttPassword = "****";
char data;
char a;
char ssid_get_from_user[20];
char password_get_from_user[20];


const int BUFFER_SIZE = 100;
char buf[BUFFER_SIZE];

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  Serial.println("\n");
  Serial.println("\n");
  Serial.println("\n");
  Serial.println("\n");
  delay(1000);
  Serial.println("Hello, We are IMP group ... ");
  Serial.println("We strive for a better life ....");
  Serial.println("Welcome");

  wifiManager.autoConnect("cloud connector");

  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }

  client.publish("easyconnect/bc461/data/th", "'temperature':33.33C 'humidity':33RH", true); //Topic name
  client.subscribe("easyconnect/bc461/data/th");

  Serial.println("Please enter your text to publish ...");


}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  Serial.println("-----------------------");

}

void loop() {
  client.loop();

  // check if data is available
  if (Serial.available() > 0) {
    // read the incoming bytes:
    int rlen = Serial.readBytesUntil('\n', buf, BUFFER_SIZE);

    // prints the received data
    Serial.print("I received: ");
    
    for (int i = 0; i < rlen; i++) Serial.print(buf[i]);
    // a=buf[0];

    client.publish("easyconnect/bc461/data/th", &buf[0], true);
  }

}
