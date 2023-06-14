#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid     = "Dialog 4G 075";
const char *password = "al123456";
const char* mqtt_server = "test.mosquitto.org";
const char* send_topic = "VRcycling/test1";   //esp32 send topic
const char* recieved_topic = "VRcycling/test2";    //Oculus end publish topic
char sendMessage[10];
int num = 0;
bool recieved = true;

float mydata[1441] = {0.0, 0.08, 0.09, 0.11, 0.15, 0.2, 0.22, 0.23, 0.24, 0.26, 0.27, 0.28, 0.3, 0.32, 0.34, 0.36, 0.4, 0.52, 0.55, 0.94, 1.46, 1.82, 1.91, 1.93, 2.01, 
2.36, 2.54, 2.82, 2.94, 3.06, 3.14, 3.17, 3.47, 3.43, 3.61, 3.91, 4.03, 4.11, 4.23, 4.22, 4.12, 4.13, 4.32, 4.29, 4.22, 4.35, 4.48, 4.42, 4.35, 4.38, 4.45, 4.36, 
4.5, 4.67, 4.6, 4.59, 4.66, 4.59, 4.54, 4.81, 4.85, 4.77, 4.76, 4.84, 4.76, 4.7, 4.8, 4.77, 4.72, 4.75, 4.86, 4.79, 4.76, 4.95, 4.91, 4.85, 4.88, 4.9, 4.83, 4.91, 
5.02, 4.95, 4.87, 4.98, 4.94, 5.09, 5.19, 5.14, 5.15, 5.18, 5.12, 5.13, 5.26, 5.28, 5.31, 5.26, 5.29, 5.24, 5.28, 5.22, 5.21, 5.32, 5.28, 5.26, 5.31, 5.25, 5.22, 
5.28, 5.23, 5.18, 5.25, 5.21, 5.15, 5.23, 5.18, 5.12, 5.19, 5.15, 5.1, 5.15, 5.12, 5.08, 5.11, 5.1, 5.11, 5.18, 5.16, 5.15, 5.19, 5.15, 5.12, 5.21, 5.23, 5.18, 
5.26, 5.28, 5.24, 5.31, 5.27, 5.22, 5.29, 5.25, 5.2, 5.28, 5.32, 5.29, 5.36, 5.37, 5.34, 5.38, 5.34, 5.3, 5.35, 5.3, 5.25, 5.31, 5.25, 5.2, 5.27, 5.21, 5.16, 5.4, 
5.36, 5.41, 5.4, 5.43, 5.47, 5.5, 5.51, 5.5, 5.52, 5.53, 5.54, 5.53, 5.55, 5.54, 5.55, 5.54, 5.53, 5.52, 5.54, 5.53, 5.54, 5.55, 5.54, 5.53, 5.54, 5.53, 5.52, 5.53, 
5.52, 5.51, 5.52, 5.51, 5.5, 5.52, 5.54, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.53, 5.38, 5.24, 5.01, 4.48, 4.31, 3.75, 3.39, 2.57, 2.25, 2.02, 1.44, 1.02, 0.78, 
0.65, 0.64, 1.06, 1.28, 2.39, 4.75, 5.5, 5.53, 5.54, 5.55, 5.54, 5.55, 5.54, 5.53, 5.54, 5.53, 5.51, 5.53, 5.52, 5.55, 5.54, 5.55, 5.54, 5.53, 5.54, 5.53, 5.52, 5.53, 
5.52, 5.51, 5.53, 5.51, 5.52, 5.53, 5.52, 5.54, 5.53, 5.54, 5.53, 5.54, 5.53, 5.55, 5.54, 5.55, 5.54, 5.55, 5.56, 5.55, 5.56, 5.52, 5.45, 5.33, 5.01, 4.79, 4.42, 3.84, 
3.45, 3.06, 2.48, 2.16, 1.63, 1.18, 2.56, 3.33, 3.74, 4.06, 4.96, 5.28, 5.33, 5.52, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 
5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.57, 5.56, 5.55, 
5.56, 5.55, 5.56, 5.55, 5.58, 5.57, 5.58, 5.57, 5.56, 5.55, 5.56, 5.55, 5.52, 5.41, 5.26, 5.06, 4.61, 4.34, 3.87, 3.47, 2.71, 2.42, 2.4, 2.3, 3.05, 4.52, 5.0, 5.16, 5.45, 
5.54, 5.53, 5.54, 5.53, 5.54, 5.52, 5.47, 5.32, 4.98, 4.76, 4.32, 3.99, 3.14, 2.87, 2.42, 1.86, 1.57, 1.26, 0.67, 0.35, 0.16, 0.0, 0.47, 1.76, 4.17, 5.2, 5.27, 5.44, 5.51, 
5.55, 5.54, 5.55, 5.54, 5.55, 5.54, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 
5.57, 5.56, 5.57, 5.56, 5.63, 5.62, 5.63, 5.6, 5.59, 5.57, 5.58, 5.57, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 
5.54, 5.53, 5.54, 5.53, 5.52, 5.51, 5.49, 5.51, 5.49, 5.48, 5.49, 5.47, 5.46, 5.44, 5.47, 5.46, 5.54, 5.55, 5.54, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 
5.55, 5.54, 5.55, 5.54, 5.53, 5.54, 5.53, 5.51, 5.53, 5.51, 5.49, 5.5, 5.48, 5.46, 5.48, 5.46, 5.45, 5.49, 5.5, 5.54, 5.55, 5.54, 5.55, 5.54, 5.55, 5.56, 5.55, 5.56, 
5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.54, 5.55, 5.54, 5.53, 5.54, 5.53, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 
5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.54, 5.53, 5.52, 5.53, 5.52, 5.53, 5.54, 5.55, 5.54, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 
5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.53, 5.48, 5.33, 5.0, 4.78, 4.31, 3.97, 3.12, 2.85, 2.41, 1.83, 1.49, 1.2, 0.65, 0.28, 0.08, 0.0, 0.1, 0.09, 0.14, 
0.18, 0.14, 0.0, 0.13, 0.16, 0.12, 0.09, 0.07, 0.0, 0.29, 0.64, 1.51, 3.08, 4.63, 4.92, 4.94, 5.31, 5.41, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 
5.55, 5.54, 5.55, 5.54, 5.55, 5.54, 5.55, 5.56, 5.55, 5.56, 5.55, 5.54, 5.55, 5.54, 5.53, 5.52, 5.53, 5.51, 5.5, 5.52, 5.49, 5.47, 5.46, 5.44, 5.45, 5.43, 5.4, 5.43, 
5.39, 5.35, 5.39, 5.35, 5.31, 5.36, 5.31, 5.26, 5.32, 5.26, 5.21, 5.27, 5.21, 5.15, 5.21, 5.16, 5.1, 5.16, 5.11, 5.05, 5.09, 5.05, 5.0, 5.02, 4.95, 4.93, 4.98, 4.89, 
4.81, 4.9, 4.84, 4.78, 4.81, 4.82, 4.73, 4.66, 4.75, 4.68, 4.61, 4.65, 4.66, 4.56, 4.47, 4.58, 4.51, 4.44, 4.46, 4.49, 4.39, 4.29, 4.39, 4.38, 4.27, 4.17, 4.3, 4.25, 
4.16, 4.15, 4.2, 4.13, 4.05, 4.1, 4.03, 3.95, 3.94, 4.0, 3.92, 3.84, 3.83, 3.89, 3.82, 3.73, 3.67, 3.77, 3.73, 3.64, 3.52, 3.66, 3.68, 3.56, 3.46, 3.52, 3.57, 3.48, 
3.38, 3.35, 3.45, 3.54, 3.59, 3.65, 3.89, 3.98, 3.93, 4.0, 4.2, 4.35, 4.32, 4.33, 4.47, 4.54, 4.68, 4.92, 4.91, 4.99, 4.96, 5.05, 5.2, 5.27, 5.28, 5.23, 5.31, 5.36, 
5.35, 5.37, 5.33, 5.4, 5.43, 5.44, 5.46, 5.44, 5.42, 5.5, 5.52, 5.53, 5.52, 5.53, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.58, 5.57, 5.58, 5.57, 
5.6, 5.61, 5.62, 5.6, 5.64, 5.71, 5.74, 5.7, 5.87, 5.91, 5.86, 6.05, 6.07, 6.12, 6.03, 6.29, 6.36, 6.41, 6.29, 6.54, 6.64, 6.71, 6.55, 6.84, 6.93, 6.95, 6.8, 7.04, 
7.19, 7.11, 7.06, 7.16, 7.48, 7.35, 7.33, 7.38, 7.87, 7.73, 7.75, 8.18, 8.4, 8.23, 8.1, 8.77, 8.92, 8.9, 8.88, 9.7, 9.56, 9.42, 9.57, 10.15, 10.18, 9.81, 10.49, 10.31, 
10.17, 10.03, 10.65, 10.84, 10.38, 10.9, 10.78, 10.55, 10.86, 11.2, 10.77, 10.75, 11.32, 11.52, 11.38, 11.63, 11.66, 11.32, 11.23, 10.72, 10.59, 10.2, 9.98, 9.79, 
9.45, 9.36, 9.0, 8.92, 8.62, 8.51, 8.28, 8.11, 7.97, 7.77, 7.69, 7.48, 7.45, 7.24, 7.22, 7.02, 6.82, 6.81, 6.64, 6.63, 6.47, 6.33, 6.32, 6.2, 6.1, 6.01, 5.93, 5.94, 
5.86, 5.87, 5.81, 5.82, 5.76, 5.71, 5.67, 5.64, 5.62, 5.61, 5.59, 5.58, 5.57, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.56, 5.57, 5.6, 5.61, 5.65, 5.7, 5.73, 
5.7, 5.72, 5.85, 5.94, 5.89, 5.91, 6.06, 6.23, 6.16, 6.18, 6.38, 6.58, 6.52, 6.79, 6.97, 6.9, 6.89, 7.38, 7.49, 7.45, 7.36, 8.21, 8.15, 8.13, 8.42, 9.1, 9.02, 8.88, 
9.69, 9.98, 10.06, 9.73, 10.72, 10.43, 10.26, 10.87, 11.27, 11.32, 10.89, 11.58, 11.66, 11.34, 11.24, 10.77, 10.61, 10.28, 9.96, 9.82, 9.44, 9.36, 9.0, 8.92, 8.64, 
8.52, 8.31, 8.13, 8.03, 7.8, 7.76, 7.52, 7.5, 7.28, 7.26, 7.06, 7.05, 6.86, 6.84, 6.67, 6.65, 6.5, 6.48, 6.35, 6.33, 6.23, 6.21, 6.13, 6.11, 6.03, 6.02, 5.95, 5.87, 
5.88, 5.82, 5.83, 5.77, 5.78, 5.73, 5.69, 5.66, 5.65, 5.63, 5.62, 5.61, 5.6, 5.58, 5.59, 5.57, 5.58, 5.57, 5.56, 5.55, 5.56, 5.55, 5.56, 5.55, 5.54, 5.53, 5.52, 
5.53, 5.52, 5.51, 5.49, 5.5, 5.49, 5.46, 5.49, 5.46, 5.45, 5.46, 5.43, 5.4, 5.39, 5.36, 5.37, 5.35, 5.32, 5.34, 5.31, 5.27, 5.3, 5.26, 5.22, 5.25, 5.22, 5.18, 
5.2, 5.17, 5.13, 5.14, 5.07, 5.09, 5.02, 4.96, 5.04, 4.97, 4.9, 4.97, 4.92, 4.86, 4.88, 4.89, 4.81, 4.78, 4.84, 4.76, 4.69, 4.82, 4.85, 4.93, 5.1, 5.2, 5.25, 
5.4, 5.44, 5.45, 5.49, 5.5, 5.52, 5.54, 5.55, 5.56, 5.55, 5.56, 5.57, 5.56, 5.59, 5.6, 5.63, 5.62, 5.66, 5.69, 5.74, 5.79, 5.8, 5.93, 6.08, 6.15, 6.13, 6.27, 6.33, 
6.31, 6.25, 6.55, 6.59, 6.57, 6.48, 6.73, 6.8, 6.81, 6.7, 7.07, 7.04, 7.07, 6.93, 7.52, 7.69, 7.64, 7.56, 8.12, 8.35, 8.19, 9.02, 9.64, 9.72, 9.49, 10.37, 10.31, 
9.99, 10.18, 10.48, 10.61, 10.32, 11.52, 11.66, 11.34, 11.23, 10.73, 10.61, 10.2, 10.03, 9.76, 9.48, 9.36, 9.01, 8.96, 8.62, 8.56, 8.31, 8.2, 8.0, 7.83, 7.73, 
7.55, 7.5, 7.3, 7.28, 7.08, 7.07, 6.89, 6.71, 6.55, 6.41, 6.4, 6.27, 6.16, 6.06, 5.97, 5.98, 5.9, 5.91, 5.83, 5.84, 5.78, 5.79, 5.73, 5.69, 5.66, 5.65, 5.64, 
5.62, 5.6, 5.61, 5.59, 5.58, 5.57, 5.56, 5.55, 5.56, 5.55, 5.54, 5.52, 5.54, 5.52, 5.5, 5.51, 5.5, 5.48, 5.5, 5.47, 5.45, 5.48, 5.45, 5.44, 5.45, 5.42, 5.41, 
5.38, 5.4, 5.38, 5.35, 5.37, 5.34, 5.3, 5.33, 5.3, 5.26, 5.3, 5.26, 5.22, 5.25, 5.22, 5.17, 5.2, 5.17, 5.13, 5.15, 5.14, 5.08, 5.1, 5.03, 5.0, 5.06, 4.98, 4.91, 
5.0, 4.94, 4.89, 4.92, 4.9, 4.83, 4.87, 4.79, 4.7, 4.8, 4.74, 4.68, 4.69, 4.73, 4.63, 4.53, 4.64, 4.59, 4.52, 4.53, 4.58, 4.48, 4.4, 4.48, 4.47, 4.37, 4.27, 4.39, 
4.34, 4.26, 4.32, 4.23, 4.16, 4.18, 4.23, 4.12, 4.04, 4.1, 4.15, 4.03, 3.93, 4.01, 4.05, 3.93, 3.84, 3.9, 3.95, 3.83, 3.75, 3.78, 3.83, 3.74, 3.66, 3.71, 3.66, 
3.56, 3.44, 3.6, 3.61, 3.48, 3.39, 3.47, 3.52, 3.42, 3.33, 3.3, 3.38, 3.26, 3.17, 3.24, 3.29, 3.21, 3.11, 3.0, 3.15, 3.19, 3.07, 2.98, 2.91, 3.03, 3.06, 2.94, 
2.85, 2.84, 2.91, 2.94, 2.82, 2.73, 2.7, 2.79, 2.83, 2.72, 2.62, 2.52, 2.66, 2.72, 2.63, 2.53, 2.44, 2.52, 2.57, 2.54, 2.45, 2.37, 2.32, 2.42, 2.48, 2.39, 2.29, 
2.22, 2.26, 2.32, 2.35, 2.25, 2.16, 2.08, 2.15, 2.21, 2.22, 2.12, 2.03, 1.97, 2.03, 2.08, 2.11, 2.02, 1.93, 1.87, 1.88, 1.95, 2.0, 1.93, 1.85, 1.78, 1.7, 1.81, 
1.86, 1.88, 1.79, 1.71, 1.65, 1.63, 1.7, 1.75, 1.74, 1.67, 1.59, 1.53, 1.52, 1.58, 1.63, 1.64, 1.57, 1.49, 1.43, 1.37, 1.45, 1.5, 1.54, 1.49, 1.42, 1.35, 1.31, 
1.3, 1.36, 1.41, 1.43, 1.38, 1.31, 1.24, 1.2, 1.18, 1.24, 1.29, 1.32, 1.28, 1.23, 1.16, 1.11, 1.07, 1.12, 1.16, 1.2, 1.22, 1.17, 1.11, 1.05, 1.0, 0.97, 1.01, 1.05, 
0.75, 0.39, 0.09, 0.0, 0.07, 0.08, 0.09, 0.1, 0.09};


WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setupWiFi() {
  delay(10);
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


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  recieved = true;
}


void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outgoingTopic", "hello world");
      // ... and resubscribe
      client.subscribe(recieved_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setupWiFi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}


void loop() {
  if (!client.connected()) {
    reconnect();
    Serial.print("connected");
  }
  client.loop();
  if(num < 1441){
    if(recieved == true){
      dtostrf(mydata[num],4,2,sendMessage);
      Serial.println(sendMessage);
      client.publish(send_topic, sendMessage);
      recieved = false;
      num++;
    }
  }
}

