#ifndef ROBO_ULTRASONIC_SENSOR_H
#define ROBO_ULTRASONIC_SENSOR_H

#include <Arduino.h>
#include <AbstractRoboPart.h>
#include <RoboBrain.h>

class RoboUltrasonicSensor : AbstractRoboPart {
  static const int STOP_SIGNAL = 0;
  static const int SEND_SIGNAL = 1;

  const int m_sensor_echo_detect_pin;
  const int m_sensor_trigger_pin;

  public:
  RoboUltrasonicSensor(RoboBrain& robo_brain, const int sensor_echo_detect_pin, const int sensor_trigger_pin) :
    m_sensor_echo_detect_pin(sensor_echo_detect_pin),
    m_sensor_trigger_pin(sensor_trigger_pin)
  {
      robo_brain.add_part(this);
  }

  inline void setup() override {
    pinMode(m_sensor_echo_detect_pin, INPUT);

    pinMode(m_sensor_trigger_pin, OUTPUT);
  }

  inline unsigned long get_cm_from_sensor() {
    digitalWrite(m_sensor_trigger_pin, STOP_SIGNAL);
    delayMicroseconds(2);
    digitalWrite(m_sensor_trigger_pin, SEND_SIGNAL);
    delayMicroseconds(10);
    digitalWrite(m_sensor_trigger_pin, STOP_SIGNAL);

    const unsigned long duration = pulseIn(m_sensor_echo_detect_pin, HIGH);

    return int(duration / 2 / 29.412);
  }
};

#endif