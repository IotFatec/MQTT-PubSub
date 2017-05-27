#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>


// Connect to the WiFi
const char* ssid = "Laboratorio-Projetos";
const char* password = "cadeafaca1";
const char* mqtt_server = "192.168.2.104";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Menssagem recebida!! [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    char receivedChar = (char)payload[i];
    Serial.print(receivedChar);
    if (receivedChar == '0')
      digitalWrite(BUILTIN_LED, HIGH);
    if (receivedChar == '1')
      digitalWrite(BUILTIN_LED, LOW);
  }
  Serial.println();
}


void reconectar() {
  while (!client.connected()) {
    Serial.print("Tentando se conectar ao MQTT...");
    if (client.connect("ESP8266 Client")) {
      Serial.println("conectado");
      client.subscribe("Teste");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentará novamente após 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(BUILTIN_LED, OUTPUT);
}

void loop() {
  if (!client.connected()) {
    reconectar();
  }
  client.loop();
}
