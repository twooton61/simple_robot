#ifndef RoboDancer_H
#define RoboDancer_H

#include <Arduino.h>
#include <RoboBrain.h>
#include <AbstractRoboPart.h>
#include <RoboServo.h>
#include <BuzzerNote.h>

class RoboDancer : AbstractRoboPart {
  static const int BUZZER_ON = HIGH;
  static const int BUZZER_OFF = LOW;

  RoboServo& m_servo;
  int m_passive_buzzer_pin;
  int m_note_count = 0;

  public:

  RoboDancer(RoboBrain& robo_brain, RoboServo& servo, const int buzzer_pin) :
    m_servo(servo),
    m_passive_buzzer_pin(buzzer_pin)
  {
    robo_brain.add_part(this);
  }

  void setup() {
      pinMode(m_passive_buzzer_pin, OUTPUT);
  }

  inline void play_note(const int note, const int duration)
  {
    tone(m_passive_buzzer_pin, note, duration);

    if(m_note_count++ % 2 == 0)
    {
      m_servo.wave_left();
    }
    else
    {
      m_servo.wave_right();
    }

    delay(duration);

    noTone(m_passive_buzzer_pin);

    delay(50);
  }

  inline void play_star_wars(RoboServo& main_servo) {
    play_note(BuzzerNote::a, 500);
    play_note(BuzzerNote::a, 500);
    play_note(BuzzerNote::a, 500);
    play_note(BuzzerNote::f, 350);
    play_note(BuzzerNote::cH, 150);
    play_note(BuzzerNote::a, 500);
    play_note(BuzzerNote::f, 350);
    play_note(BuzzerNote::cH, 150);
    play_note(BuzzerNote::a, 650);

    delay(500);

    play_note(BuzzerNote::eH, 500);
    play_note(BuzzerNote::eH, 500);
    play_note(BuzzerNote::eH, 500);
    play_note(BuzzerNote::fH, 350);
    play_note(BuzzerNote::cH, 150);
    play_note(BuzzerNote::gS, 500);
    play_note(BuzzerNote::f, 350);
    play_note(BuzzerNote::cH, 150);
    play_note(BuzzerNote::a, 650);

    delay(500);

    play_note(BuzzerNote::aH, 500);
    play_note(BuzzerNote::a, 300);
    play_note(BuzzerNote::a, 150);
    play_note(BuzzerNote::aH, 500);
    play_note(BuzzerNote::gSH, 325);
    play_note(BuzzerNote::gH, 175);
    play_note(BuzzerNote::fSH, 125);
    play_note(BuzzerNote::fH, 125);
    play_note(BuzzerNote::fSH, 250);

    delay(325);

    play_note(BuzzerNote::aS, 250);
    play_note(BuzzerNote::dSH, 500);
    play_note(BuzzerNote::dH, 325);
    play_note(BuzzerNote::cSH, 175);
    play_note(BuzzerNote::cH, 125);
    play_note(BuzzerNote::b, 125);
    play_note(BuzzerNote::cH, 250);

    delay(350);

    play_note(BuzzerNote::f, 250);
    play_note(BuzzerNote::gS, 500);
    play_note(BuzzerNote::f, 375);
    play_note(BuzzerNote::cH, 125);
    play_note(BuzzerNote::a, 500);
    play_note(BuzzerNote::f, 375);
    play_note(BuzzerNote::cH, 125);
    play_note(BuzzerNote::a, 650);

    delay(650);
  }
};

#endif