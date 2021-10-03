/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 03 Oct 2021 09:01:24 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Wire.h>
#include "U8g2lib.h"
#include <adxl345_blockly.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
ADXL345Block adxl345;

void setup()
{
  Serial.begin(9600);

  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);

  u8g2.setFont(u8g2_font_unifont_t_chinese1);
  adxl345.begin();
}


void loop()
{
  Serial.println((String("X: ")+String(adxl345.getX())));
  Serial.println((String("Y: ")+String(adxl345.getY())));
  Serial.println((String("Z: ")+String(adxl345.getZ())));
  Serial.println((String("俯仰: ")+String(adxl345.getPitch())));
  Serial.println((String("翻滾: ")+String(adxl345.getRoll())));
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 1);
    u8g2.print(String("EZ Starter Kit+").c_str());
    u8g2.setCursor(0, 17);
    u8g2.print(String(String("X:")+String(adxl345.getX())).c_str());
    u8g2.setCursor(0, 33);
    u8g2.print(String(String("Y:")+String(adxl345.getY())).c_str());
    u8g2.setCursor(0, 49);
    u8g2.print(String(String("Z:")+String(adxl345.getZ())).c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  delay(500);
}