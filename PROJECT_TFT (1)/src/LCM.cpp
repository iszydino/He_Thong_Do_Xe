#include "LCM.h"
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
#define LCM_COM_IN 16
#define LCM_COM_OUT 17
int last;
int carWidth = 106, carHeight = 106;
int value_1 = 0;
int value_2 = 0;
int prevValue_1 = 0;
int prevValue_2 = 0;
int value_free = 0;
unsigned long prevTime_1 = 0;
unsigned long prevTime_2 = 0;
const unsigned long delayTime = 500;
void TFT_init()
{
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(300, 200);
}
void setup_LCM35()
{
  pinMode(LCM35_1, INPUT);
  pinMode(LCM35_2, INPUT);
  pinMode(LCM35_3, INPUT);
  pinMode(LCM35_4, INPUT);
  pinMode(LCM35_5, INPUT);
  pinMode(LCM35_6, INPUT);
}
void updateLCM()
{
  int freeSpaces = 0;
  int sensorStates[6] = {0};

  // Đọc trạng thái của các cảm biến LCM35
  sensorStates[0] = digitalRead(LCM35_1);
  sensorStates[1] = digitalRead(LCM35_2);
  sensorStates[2] = digitalRead(LCM35_3);
  sensorStates[3] = digitalRead(LCM35_4);
  sensorStates[4] = digitalRead(LCM35_5);
  sensorStates[5] = digitalRead(LCM35_6);

  // Vẽ/xóa hình ảnh dựa trên trạng thái của các cảm biến
  const int spacing = 3; // Khoảng cách giữa các ô
  for (int i = 0; i < 6; i++)
  {
    int x = i % 3 * (carWidth + spacing);
    int y = i / 3 * (carHeight + spacing);
    if (!sensorStates[i] == HIGH)
    {
      tft.drawRGBBitmap(x, y, Car1, carWidth, carHeight);
    }
    else
    {
      tft.fillRect(x, y, carWidth, carHeight, ILI9341_BLUE);
    }
  }

  // Đếm số chỗ trống
  for (int i = 0; i < 6; i++)
  {
    if (sensorStates[i] == 0)
    {
      freeSpaces++;
    }
  }
  value_free = freeSpaces;
  freeSpaces = 6 - freeSpaces;
  // Hiển thị số chỗ trống
  tft.setCursor(0, 220);
  tft.setTextColor (ILI9341_WHITE);
  tft.print("FREE SPACES:");
  unsigned long currentTime = millis();
  if (last != freeSpaces)
  {
    tft.fillRect(143, 220, 20, 20, ILI9341_BLACK);
    tft.print(freeSpaces);
    last = freeSpaces;
  }

  // In ra dấu '||'
  tft.setCursor(163, 220);
  tft.print("||");

  // Kiểm tra và in ra trạng thái
  value_1 = digitalRead(LCM_COM_IN);
  value_2 = digitalRead(LCM_COM_OUT);
  // 500 milliseconds

  if (value_1 != prevValue_1)
  {
    if (millis() - prevTime_1 >= delayTime)
    {
      if (!value_1)
      {
        tft.fillRect(188, 220, 150, 20, ILI9341_BLACK);
        tft.setCursor(190, 220);
        tft.print("CAR OUT<<<");
      }
      else
      {
        tft.fillRect(188, 220, 150, 20, ILI9341_BLACK);
        tft.setCursor(190, 220);
        tft.print("NO CAR");
      }
      prevValue_1 = value_1;
      prevTime_1 = millis();
    }
  }

  if (value_2 != prevValue_2)
  {
    if (millis() - prevTime_2 >= delayTime)
    {
      if (!value_2)
      {
        tft.fillRect(188, 220, 150, 20, ILI9341_BLACK);
        tft.setCursor(190, 220);
        tft.print("CAR IN>>>");
      }
      else
      {
        tft.fillRect(188, 220, 150, 20, ILI9341_BLACK);
        tft.setCursor(190, 220);
        tft.print("NO CAR");
      }
      prevValue_2 = value_2;
      prevTime_2 = millis();
    }
  }
}