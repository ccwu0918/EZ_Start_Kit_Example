/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 03 Oct 2021 16:29:54 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include "Wire.h"
#include "U8g2lib.h"
#include "StringSplitter.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
String image[1] = "FF,FF,FF,FF,FF,FF,FF,FF,FF,FF,FF,FF, F8,FF,FF,FF,FF,FF,FF,FF,FF,FF,FF,FF, FF,FF,FF,7F,E0,FF,FF,FF,FF,FF,FF,FF, FF,FF,FF,FF,FF,FF,FF,81,03,F8,FF,FF, FF,FF,FF,FF,FF,FF,FF,FF,FF,FF,3F,FC, C2,C1,FF,FF,FF,B7,FF,BF,FF,FF,FF,FF, FF,FF,87,BF,F3,9F,FF,FF,FF,83,3F,00, FF,F3,3F,FF,FF,FF,F3,CF,F9,3F,FF,FF, 3F,F4,7F,B7,FF,0B,BF,07,FE,FF,FD,F7, F8,7F,FE,FF,BF,EF,7F,A3,7F,F0,DF,DC, FF,FF,FE,FB,FC,FF,FC,FF,BF,68,7F,B8, BF,FB,1F,DE,FF,7F,FF,79,FE,FF,F9,FF, 3F,6F,7F,C5,FF,FB,DF,5E,FC,9F,FF,3D, FE,FF,F3,FF,5F,98,7F,DD,FF,C3,5F,82, FD,CF,FF,3E,FF,FF,F7,FF,5F,93,7F,C0, FF,F8,9F,D7,FE,E7,FF,9E,FF,FF,E7,FF, 5F,9D,7F,FF,FF,FF,DF,D5,FE,E7,7F,CE, FF,FF,CF,FF,EF,AE,FD,77,FE,07,1F,94, FE,F3,7F,E7,FF,FF,CF,FF,EF,BD,BD,EF, 7D,B8,DF,56,FF,F9,7F,F7,FF,FF,9F,FF, 1F,4B,BD,DE,7D,9F,DF,DC,FF,F9,7F,FB, FF,FF,9F,FF,5F,D7,DC,BD,7F,DF,1F,DF, FF,FC,BF,FF,FF,FF,BF,FF,DF,F0,CC,C3, FF,02,FF,DF,FF,C4,B7,FF,FF,FF,BF,FF, FF,FF,FF,FF,FF,FF,FF,FF,7F,38,BA,03, F0,FF,BF,FF,FF,FF,FF,FF,FF,FF,FF,FF, BF,BF,79,3C,F0,FF,BF,FF,FF,FF,FF,FF, FF,FF,FF,FF,DF,9F,C3,07,F8,FF,3F,FF, FF,FF,FF,FF,FF,FF,FF,FF,9F,03,C3,F1, F8,FF,3F,FF,7F,CD,FF,EE,FF,FF,FF,FF, CF,3C,01,FF,F3,FF,7F,FF,6F,89,FF,85, FF,FC,CF,FF,4F,E3,80,FF,EF,FF,7F,FF, 6F,94,3F,F0,FF,C2,EF,81,67,9D,DF,3F, BE,FF,7F,FF,CF,09,FF,F1,1F,FC,37,F7, A7,BE,C3,FF,7C,FF,7F,FF,33,24,DB,F9, EF,FE,87,F7,B7,FE,BF,FF,F2,FE,7F,FF, 5F,B1,83,C1,FF,FE,B7,17,57,FF,C7,3F, EF,FD,7F,FF,A7,C2,5B,DA,FF,F0,97,60, 53,9F,BF,3F,DF,FD,7F,FF,EF,DE,DB,C2, 3F,FE,E7,B5,5B,9F,C7,3F,DF,F8,7F,FF, C3,C2,8B,FC,FF,FF,77,B5,EB,FE,F0,FF, 0F,FA,7F,FF,DF,C6,F7,E1,FF,C1,07,A5, E9,78,70,FF,83,F7,7F,FF,C3,DA,7F,7C, 1F,EE,B7,D5,ED,00,38,FE,C1,F7,7F,FE, DB,82,FF,81,DF,E7,37,F7,75,C0,19,00, E0,F7,7F,FE,C3,C8,1F,CE,DF,F7,C7,F7, 34,7F,F8,1F,F8,EF,FF,FE,F7,9D,FF,3E, BF,C0,FF,F7,D6,7F,F8,7F,FC,EF,FF,FE, FF,FF,7F,7F,FF,FF,FF,FF,DA,7F,F8,FF, F6,EF,FF,FC,FF,FF,FF,FF,FF,FF,FF,FF, 9A,3F,F0,7F,F3,EF,FF,FD,FF,FF,FF,FF, 07,FE,80,7F,BA,1F,86,BF,F1,C7,FF,F9, 1F,F8,FF,F8,F3,FC,BE,7F,7B,CF,1F,BE, F0,D9,FF,FB,DF,FB,7F,FE,FB,FC,BE,7F, 7B,77,3D,B8,78,DE,FF,FB,DF,FB,3F,FF, FB,FE,BE,7F,7D,71,59,B0,B8,DF,FF,F3, DF,FB,1F,F8,73,FE,9E,7F,7D,38,59,20, CC,9F,FF,F7,DF,FB,DF,F3,07,FE,DF,3F, 7D,2C,C9,20,F3,BF,FF,E7,FF,FB,DF,E7, FF,FE,DF,BF,7D,26,49,C1,FC,BF,FF,EF, FF,FB,DF,EF,FF,FE,DF,BF,7D,92,64,36, FF,BF,FF,EF,FF,FD,3F,F0,FF,FE,DF,BF, BE,00,00,2C,00,BF,FF,CF,FF,FD,FF,FF, FF,FF,FF,BF,9E,E1,07,C4,FF,BF,FF,DF, FF,FD,EF,FF,6F,ED,9F,B0,9E,FE,FF,87, FF,7F,FF,9F,FF,FD,DF,C7,83,F1,A7,76, 7E,FC,FF,0B,F0,FF,E0,BF,FF,FF,9F,D8, E7,E2,B7,72,FF,F8,FF,F0,00,FE,C7,BF, FF,FF,E7,DB,57,E7,C7,7C,FF,F3,7F,FE, 3F,F8,1F,3F,FF,FF,EF,DD,93,E9,FF,70, FE,CF,7F,FF,7F,F0,7F,7C,FF,FF,1F,E5, A7,E1,07,F7,F9,9F,BF,FF,7F,F0,FF,79, FF,FF,E3,EE,87,ED,6F,F9,F3,7F,BE,FF, FF,F0,FF,63,FF,FF,EF,CF,B7,E1,0F,FA, C7,FF,DC,FF,FF,F0,FF,CF,FF,FF,97,90, 87,EF,6F,F9,9F,FF,E1,FF,7F,F0,FF,9F, FF,FF,EB,DD,57,E8,1F,FE,3F,FE,F3,FF, 7F,F2,FF,3F,FF,FF,E3,8D,B7,EB,6F,FF, FF,F8,FF,FF,3F,F7,FF,BF,FF,FF,1D,F5, 37,EC,7F,80,FF,83,FF,FF,3F,EF,FF,BF, FF,FF,FD,F8,B7,ED,03,FF,FF,3F,FF,FF, 7F,DF,FF,9F,FF,FF,FF,87,37,EE,7F,FF, FF,7F,FE,FF,7F,9F,FF,C7,FF,FF,FF,FF, FF,CF,7F,FF,FF,FF,FC,FF,3F,1E,00,F0, FF,FF,FF,FF,FF,FF,FF,FF,FF,FF,01,FF, 81,C0,FF,FF,";

