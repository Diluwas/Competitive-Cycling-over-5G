#include <NTPClient.h>
// change next line to use with another board/shield
//#include <ESP8266WiFi.h>
#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#include <PubSubClient.h>


const char *ssid     = "Dialog 4G TNR";
const char *password = "Legendseeker#23";
const char* mqtt_server = "192.168.8.130";
int BUFFER_SIZE = 10; 

WiFiUDP ntpUDP;
WiFiClient espClient;
PubSubClient client(espClient);

char msg[7];
float Sinwave[193] = {0,0.49009,0.97545,1.4514,1.9134,2.357,2.7779,3.172,3.5355,3.8651,4.1573,4.4096,4.6194,4.7847,4.9039,4.9759,5,4.9759,4.9039,4.7847,4.6194,
4.4096,4.1573,3.8651,3.5355,3.172,2.7779,2.357,1.9134,1.4514,0.97545,0.49009,0,-0.49009,-0.97545,-1.4514,-1.9134,-2.357,-2.7779,-3.172,-3.5355,-3.8651,
-4.1573,-4.4096,-4.6194,-4.7847,-4.9039,-4.9759,-5,-4.9759,-4.9039,-4.7847,-4.6194,-4.4096,-4.1573,-3.8651,-3.5355,-3.172,-2.7779,-2.357,-1.9134,-1.4514,-0.97545,
-0.49009,0,0.49009,0.97545,1.4514,1.9134,2.357,2.7779,3.172,3.5355,3.8651,4.1573,4.4096,4.6194,4.7847,4.9039,4.9759,5,4.9759,4.9039,4.7847,4.6194,
4.4096,4.1573,3.8651,3.5355,3.172,2.7779,2.357,1.9134,1.4514,0.97545,0.49009,0,-0.49009,-0.97545,-1.4514,-1.9134,-2.357,-2.7779,-3.172,-3.5355,
-3.8651,-4.1573,-4.4096,-4.6194,-4.7847,-4.9039,-4.9759,-5,-4.9759,-4.9039,-4.7847,-4.6194,-4.4096,-4.1573,-3.8651,-3.5355,-3.172,-2.7779,-2.357,-1.9134,
-1.4514,-0.97545,-0.49009,0,0.49009,0.97545,1.4514,1.9134,2.357,2.7779,3.172,3.5355,3.8651,4.1573,4.4096,4.6194,4.7847,4.9039,4.9759,5,4.9759,
4.9039,4.7847,4.6194,4.4096,4.1573,3.8651,3.5355,3.172,2.7779,2.357,1.9134,1.4514,0.97545,0.49009,0,-0.49009,-0.97545,-1.4514,-1.9134,-2.357,-2.7779,
-3.172,-3.5355,-3.8651,-4.1573,-4.4096,-4.6194,-4.7847,-4.9039,-4.9759,-5,-4.9759,-4.9039,-4.7847,-4.6194,-4.4096,-4.1573,-3.8651,-3.5355,-3.172,-2.7779,
-2.357,-1.9134,-1.4514,-0.97545,-0.49009,0};

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionally you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "lk.pool.ntp.org", 0, 60000);

void setup_wifi(){
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), NULL, NULL , "CCO5/test", 1, false, "hello")) {
      Serial.println("connected");
      client.publish("CCO5/test", "hello",BUFFER_SIZE);
      // Once connected, publish an announcement...
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


void setup(){
  Serial.begin(115200);
  setup_wifi();
  timeClient.begin();
  client.setServer(mqtt_server, 1883);

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  for(int i = 0; i < 193; i++){
    //Serial.print("Publish message: ");
    dtostrf(Sinwave[i], BUFFER_SIZE - 1, 4,  msg);
    timeClient.update();
    client.publish("CCO5/test", msg, BUFFER_SIZE);
    Serial.println(msg);
    memset(msg, 0, 10);
    delay(400);
  }
  Serial.print("Finish");  
  exit(0);
}
