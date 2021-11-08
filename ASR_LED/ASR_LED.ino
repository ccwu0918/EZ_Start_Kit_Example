/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 07 Nov 2021 18:15:23 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Wire.h>
#include "U8g2lib.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
String message = "";

uint8_t asr_value=0;
uint8_t checkASR(byte asrAddress){
  uint8_t myASRvalue=0;
  Wire.setClock(100000);
  Wire.requestFrom(asrAddress,1,true);
  if (Wire.available()){
    myASRvalue=Wire.read();
  }
  return myASRvalue;
}
void asrSet(byte asrAddress, byte myData){
  Wire.setClock(100000);
  Wire.beginTransmission(asrAddress);
  Wire.write(myData);
  Wire.endTransmission();
}

byte A_Pin=0;
byte B_Pin=7;
char myBtnStatus;
bool buttonPressed(char btnName)
{
  if (btnName=='A'){
    if (digitalRead(A_Pin) == 1)
      return false;
    else
      return true;
  }
  else if (btnName=='B'){
    if (digitalRead(B_Pin) == 1)
      return false;
    else
      return true;
  } else {
    if ((digitalRead(A_Pin) == 1) && (digitalRead(B_Pin) == 1))
      return false;
    else
      return true;
  }
}

char getBtnStatus(){
  char buttonStatus=' ';
  int checkButtonDelay=200;
  if (buttonPressed('A')){
    delay(checkButtonDelay);
    if (buttonPressed('A')){
      buttonStatus='A';
      if (buttonPressed('B'))
        buttonStatus='C';
    }
  } else if (buttonPressed('B')){
      delay(checkButtonDelay);
      if (buttonPressed('B')){
        buttonStatus='B';
        if (buttonPressed('A'))
          buttonStatus='C';
      }
  }
  return buttonStatus;
}

byte r_pin=13;
byte y_pin=12;
byte g_pin=11;

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
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 1);
    u8g2.print(String("請說「您好小恩」").c_str());
    u8g2.setCursor(0, 17);
    u8g2.print(String("啟動語音辨識").c_str());
    u8g2.setCursor(0, 33);
    u8g2.print(String("A:學習 B:清除").c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  Wire.begin();
  pinMode(A_Pin, INPUT);
  pinMode(B_Pin, INPUT);
  pinMode(r_pin, OUTPUT);
  pinMode(y_pin, OUTPUT);
  pinMode(g_pin, OUTPUT);
}


void loop()
{
  myBtnStatus=getBtnStatus();
  if (myBtnStatus=='A'){
    asrSet(0x0B, 0x50);
    while(buttonPressed('A')){}
  }
  if (myBtnStatus=='B'){
    asrSet(0x0B, 0x60);
    while(buttonPressed('B')){}
  }
  asr_value=checkASR(0x0B);
  if (asr_value==80) {
    digitalWrite(r_pin, HIGH);
    message = "紅燈已開啟";
  } else if (asr_value==81) {
    digitalWrite(r_pin, LOW);
    message = "紅燈已關閉";
  } else if (asr_value==82) {
    digitalWrite(y_pin, HIGH);
    message = "黃燈已開啟";
  } else if (asr_value==83) {
    digitalWrite(y_pin, LOW);
    message = "黃燈已關閉";
  } else if (asr_value==84) {
    digitalWrite(g_pin, HIGH);
    message = "綠燈已開啟";
  } else if (asr_value==85) {
    digitalWrite(g_pin, LOW);
    message = "綠燈已關閉";
  }
  if (message != "") {
    u8g2.clearDisplay();
    u8g2.firstPage();
    do {
      u8g2.setCursor(0, 1);
      u8g2.print(String(message).c_str());

      u8g2.sendBuffer();
    } while (u8g2.nextPage());
    message = "";
  }
}