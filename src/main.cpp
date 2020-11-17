/*
   Server Robot
   Author: twooton
   Email: tcwooton@gmail.com
   Description: Simple robot
*/

//#include <Servo.h>
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <IRremote.h>

#define ULTRASONIC_SENSOR_ECHO_DETECT_PIN 8
#define ULTRASONIC_SENSOR_TRIGGER_PIN 9
#define IR_RECEIVER_PIN 7
#define PASSIVE_BUZZER_PIN 6
#define SERVO_PIN 10

#define SENSOR_STOP_SIGNAL 0
#define SENSOR_SEND_SIGNAL 1
#define BUZZER_ON HIGH
#define BUZZER_OFF LOW
#define SENSOR_DISTANCE_IN_RANGE 30
#define SENSOR_DISTANCE_WAY_FAR_AWAY 1000

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Servo servo;

IRrecv irrecv(IR_RECEIVER_PIN);
decode_results results;

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

inline void buzzer_tune_1() {
  tone(PASSIVE_BUZZER_PIN, 400, 100);
  delay(100);
  tone(PASSIVE_BUZZER_PIN, 800, 100);
  delay(100);
  tone(PASSIVE_BUZZER_PIN, 200, 100);
  delay(100);
  tone(PASSIVE_BUZZER_PIN, 400, 50);
  delay(50);
  tone(PASSIVE_BUZZER_PIN, 400, 50);
  delay(50);
  tone(PASSIVE_BUZZER_PIN, 400, 50);
  delay(50);
}

inline void buzzer_tune_2() {
  tone(PASSIVE_BUZZER_PIN, 100, 100);
  delay(100);
  tone(PASSIVE_BUZZER_PIN, 200, 100);
  delay(100);
  tone(PASSIVE_BUZZER_PIN, 200, 100);
  delay(100);
  tone(PASSIVE_BUZZER_PIN, 400, 50);
  delay(50);
  tone(PASSIVE_BUZZER_PIN, 400, 50);
  delay(50);
  tone(PASSIVE_BUZZER_PIN, 800, 100);
  delay(100);
}
/*
inline void reset_servo(Servo& servo) {
  servo.write(90);
}

inline void wave_servo_left(Servo& servo) {
  servo.write(0);
  delay(400);
  servo.write(90);
}*/

void setup()
{
  Serial.begin(9600); // Serial connection with baudrate 960
  pinMode(ULTRASONIC_SENSOR_TRIGGER_PIN, OUTPUT);

  pinMode(ULTRASONIC_SENSOR_ECHO_DETECT_PIN, INPUT);

  /*servo.attach(SERVO_PIN);

  reset_servo(servo);

  servo.write(90);*/

  irrecv.enableIRIn();
}

void loop()
{
  Serial.println("loop");
  
  if (irrecv.decode(&results)) {
    writeLCDDoubleLine(String(String("C: ") + String(results.value)), String(String("Bits: ") + String(results.bits)));
    switch(results.value) {
      case 16724175:
        writeLCDDoubleLine(String("1"), String(""));
        break;
      default:          
        writeLCDDoubleLine(String(String("C: ") + String(results.value)), String(String("Bits: ") + String(results.bits)));
          break;
    }

    Serial.print("C: ");
    Serial.print(results.value, HEX);
    Serial.print(", Bits: ");
    Serial.println(results.bits);
    
    irrecv.resume();
  }
  
  delay(600);

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
/*
      wave_servo_left(servo);

      standard_delay();

      wave_servo_left(servo);

      buzzer_tune_1();

      standard_delay();

      buzzer_tune_2();

      standard_delay();
      */
    } else {
      writeLCDDoubleLine("where did", "they go");

      // reset_servo(servo);
    }
    
  }

  delay(1000);
}