void showXBM(String myXBM,unsigned char *myBitMap){
    myXBM.replace(" ","");
    myXBM.replace("\r","");
    myXBM.replace("\n","");
    StringSplitter *splitter = new StringSplitter(myXBM, ',', 1024);
    for(int i = 0; i < 1024; i++){
      myBitMap[i]= 0;
    }
    for(int i = 0; i < splitter->getItemCount(); i++){
      splitter->getItemAtIndex(i)="0x"+splitter->getItemAtIndex(i);
      myBitMap[i]= strtol(splitter->getItemAtIndex(i).c_str(), 0, 16);
    }
    delete splitter;
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

  u8g2.clearDisplay();
}


void loop()
{
  u8g2.setDrawColor(1);
  u8g2.firstPage();
  do {
    unsigned char xBitMap[1024];
    showXBM((image[0]),xBitMap);
    u8g2.clearBuffer();
    u8g2.drawXBMP(0, 0, 128, 64, xBitMap);

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  delay(500);
  u8g2.setDrawColor(0);
  u8g2.firstPage();
  do {
    unsigned char xBitMap[1024];
    showXBM((image[0]),xBitMap);
    u8g2.clearBuffer();
    u8g2.drawXBMP(0, 0, 128, 64, xBitMap);

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  delay(500);
}