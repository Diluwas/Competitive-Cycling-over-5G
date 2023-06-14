#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "MPU6050_6Axis_MotionApps20.h"
#include <Wire.h>
#include <PubSubClient.h>
#include <WiFi.h>

#include "FS.h"
#include "SD.h"
#include "SPI.h"

//const char *ssid     = "V2061";        //my hotspot
//const char *password = "Dulsara123";

//const char *ssid     = "Aruna-Lakpriya";      //SDR 4G core
//const char *password = "al123456";

//const char *ssid     = "Dialog 4G 075";       //Aruna 4G
//const char *password = "al123456";

const char *ssid     = "Dialog 4G TNR";         //Tharuka 4G
const char *password = "Legendseeker#23";

//const char *ssid     = "5G PSI Lab Router 2.4GHz";         //Dialog 5G
//const char *password = "Dialog@psitest24";

//const char *ssid     = "HUAWEI_H112_239E";         //Uni 5G
//const char *password = "houseoffire";



//const char* mqtt_server = "192.168.1.10";
//const char* mqtt_server = "192.168.8.183";
const char* mqtt_server = "test.mosquitto.org";



char destinationZ1[10];
char destinationZ2[10];
char destinationZ3[10];
char destinationZ4[10];

double linearVelZ;
double updatedVelZ;
double displayspeed;
double gyroZ;
double playbackSpeed;
double radius = 0.21;
double distance = 0;
double sampletime = 0.1;  //delay of loop to get speed,distance values
double maxSpeed = 12.5;
double maxPlayback = 3;
double gyroZerror = 0.02;
double prev_speed=0;
long count = 0;

double p1 = 0.005429;
double p2 = -0.08082;
double p3 = 0.3511;
double p4 = -0.3186;
double p5 = 0.609;
double p6 = 0.06184;

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
    String clientId = "ESP32Client-";
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
  

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
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
  mpu1.setXGyroOffset(47);
  mpu1.setYGyroOffset(22);
  mpu1.setZGyroOffset(27);
  mpu1.setXAccelOffset(-2179); // 1688 factory default for my test chip
  mpu1.setYAccelOffset(1827);
  mpu1.setZAccelOffset(3226);

}


void loop() {

    
  if (!client.connected()) {
      reconnect();
  }
  client.loop();
    /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  
  //dtostrf(abs(a.acceleration.z),4,2,destinationZ1);
  double gyroZ_temp = g.gyro.z;
  if(abs(gyroZ_temp) > gyroZerror) {
    gyroZ = gyroZerror + gyroZ_temp;
    gyroZerror = gyroZ_temp/10;
  } 
  else{
    gyroZ = g.gyro.z;
    gyroZerror = 0.02;
  }    
  linearVelZ = radius*(abs(gyroZ));
  updatedVelZ = (pow(linearVelZ,5)*p1) + (pow(linearVelZ,4)*p2) + (pow(linearVelZ,3)*p3) + (pow(linearVelZ,2)*p4) + (linearVelZ*p5) + p6;

  if(updatedVelZ > 0.07){
    displayspeed = updatedVelZ;
  }
  else{
    displayspeed = 0.00;
  }

 /* if (displayspeed > 12.5){
    playbackSpeed = maxPlayback;
  }
  else if(displayspeed > 0.1){
    playbackSpeed = (displayspeed*maxPlayback) / maxSpeed ;
  }
  else{
    playbackSpeed = 0.00;
  }*/

  dtostrf(displayspeed,4,2,destinationZ4); 
  //dtostrf(playbackSpeed,4,2,destinationZ2); 
  
  if (displayspeed < 12.5){
    distance = distance + (((displayspeed+prev_speed)/2) * sampletime);
  }
  else{
    distance = distance + (((12.5+prev_speed)/2) * sampletime) ;
  }
  dtostrf(distance,4,2,destinationZ3);
  prev_speed = displayspeed;
  if (count%50==0){
    client.publish("VRcycling/UserB/Distance", destinationZ3);  //distance
    Serial.print("distance = ");
    Serial.println(destinationZ3);
  }
  if (count%2==0){
    client.publish("VRcycling/UserB/Speed", destinationZ4);     // bicycle display speed
    Serial.print("bicycle speed = ");
    Serial.println(destinationZ4);
  }
  count+=1;

  //client.publish("Mytest", destinationZ1);         //acceleration
  //client.publish("VRcycling/playback", destinationZ2);  //playback speed
  
  //Serial.print("acceleration = ");
  //Serial.println(destinationZ1);
  //Serial.print("playback speed = ");
  //Serial.println(destinationZ2);
  
  delay(100);
}
