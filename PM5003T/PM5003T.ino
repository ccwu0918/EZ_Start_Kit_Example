/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 09 Jan 2022 21:20:13 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include "Wire.h"
#include "U8g2lib.h"
#include <SoftwareSerial.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
SoftwareSerial pms5003tSerial(3, 0);
long pmat10_ = 0;
long pmat25_ = 0;
long pmat100_ = 0;
long Temp_ = 0;
long Humid_ = 0;
char buf[50];

void retrievepm25(){
  int count = 0;
  unsigned char c;
  unsigned char high;
  while (pms5003tSerial.available()) {
     c = pms5003tSerial.read();
     if((count==0 && c!=0x42) || (count==1 && c!=0x4d)){
       break;
     }
     if(count > 27){
       break;
     }
      else if(count == 10 || count == 12 || count == 14 || count == 24 || count == 26) {
       high = c;
     }
     else if(count == 11){
       pmat10_ = 256*high + c;
     }
     else if(count == 13){
       pmat25_ = 256*high + c;
     }
     else if(count == 15){
       pmat100_ = 256*high + c;
     }
      else if(count == 25){
          Temp_ = (256*high + c)/10;
     }
     else if(count == 27){
                  Humid_ = (256*high + c)/10;
    }       count++;
  }  while(pms5003tSerial.available()) pms5003tSerial.read();
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

  Serial.begin(9600);

  u8g2.clearDisplay();
  pms5003tSerial.begin(9600);

}


void loop()
{
  retrievepm25();
  u8g2.clearDisplay();
  u8g2.setFont(u8g2_font_6x10_mf);
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 0);
    u8g2.print(String(String("PM10: ")+String(pmat10_)).c_str());
    u8g2.setCursor(0, 12);
    u8g2.print(String(String("PM100: ")+String(pmat100_)).c_str());
    u8g2.setCursor(0, 24);
    u8g2.print(String(String("PM25: ")+String(pmat25_)).c_str());
    u8g2.setCursor(0, 36);
    u8g2.print(String(String("Temp: ")+String(Temp_)).c_str());
    u8g2.setCursor(0, 48);
    u8g2.print(String(String("Humid: ")+String(Humid_)).c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
}