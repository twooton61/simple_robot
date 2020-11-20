/*
   Server Robot
   Author: twooton
   Email: tcwooton@gmail.com
   Description: Simple Robot
*/

#include <Servo.h>
#include <Arduino.h>
#include <LiquidCrystal.h>

/* servo */
const uint8_t SERVO_PIN = 10;

namespace servo_helper {
  inline void reset(Servo& servo) {
    servo.write(90);
  }

  inline void wave_left(Servo& servo) {
    servo.write(0);
  }

  inline void wave_right(Servo& servo) {
    servo.write(90);
  }
}

Servo servo;

/* lcd */

namespace lcd_helper {
  inline void writeLCDDoubleLine(LiquidCrystal& lcd, String line1, String line2) {
    lcd.begin(16, 2);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
  }
}

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/* setup ultrasonic sensor */
const uint8_t ULTRASONIC_SENSOR_ECHO_DETECT_PIN = 8;
const uint8_t ULTRASONIC_SENSOR_TRIGGER_PIN = 9;
const uint8_t SENSOR_STOP_SIGNAL = 0;
const uint8_t SENSOR_SEND_SIGNAL = 1;
const unsigned int SENSOR_DISTANCE_IN_RANGE = 30;
const unsigned int SENSOR_DISTANCE_WAY_FAR_AWAY = 1000;

namespace ultrasonic_helper {
  inline unsigned long get_cm_from_sensor() {
    digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, SENSOR_STOP_SIGNAL);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, SENSOR_SEND_SIGNAL);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_SENSOR_TRIGGER_PIN, SENSOR_STOP_SIGNAL);

    const unsigned long duration = pulseIn(ULTRASONIC_SENSOR_ECHO_DETECT_PIN, HIGH);

    return int(duration / 2 / 29.412);
  }
}

/* buzzer */
const uint8_t PASSIVE_BUZZER_PIN = 6;
const uint8_t BUZZER_ON = HIGH;
const uint8_t BUZZER_OFF = LOW;
namespace buzzer_helper {
  namespace note {
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

  inline void play_note(const int buzzer_note, const int duration)
  {
    static int note_count = 0;

    tone(PASSIVE_BUZZER_PIN, buzzer_note, duration);

    if(note_count % 2 == 0)
    {
      servo_helper::wave_left(servo);
    }
    else
    {
      servo_helper::wave_right(servo);
    }

    delay(duration);

    noTone(PASSIVE_BUZZER_PIN);

    delay(50);

    note_count++;
  }

  inline void play_star_wars() {
    play_note(buzzer_helper::note::a, 500);
    play_note(buzzer_helper::note::a, 500);
    play_note(buzzer_helper::note::a, 500);
    play_note(buzzer_helper::note::f, 350);
    play_note(buzzer_helper::note::cH, 150);
    play_note(buzzer_helper::note::a, 500);
    play_note(buzzer_helper::note::f, 350);
    play_note(buzzer_helper::note::cH, 150);
    play_note(buzzer_helper::note::a, 650);

    delay(500);

    play_note(buzzer_helper::note::eH, 500);
    play_note(buzzer_helper::note::eH, 500);
    play_note(buzzer_helper::note::eH, 500);
    play_note(buzzer_helper::note::fH, 350);
    play_note(buzzer_helper::note::cH, 150);
    play_note(buzzer_helper::note::gS, 500);
    play_note(buzzer_helper::note::f, 350);
    play_note(buzzer_helper::note::cH, 150);
    play_note(buzzer_helper::note::a, 650);

    delay(500);

    play_note(buzzer_helper::note::aH, 500);
    play_note(buzzer_helper::note::a, 300);
    play_note(buzzer_helper::note::a, 150);
    play_note(buzzer_helper::note::aH, 500);
    play_note(buzzer_helper::note::gSH, 325);
    play_note(buzzer_helper::note::gH, 175);
    play_note(buzzer_helper::note::fSH, 125);
    play_note(buzzer_helper::note::fH, 125);
    play_note(buzzer_helper::note::fSH, 250);

    delay(325);

    play_note(buzzer_helper::note::aS, 250);
    play_note(buzzer_helper::note::dSH, 500);
    play_note(buzzer_helper::note::dH, 325);
    play_note(buzzer_helper::note::cSH, 175);
    play_note(buzzer_helper::note::cH, 125);
    play_note(buzzer_helper::note::b, 125);
    play_note(buzzer_helper::note::cH, 250);

    delay(350);

    play_note(buzzer_helper::note::f, 250);
    play_note(buzzer_helper::note::gS, 500);
    play_note(buzzer_helper::note::f, 375);
    play_note(buzzer_helper::note::cH, 125);
    play_note(buzzer_helper::note::a, 500);
    play_note(buzzer_helper::note::f, 375);
    play_note(buzzer_helper::note::cH, 125);
    play_note(buzzer_helper::note::a, 650);

    delay(650);
  }
}

void setup()
{
  Serial.begin(9600);

  pinMode(PASSIVE_BUZZER_PIN, OUTPUT);

  pinMode(ULTRASONIC_SENSOR_TRIGGER_PIN, OUTPUT);

  pinMode(ULTRASONIC_SENSOR_ECHO_DETECT_PIN, INPUT);

  servo.attach(SERVO_PIN);

  servo_helper::reset(servo);
}

void loop()
{
  Serial.println("loop");

  const unsigned long cm_from_ultrasonic_sensor = ultrasonic_helper::get_cm_from_sensor();
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
      lcd_helper::writeLCDDoubleLine(lcd, "Motion Detected", String(String(cm_from_ultrasonic_sensor/2.54) + "in away"));

      delay(3000);

      lcd_helper::writeLCDDoubleLine(lcd, "Playing", "Star Wars");

      buzzer_helper::play_star_wars();

    } else {
      lcd_helper::writeLCDDoubleLine(lcd, "Hello! Wave", "for a song");

      servo_helper::reset(servo);
    }
  }

  delay(1000);
}