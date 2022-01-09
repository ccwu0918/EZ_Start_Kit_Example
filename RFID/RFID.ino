/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 06 Jan 2022 19:01:02 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include "Wire.h"
#include "U8g2lib.h"
#include <SPI.h>

#include <MFRC522.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
MFRC522 rfid(/*SS_PIN*/ 10, /*RST_PIN*/ UINT8_MAX);

String mfrc522_readID_nostop()
{
  String ret;
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
  {
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

    for (byte i = 0; i < rfid.uid.size; i++) {
      ret += (rfid.uid.uidByte[i] < 0x10 ? "0" : "");
      ret += String(rfid.uid.uidByte[i], HEX);
    }
  }
  return ret;
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
  u8g2.setFont(u8g2_font_unifont_t_chinese1);
  SPI.begin();
  rfid.PCD_Init();

}


void loop()
{
  String RfidNo = mfrc522_readID_nostop();
  if (RfidNo != "") {
    Serial.println((String("RFID: ")+String(RfidNo)));
    u8g2.clearDisplay();
    u8g2.firstPage();
    do {
      u8g2.setCursor(0, 0);
      u8g2.print(String("RFID: ").c_str());
      u8g2.setCursor(0, 16);
      u8g2.print(String(RfidNo).c_str());

      u8g2.sendBuffer();
    } while (u8g2.nextPage());
  }
  delay(1000);
}