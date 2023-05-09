#define PI 3.141592

int HallSensor = 2;
int LED = 13;
float revolutions = 0;
float omega = 0;
float speed;
int rpm = 0;
long startTime = 0;
long elapsedTime = 0;
float radius = 0.17;

void setup() {
  pinMode(HallSensor, INPUT_PULLUP); 
  Serial.begin(9600);
}

void loop() {
  revolutions = 0; rpm = 0;
  startTime  = millis();
  attachInterrupt(digitalPinToInterrupt(2), interruptFunction, RISING);
  delay(1000);
  detachInterrupt(2);

  elapsedTime = millis() - startTime;

  if(revolutions >= 0){
    rpm = (revolutions * 60000) / (4 * elapsedTime);
    omega = 2 * PI * (rpm / 60);
    speed = omega * radius;
  }
  Serial.print("Speed = ");
  Serial.print(speed);
  Serial.print(" RPM = ");
  Serial.println(rpm);

}

void interruptFunction(){
  revolutions++;
}
