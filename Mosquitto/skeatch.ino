#include<DHT.h>
#include<PubSubClient.h>
#include<WiFi.h>

const char* ssid = "XXXXXX"; //input your SSID
const char* password = "XXXXXX"; //input your password SSID
const char* mqtt_broker = "XXXXXX"; // input your url mqtt_server
const char* mqtt_user = "XXXXXX"; //input your MQTT Username
const char* mqtt_password = "XXXXXX"; //input your MQTT Password

#define pin 15
#define tipe DHT22
WiFiClient eclient;
PubSubClient client(eclient);
DHT dht(pin, tipe);
void setup() {
  // put your setup code here, to run once:
  dht.begin();
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  client.setServer(mqtt_broker, 1883);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  float suhu = dht.readTemperature();
  float humi = dht.readHumidity();

  // Kirim data suhu dan kelembapan ke broker MQTT
  client.publish("sensor/suhu", String(suhu).c_str());
  client.publish("sensor/kelembapan", String(humi).c_str());
  
  Serial.println("Suhu: " + String(suhu) + "||" + "Kelembaban : " + String(humi));
  delay(10000);
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32_DHT22", mqtt_user, mqtt_password)) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.println("Failed to connect to MQTT. Retrying in 5 seconds");
      delay(5000);
    }
  }
}