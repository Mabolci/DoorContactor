#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
// Replace the next variables with your SSID/Password combination
const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";
const char* mqtt_username = "MQTT_USERNAME";
const char* mqtt_password = "MQTT_PASSWORD";
// // Add your MQTT Broker IP address, example:
const char* mqtt_server = "MQTT_SERVER_NAME";
// replace with proper port
uint16_t mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

#define MAIN_DOOR_PIN 2

int main_door_state_changed;

void IRAM_ATTR main_door_int(){
  main_door_state_changed=1;
}

void setup() {

  pinMode(MAIN_DOOR_PIN, INPUT_PULLUP);
  attachInterrupt(MAIN_DOOR_PIN, main_door_int, CHANGE);

  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  main_door_state_changed = 1;
}

void setup_wifi() {
  delay(10);
  WiFi.mode(WIFI_STA);
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connection failed with status: ");
    Serial.println(WiFi.status());
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("CLIENT_NAME", mqtt_username, mqtt_password)) {
      Serial.print("connected with ");
      Serial.print(mqtt_username);
      Serial.println("!");
      delay(1000);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds...");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  //Serial.print("dupa\n");
  delay(2000);
  static char buffer[70];
  if (!client.connected()) {
   reconnect();
  }
  if(main_door_state_changed){
   main_door_state_changed = 0;
   sprintf(buffer,"{  \"idx\" : 1,  \"nvalue\" : %i,  \"svalue\" : \"0\" }" , digitalRead(MAIN_DOOR_PIN));
   client.publish("domoticz/in", buffer);
   Serial.print("Value on a pin changed to: ");
   Serial.println(String(!digitalRead(MAIN_DOOR_PIN)).c_str());
  }
  client.loop();
}