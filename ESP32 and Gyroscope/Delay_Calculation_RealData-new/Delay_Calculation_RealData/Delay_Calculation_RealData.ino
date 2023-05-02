#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "MPU6050_6Axis_MotionApps20.h"
#include <Wire.h>
#include <PubSubClient.h>
#include <WiFi.h>

const char *ssid     = "V2061";
const char *password = "Dulsara123";
//const char *ssid     = "Dialog 4G TNR";   tharuka
//const char *password = "Legendseeker#23";
const char* mqtt_server = "test.mosquitto.org";
char destinationX1[10];
char destinationX2[10];
char destinationY1[10];
char destinationY2[10];
char destinationZ1[10];
char destinationZ2[10];
//const char *acc = " Acceleration";
//const char *vel = " Velocity";
double linearVelX;
double linearVelY;
double linearVelZ;
double radius = 0.3;

//WiFiUDP ntpUDP;
WiFiClient espClient;
PubSubClient client(espClient);

Adafruit_MPU6050 mpu;
MPU6050 mpu1;

//NTPClient timeClient(ntpUDP, "lk.pool.ntp.org", 0, 60000);

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
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);

    
 // supply your own gyro offsets here, scaled for min sensitivity
  mpu1.setXGyroOffset(50);
  mpu1.setYGyroOffset(18);
  mpu1.setZGyroOffset(19);
  mpu1.setXAccelOffset(-1847); // 1688 factory default for my test chip
  mpu1.setYAccelOffset(49);
  mpu1.setZAccelOffset(1523);
}

void loop() {

    
  if (!client.connected()) {
      reconnect();
  }
  client.loop();
  //client.publish("Mytest", "Rounds seperator");
    //Serial.println(msg);
    /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);


  /* Print out the values */
  /*Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);   
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);*/
  dtostrf(abs(a.acceleration.x),4,2,destinationX1);  
  strcat(destinationX1, "=aX ");
  dtostrf(abs(a.acceleration.y),4,2,destinationY1);  
  strcat(destinationY1, "=aY ");
  dtostrf(abs(a.acceleration.z),4,2,destinationZ1);  
  strcat(destinationZ1, "=aZ ");     
  //Serial.println(" m/s^2");
  
  /*Serial.print("Rotation X: ");
  /Serial.print(g.gyro.x);
  linearVelX = (g.gyro.x * radius);  
  /dtostrf(g.gyro.x,4,2,destination2); 
  if (linearVelX>0) {

    dtostrf(linearVelX,4,2,destinationX2); 
    client.publish("VRcycling/test", destinationX2);
    Serial.print(destinationX2);
    Serial.println("");
    }*/    
 /* client.publish("Mytest", g.gyro.x);
  Serial.print(g.gyro.x);  
  client.publish("Mytest", g.gyro.y);
  Serial.print(g.gyro.y);
  client.publish("Mytest", g.gyro.z);
  Serial.print(g.gyro.z); */

  
  linearVelX = (abs(g.gyro.x));
  dtostrf(linearVelX,4,2,destinationX2);    
  //strcat(destinationX2, "=vX");   
  //strcat(destinationX1, destinationX2);      
  //Serial.print(", Y: ");
  //Serial.print(g.gyro.y);
  linearVelY = (abs(g.gyro.y));
  dtostrf(linearVelY,4,2,destinationY2);
  //strcat(destinationY2, "=vY");   
  //strcat(destinationY1, destinationY2);  
  //Serial.print(", Z: ");
  //Serial.print(g.gyro.z);
  linearVelZ = (abs(g.gyro.z)); 
  dtostrf(linearVelZ,4,2,destinationZ2);  
  //strcat(destinationZ2, "=vZ");   
  //strcat(destinationZ1, destinationZ2);   
  //Serial.println(" rad/s");
  strcat(destinationX2, "  ");
  strcat(destinationX2, destinationY2);
  strcat(destinationX2, "  ");
  strcat(destinationX2, destinationZ2);

  client.publish("Mytest", destinationX2);
  //client.publish("Mytest", destinationY2);
  //client.publish("Mytest", destinationZ2);      
  //Serial.println(destinationX1); 
  //Serial.println(destinationY1);   
  //Serial.println(destinationZ1);
  /*Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");*/

  //Serial.println("");
  delay(1000);
}
