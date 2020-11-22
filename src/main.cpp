/*
   Server Robot
   Author: twooton
   Email: tcwooton@gmail.com
   Description: Simple Robot
*/

#include <Servo.h>
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <RoboServo.h>
#include <RoboLCD.h>
#include <RoboDancer.h>
#include <RoboUltrasonicSensor.h>


const int SERVO_PIN = 10;
RoboServo main_robo_servo(SERVO_PIN);

const int PASSIVE_BUZZER_PIN = 6;
RoboDancer robo_dancer(main_robo_servo, PASSIVE_BUZZER_PIN);

const int ULTRASONIC_SENSOR_ECHO_DETECT_PIN = 8;
const int ULTRASONIC_SENSOR_TRIGGER_PIN = 9;
RoboUltrasonicSensor robo_ultrasonice_sensor(ULTRASONIC_SENSOR_ECHO_DETECT_PIN, ULTRASONIC_SENSOR_TRIGGER_PIN);

RoboLCD robo_lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);

  main_robo_servo.setup();
  robo_dancer.setup();
  robo_ultrasonice_sensor.setup();
}

void loop()
{
  Serial.println("loop");

  const unsigned long cm_from_ultrasonic_sensor = robo_ultrasonice_sensor.get_cm_from_sensor();

  const unsigned int SENSOR_DISTANCE_WAY_FAR_AWAY = 1000;
  const unsigned int SENSOR_DISTANCE_IN_RANGE = 30;

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
      robo_lcd.write_double_line("Motion Detected", String(String(cm_from_ultrasonic_sensor/2.54) + "in away"));

      delay(3000);

      robo_lcd.write_double_line("Playing", "Star Wars");

      robo_dancer.play_star_wars(main_robo_servo);

    } else {
      robo_lcd.write_double_line("Hello, wave for", "a song");

      main_robo_servo.reset();
    }
  }

  delay(1000);
}