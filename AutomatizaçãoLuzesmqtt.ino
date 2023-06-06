#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "nome_da_rede";
const char* password = "senha_da_rede";
const char* mqtt_server = "endereco_do_broker_mqtt";
const int mqtt_port = 1883;
const char* mqtt_topic = "topic/test";
const byte LED = 9;
const byte LDR = A5;

unsigned int valorLDR;
WiFiClient espClient;
PubSubClient client(espClient);
ESP8266WebServer server(80);

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
 }

client.setServer(mqtt_server, mqtt_port);
client.setCallback(callback);

server.on("/", handleRoot);
server.onNotFound(handleNotFound);
server.begin();
}

void loop() {
 if (!client.connected()) {
 reconnect();
}

client.loop();
valorLDR = analogRead(LDR);
analogWrite(LED, byte(200 - (valorLDR / 4)));
char msg[10];
sprintf(msg, "%d", valorLDR);
client.publish(mqtt_topic, msg);
Serial.println(valorLDR);
server.handleClient();
}

void callback(char* topic, byte* payload, unsigned int length) {
 // Função de callback para receber mensagens MQTT
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("arduino-client")) {
      client.subscribe(mqtt_topic);
    } else {
      delay(5000);
    }
  }
}

void handleRoot() {
  String html = "<html><body><h1>Dados do LDR</h1><p>";
  html += "Valor LDR: " + String(valorLDR) + "</p></body></html>";
  server.send(200, "text/html", html);
}

void handleNotFound() {
  String message = "Página não encontrada.";
  server.send(404, "text/plain", message);
}
