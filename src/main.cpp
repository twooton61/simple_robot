/*
   Server Robot
   Author: twooton
   Email: tcwooton@gmail.com
   Description: Simple Robot
*/

#include <Arduino.h>
#include <Helpers.h>
#include <RoboServo.h>
#include <RoboLCD.h>
#include <RoboDancer.h>
#include <RoboUltrasonicSensor.h>

RoboServo main_robo_servo(DIGITAL_IO_PIN(10));

RoboDancer robo_dancer(main_robo_servo, DIGITAL_IO_PIN(6));

RoboUltrasonicSensor robo_ultrasonice_sensor(DIGITAL_IO_PIN(8), DIGITAL_IO_PIN(9));

RoboLCD robo_lcd(
  DIGITAL_IO_PIN(12),
  DIGITAL_IO_PIN(11),
  DIGITAL_IO_PIN(5),
  DIGITAL_IO_PIN(4),
  DIGITAL_IO_PIN(3),
  DIGITAL_IO_PIN(2)
);

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

  if (cm_from_ultrasonic_sensor <= CENTIMETERS(1000)) {

    if (cm_from_ultrasonic_sensor == 0) {
      Serial.println("sensor error, reading 0 distance");
    }
    else if (cm_from_ultrasonic_sensor <= CENTIMETERS(30))
    {
      robo_lcd.write_double_line("Motion Detected", String(String(CENTIMETERS_TO_INCHES(2.54)) + "in away"));

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