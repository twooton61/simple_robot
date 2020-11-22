#ifndef ROBO_LCD_H
#define ROBO_LCD_H

class RoboLCD {
  LiquidCrystal m_lcd;

  public:
  RoboLCD(int rs, int enable,
    int d0, int d1, int d2, int d3) :
    m_lcd(rs, enable, d0, d1, d2, d3)
  {
  }

  inline void write_double_line(String line1, String line2) {
    m_lcd.begin(16, 2);
    m_lcd.print(line1);
    m_lcd.setCursor(0, 1);
    m_lcd.print(line2);
  }
};

#endif