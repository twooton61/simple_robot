#ifndef ROBO_SERVO_H
#define ROBO_SERVO_H

#include <Arduino.h>
#include <Servo.h>
#include <RoboBrain.h>
#include <AbstractRoboPart.h>

class RoboServo : AbstractRoboPart {
  const int m_pin = 0;
  Servo m_servo;

  public:
  RoboServo(RoboBrain& robo_brain, const int pin) :
    m_pin(pin)
  {
    robo_brain.add_part(this);
  }

  inline void setup() override {
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