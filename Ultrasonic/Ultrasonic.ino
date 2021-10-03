/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 03 Oct 2021 09:29:17 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include "Wire.h"
#include "U8g2lib.h"
#include <Ultrasonic.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
int cm = 0;

int in = 0;

Ultrasonic ultrasonic_6_2(6, 2);

void setup()
{
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);

  u8g2.clearDisplay();
  u8g2.setFont(u8g2_font_unifont_t_chinese1);
}


void loop()
{
  cm = ultrasonic_6_2.convert(ultrasonic_6_2.timing(), Ultrasonic::CM);
  in = ultrasonic_6_2.convert(ultrasonic_6_2.timing(), Ultrasonic::IN);
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 1);
    u8g2.print(String(String("公分: ")+String(cm)).c_str());
    u8g2.setCursor(0, 17);
    u8g2.print(String(String("英吋: ")+String(in)).c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  delay(100);
}