/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Fri, 01 Oct 2021 15:23:09 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include "Wire.h"
#include "U8g2lib.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;

void setup()
{
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);


}


void loop()
{
  u8g2.setFont(u8g2_font_unifont_t_chinese1);
  u8g2.firstPage();
  do {
    u8g2.setCursor(30, 1);
    u8g2.print(String("中文顯示").c_str());
    u8g2.drawLine(30, 17, 93, 17);
    u8g2.setCursor(5, 30);
    u8g2.print(String("中文字顯示測試").c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  delay(2000);
  u8g2.setFont(u8g2_font_6x10_mf);
  u8g2.firstPage();
  do {
    u8g2.setCursor(39, 1);
    u8g2.print(String("English").c_str());
    u8g2.drawLine(39, 12, 80, 12);
    u8g2.setCursor(5, 30);
    u8g2.print(String("English Display Test").c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  delay(2000);
}