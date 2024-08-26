#include <TFT_Setup.h>
#include <LCM.h>
#include <Servo_com.h>
#include <port.h>
#include <blinky.h>
void setup()
{
  TFT_init();
  setup_LCM35();
  Servo_Setup();
  connect_blynk();
  Serial.begin(9600);
}

void loop()
{
  Servo_Com1_Control();// ĐIỀU KHIỂN SERVO MỞ CỔNG 
  Servo_Com2_Control();//ĐIỀU KIỂN SERVO ĐÓNG CỔNG 
  updateLCM();// CẬP NHẬT VỊ TRÍ CÓ/KHÔNG XE 
  truyendulieu_blynk();
  xuatdulieu_blynk();
}