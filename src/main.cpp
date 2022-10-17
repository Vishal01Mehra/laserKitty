#include <Arduino.h>
#include <ESP32Servo.h>

const int echo = 4;
const int trig = 5;
#define SOUND_SPEED 0.034 //-cm/uS
#define CM_TO_INCH 0.393701
long Duration;
float distanceCm;
int tempDist;

Servo  pitch, yaw; 
int pos = 0;   
int pitchPin = 17;
int YawPin = 16;
int homepos;

void home(){
  homepos = true;
  yaw.write(90);
  delay(150);
  pitch.write(90);
  delay(150);
}

void setup() {
  Serial.begin(115200);

	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	pitch.setPeriodHertz(50);
  yaw.setPeriodHertz(50);
	pitch.attach(pitchPin, 1000, 2000);
  yaw.attach(YawPin, 1000, 2000);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT); 
  home();
}

void readDist(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  Duration = pulseIn(echo, HIGH);
  distanceCm = Duration * SOUND_SPEED/2;
}

void loop() {
  readDist();
  distanceCm = tempDist;
  delay(500);
  readDist();
  if(distanceCm != tempDist){
    int rndm = random(50,120);
    int rndm2 = random(50, 120);
    pitch.write(rndm);
    yaw.write(rndm2);
    delay(500);
  }

}
