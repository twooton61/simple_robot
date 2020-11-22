#ifndef ROBO_SERVO_H
#define ROBO_SERVO_H

#include <Arduino.h>

class RoboServo {
  const int m_pin = 0;
  Servo m_servo;

  public:
  RoboServo(const int pin) :
    m_pin(pin)
  {
  }

  inline void setup() {
    m_servo.attach(m_pin);

    reset();
  }

  inline void reset() {
    m_servo.write(90);
  }

  inline void wave_left() {
    m_servo.write(0);
  }

  inline void wave_right() {
    m_servo.write(90);
  }
};

#endif