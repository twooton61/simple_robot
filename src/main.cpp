/*
   Server Robot
   Author: twooton
   Email: tcwooton@gmail.com
   Description: Simple Robot
*/

#include <Servo.h>
#include <Arduino.h>
#include <LiquidCrystal.h>

const uint8_t ULTRASONIC_SENSOR_ECHO_DETECT_PIN = 8;
const uint8_t ULTRASONIC_SENSOR_TRIGGER_PIN = 9;
const uint8_t IR_RECEIVER_PIN = 7;
const uint8_t PASSIVE_BUZZER_PIN = 6;
const uint8_t SERVO_PIN = 10;

const uint8_t SENSOR_STOP_SIGNAL = 0;
const uint8_t SENSOR_SEND_SIGNAL = 1;
const uint8_t BUZZER_ON = HIGH;
const uint8_t BUZZER_OFF = LOW;

const unsigned int SENSOR_DISTANCE_IN_RANGE = 30;
const unsigned int SENSOR_DISTANCE_WAY_FAR_AWAY = 1000;

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
int counter = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Servo servo;


inline void reset_servo(Servo& servo) {
  servo.write(90);
}

inline void wave_servo_left(Servo& servo) {
  servo.write(0);
}

inline void wave_servo_right(Servo& servo) {
  servo.write(90);
}

void beep(int note, int duration)
{
  tone(PASSIVE_BUZZER_PIN, note, duration);
 
  if(counter % 2 == 0)
  {
    wave_servo_left(servo);

  }else
  {
    wave_servo_right(servo);

  }

  delay(duration);

 
  noTone(PASSIVE_BUZZER_PIN);
 
  delay(50);
 
  counter++;
}

inline void writeLCDDoubleLine(String line1, String line2) {
  lcd.begin(16, 2);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

inline void standard_delay() {
  delay(400);
}

inline unsigned long get_cm_from_sensor() {
  digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, SENSOR_STOP_SIGNAL);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, SENSOR_SEND_SIGNAL);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, SENSOR_STOP_SIGNAL);

  const unsigned long duration = pulseIn(ULTRASONIC_SENSOR_ECHO_DETECT_PIN, HIGH);

  return int(duration / 2 / 29.412);
}

inline void play_star_wars() {
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);

  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);

  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);

  delay(325);

  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  

  delay(350);

  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 650);  

  delay(650);

 

}


void setup()
{
  Serial.begin(9600);

  pinMode(PASSIVE_BUZZER_PIN, OUTPUT);

  pinMode(ULTRASONIC_SENSOR_TRIGGER_PIN, OUTPUT);

  pinMode(ULTRASONIC_SENSOR_ECHO_DETECT_PIN, INPUT);

  servo.attach(SERVO_PIN);

  reset_servo(servo);

  servo.write(90);
}

void loop()
{
  Serial.println("loop");
  
  const unsigned long cm_from_ultrasonic_sensor = get_cm_from_sensor();
  if (cm_from_ultrasonic_sensor <= SENSOR_DISTANCE_WAY_FAR_AWAY) {
    Serial.print("sensor: distance is ");
    Serial.print(cm_from_ultrasonic_sensor);
    Serial.print("cm comparing to ");
    Serial.print(SENSOR_DISTANCE_IN_RANGE);
    Serial.println("cm");
    if (cm_from_ultrasonic_sensor == 0) {
      Serial.println("sensor error, reading 0 distance");
    }
    else if (cm_from_ultrasonic_sensor <= SENSOR_DISTANCE_IN_RANGE)
    {
      writeLCDDoubleLine("Audrey & Charlie", String(String(cm_from_ultrasonic_sensor/2.54) + "in away"));

      play_star_wars();

    } else {
      writeLCDDoubleLine("Robo Jukebox", "Select a Song");

      reset_servo(servo);
    }
    
  }

  delay(1000);
}
