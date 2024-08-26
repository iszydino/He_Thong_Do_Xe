#include <Servo_com.h>

#define LCM_COM1 16
#define LCM_COM2 17
#define Servo_Pin1 21
#define Servo_Pin2 22
#define Buzzers 13

Servo Servo_Com1;
Servo Servo_Com2;

bool Value_Com1, Value_Com2;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long openMillis1 = 0;
unsigned long openMillis2 = 0;
const long interval = 50;      // Khoảng thời gian cập nhật servo (50ms)
const long openDelay = 2000;   // Delay mở servo (2 giây)
const long debounceDelay = 20; // Delay chống rung

void Servo_Setup()
{
  Servo_Com1.attach(Servo_Pin1);
  Servo_Com2.attach(Servo_Pin2);
  pinMode(LCM_COM1, INPUT);
  pinMode(LCM_COM2, INPUT);
  pinMode(Buzzers, OUTPUT);
}

void buzzer()
{
  digitalWrite(Buzzers, HIGH);
  delay(200); // Tăng delay để tiếng buzzer không quá ngắn
  digitalWrite(Buzzers, LOW);
}

int oldState1 = HIGH, currentState1 = HIGH;
int oldState2 = HIGH, currentState2 = HIGH;

void Servo_Com1_Control()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis1 >= interval)
  {
    previousMillis1 = currentMillis;

    oldState1 = currentState1;
    currentState1 = digitalRead(LCM_COM1);

    if (currentState1 == LOW && oldState1 == HIGH)
    {
      buzzer();
    }

    if (currentState1 == LOW)
    {
      Servo_Com1.write(180);
      openMillis1 = currentMillis;
      Value_Com1 = false;
    }
    else
    {
      if (currentMillis - openMillis1 >= openDelay)
      {
        Servo_Com1.write(90);
        Value_Com1 = true;
      }
    }
  }
}

void Servo_Com2_Control()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis2 >= interval)
  {
    previousMillis2 = currentMillis;

    oldState2 = currentState2;
    currentState2 = digitalRead(LCM_COM2);

    if (currentState2 == LOW && oldState2 == HIGH)
    {
      buzzer();
    }

    if (currentState2 == LOW)
    {
      Servo_Com2.write(100);
      openMillis2 = currentMillis;
      Value_Com2 = false;
    }
    else
    {
      if (currentMillis - openMillis2 >= openDelay)
      {
        Servo_Com2.write(180);
        Value_Com2 = true;
      }
    }
  }
}