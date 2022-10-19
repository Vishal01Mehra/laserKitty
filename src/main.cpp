#include <Arduino.h>
#include <ESP32Servo.h>

const int echo = 5;
const int trig = 4;
#define SOUND_SPEED 0.034 //-cm/uS
#define CM_TO_INCH 0.393701
long Duration;
long Duration2;

float distanceCm;   
float tempDist;
float deadband = 1.5;

Servo pitch, yaw;
int pos = 0;
int pitchPin = 17;
int YawPin = 16;
int homepos;

void home()
{
  homepos = true;
  yaw.write(90);
  delay(150);
  pitch.write(90);
  delay(150);
}

void readDist()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  Duration = pulseIn(echo, HIGH);
  distanceCm = Duration * SOUND_SPEED / 2;
  delay(100);
}

void readDist2()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  Duration2 = pulseIn(echo, HIGH);
  tempDist = Duration2 * SOUND_SPEED / 2;
  delay(100);
}

void moveRandom(){
    int rndm = random(40, 120);
    int rndm2 = random(0, 120);
    pitch.write(rndm);
    yaw.write(rndm2);
    delay(100);
}


void setup()
{
  Serial.begin(9600);

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
  readDist2();
}



void loop()
{
  readDist();
  if (tempDist - distanceCm > deadband)
  {
   moveRandom();
   readDist();
   delay(500);
  }
  readDist2();
  Serial.print("Difference: ");
  Serial.println(tempDist - distanceCm);
}
