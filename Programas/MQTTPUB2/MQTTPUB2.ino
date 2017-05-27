#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

 
// Connect to the WiFi
const char* ssid = "ROSANNA-JEFFERSON";
const char* password = "DCPJMF050916";
const char* mqtt_server = "192.168.31.21";
const int button = D2;
int button_state = 0;
 
WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void reconectar() {
 while (!client.connected()) {
 Serial.print("Tentando se conectar ao MQTT...");
 if (client.connect("ESP8266 Client4")) {
  Serial.println("conectado");
  
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
 setup_wifi();
 client.setServer(mqtt_server, 1883);
 //client.setCallback(callback);
 pinMode(BUILTIN_LED, OUTPUT);
 pinMode(button, INPUT);
}
 
void loop() {
 if (!client.connected()) {
  reconectar();
 }
 button_state = digitalRead(button);
 if (button_state == LOW){
  Serial.println("Mensagem enviada!!");
  client.publish("Transelevador", "2");
  delay (5000);
 }
 client.loop();
}
