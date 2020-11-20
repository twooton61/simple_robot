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

namespace buzzer_note {
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
}

inline void reset_servo(Servo& servo) {
  servo.write(90);
}

inline void wave_servo_left(Servo& servo) {
  servo.write(0);
}

inline void wave_servo_right(Servo& servo) {
  servo.write(90);
}


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Servo servo;

inline void play_buzzer_note(const int buzzer_note, const int duration)
{
  static int note_count = 0;

  tone(PASSIVE_BUZZER_PIN, buzzer_note, duration);

  if(note_count % 2 == 0)
  {
    wave_servo_left(servo);
  }
  else
  {
    wave_servo_right(servo);
  }

  delay(duration);

  noTone(PASSIVE_BUZZER_PIN);

  delay(50);

  note_count++;
}

inline void writeLCDDoubleLine(String line1, String line2) {
  lcd.begin(16, 2);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
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
  play_buzzer_note(buzzer_note::a, 500);
  play_buzzer_note(buzzer_note::a, 500);
  play_buzzer_note(buzzer_note::a, 500);
  play_buzzer_note(buzzer_note::f, 350);
  play_buzzer_note(buzzer_note::cH, 150);
  play_buzzer_note(buzzer_note::a, 500);
  play_buzzer_note(buzzer_note::f, 350);
  play_buzzer_note(buzzer_note::cH, 150);
  play_buzzer_note(buzzer_note::a, 650);

  delay(500);

  play_buzzer_note(buzzer_note::eH, 500);
  play_buzzer_note(buzzer_note::eH, 500);
  play_buzzer_note(buzzer_note::eH, 500);
  play_buzzer_note(buzzer_note::fH, 350);
  play_buzzer_note(buzzer_note::cH, 150);
  play_buzzer_note(buzzer_note::gS, 500);
  play_buzzer_note(buzzer_note::f, 350);
  play_buzzer_note(buzzer_note::cH, 150);
  play_buzzer_note(buzzer_note::a, 650);

  delay(500);

  play_buzzer_note(buzzer_note::aH, 500);
  play_buzzer_note(buzzer_note::a, 300);
  play_buzzer_note(buzzer_note::a, 150);
  play_buzzer_note(buzzer_note::aH, 500);
  play_buzzer_note(buzzer_note::gSH, 325);
  play_buzzer_note(buzzer_note::gH, 175);
  play_buzzer_note(buzzer_note::fSH, 125);
  play_buzzer_note(buzzer_note::fH, 125);
  play_buzzer_note(buzzer_note::fSH, 250);

  delay(325);

  play_buzzer_note(buzzer_note::aS, 250);
  play_buzzer_note(buzzer_note::dSH, 500);
  play_buzzer_note(buzzer_note::dH, 325);
  play_buzzer_note(buzzer_note::cSH, 175);
  play_buzzer_note(buzzer_note::cH, 125);
  play_buzzer_note(buzzer_note::b, 125);
  play_buzzer_note(buzzer_note::cH, 250);

  delay(350);

  play_buzzer_note(buzzer_note::f, 250);
  play_buzzer_note(buzzer_note::gS, 500);
  play_buzzer_note(buzzer_note::f, 375);
  play_buzzer_note(buzzer_note::cH, 125);
  play_buzzer_note(buzzer_note::a, 500);
  play_buzzer_note(buzzer_note::f, 375);
  play_buzzer_note(buzzer_note::cH, 125);
  play_buzzer_note(buzzer_note::a, 650);

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
      writeLCDDoubleLine("Motion Detected", String(String(cm_from_ultrasonic_sensor/2.54) + "in away"));

      play_star_wars();

    } else {
      writeLCDDoubleLine("Hello!", "How are you?");

      reset_servo(servo);
    }
  }

  delay(1000);
}
