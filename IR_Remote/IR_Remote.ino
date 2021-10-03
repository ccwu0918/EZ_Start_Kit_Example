/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sat, 02 Oct 2021 15:29:02 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include "Wire.h"
#include "U8g2lib.h"
#include <IRremote.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
IRrecv irrecv(17);
decode_results results;
String myCodeType;
String myIRcode;
String ir_type(int tip)
{
  if (tip == 1){
    return "RC5";
  } else if (tip == 2){
    return "RC6";
  } else if (tip == 3){
    return "NEC";
  } else if (tip == 4){
    return "SONY";
  } else if (tip == 5){
    return "PANASONIC";
  } else if (tip == 6){
    return "JVC";
  } else if (tip == 7){
    return "SAMSUNG";
  } else if (tip == 10){
    return "LG";
  } else if (tip == 14){
    return "SHARP";
  } else if (tip == 17){
    return "LEGO_PF";
  } else {
    return "UNKNOWN";
  }
}

void setup()
{
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);

  irrecv.enableIRIn();

  u8g2.clearDisplay();
}


void loop()
{
  if (irrecv.decode(&results)) {
    if (results.decode_type>0){
      myCodeType=ir_type(results.decode_type);
      myIRcode=String(results.value, HEX);
      u8g2.firstPage();
      do {
        u8g2.setCursor(0, 0);
        u8g2.print(String(String("Code: ")+String(myIRcode)).c_str());
        u8g2.setCursor(0, 10);
        u8g2.print(String(String("Type: ")+String(myCodeType)).c_str());

        u8g2.sendBuffer();
      } while (u8g2.nextPage());
      delay(100);
    }
    irrecv.resume();
  }
}