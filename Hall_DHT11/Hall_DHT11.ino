/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 03 Oct 2021 07:39:59 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include "Wire.h"
#include "U8g2lib.h"
#include <DHT.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
int alarm = 0;

DHT dht11_p10(10, DHT11);

void setup()
{
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);

  u8g2.setFont(u8g2_font_unifont_t_chinese1);
  dht11_p10.begin();
  pinMode(2, INPUT);
}


void loop()
{
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 1);
    u8g2.print(String("EZ Starter Kit+").c_str());
    u8g2.setCursor(0, 17);
    u8g2.print(String(String("DHT溫度: ")+String(dht11_p10.readTemperature())).c_str());
    u8g2.setCursor(0, 33);
    u8g2.print(String(String("DHT溼度: ")+String(dht11_p10.readHumidity())).c_str());
    u8g2.setCursor(0, 49);
    u8g2.print(String(String("Hall偵測: ")+String(digitalRead(2))).c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
}