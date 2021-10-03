/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 03 Oct 2021 14:42:47 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Wire.h>
#include "U8g2lib.h"
#include "MAX30105.h"
#include "heartRate.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
#define FINGER_ON 7000
#define MINIMUM_SPO2 90.0
boolean max3010xReady=false;
double avgRed=0, avgIR=0, ESpO2 = MINIMUM_SPO2;
const double FSpO2 = 0.7, frate = 0.95;
byte validMin=20, validMax=250;
MAX30105 max3010xSensor;

int getHeartBeat(byte avgTimes)
{
  long lastBeat=0, myIRvalue=0, delta=0;
  byte myCount=0;
  int beatSum=0;
  float myBPM=0.0;
  while(myCount<avgTimes){
    myIRvalue=max3010xSensor.getIR();
    if (checkForBeat(myIRvalue)) {
      delta = millis() - lastBeat;
      lastBeat = millis();
      myBPM = 60 / (delta / 1000.0);
      if (myBPM < validMax && myBPM > validMin) {
        beatSum+=( (byte)myBPM);
        myCount++;
      }
    }
    if (myIRvalue < FINGER_ON )
      break;
  }
  if (myCount==0)
    myCount=1;
  return(beatSum/myCount);
}

double getSPO2(byte avgTimes)
{
  uint32_t ir,red;
  double df_red,df_ir;
  byte myCount=0;
  double sumIR = 0, sumRed = 0, SpO2 = 0;
  while(myCount<avgTimes){
    max3010xSensor.check();
    if (max3010xSensor.available()) {
      myCount++;
      red = max3010xSensor.getFIFOIR();
      ir = max3010xSensor.getFIFORed();
      max3010xSensor.nextSample();
      df_red = (double)red;
      df_ir = (double)ir;
      avgRed = avgRed * frate + (double)red * (1.0 - frate);
      avgIR = avgIR * frate + (double)ir * (1.0 - frate);
      sumRed += (df_red - avgRed) * (df_red - avgRed);
      sumIR += (df_ir - avgIR) * (df_ir - avgIR);
    }
  }
  if (myCount==avgTimes){
    double R = (sqrt(sumRed) / avgRed) / (sqrt(sumIR) / avgIR);
    SpO2 = -23.3 * (R - 0.4) + 100;
    ESpO2 = FSpO2 * ESpO2 + (1.0 - FSpO2) * SpO2;
    if (ESpO2 <= MINIMUM_SPO2)
      ESpO2 = MINIMUM_SPO2;
    if (ESpO2 > 100)
      ESpO2 = 99.9;
  } else {
      ESpO2 = MINIMUM_SPO2;
  }
  return ESpO2;
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

  max3010xReady=max3010xSensor.begin(Wire, I2C_SPEED_FAST);
  max3010xSensor.setup(127, 4, 2, 800, 215, 16384);
  max3010xSensor.enableDIETEMPRDY();
  max3010xSensor.setPulseAmplitudeRed(0x0A);
  max3010xSensor.setPulseAmplitudeGreen(0);

  u8g2.setFont(u8g2_font_unifont_t_chinese1);
  validMin=20;
  validMax=250;
}


void loop()
{
  if ((max3010xSensor.getIR()>FINGER_ON)) {
    u8g2.firstPage();
    do {
      u8g2.setCursor(10, 5);
      u8g2.print(String(String("心率: ")+String(getHeartBeat(1))+String(" BPM")).c_str());
      u8g2.setCursor(10, 25);
      u8g2.print(String(String("血氧: ")+String(getSPO2(30))+String(" %")).c_str());
      u8g2.setCursor(10, 45);
      u8g2.print(String(String("溫度: ")+String(max3010xSensor.readTemperature())+String(" C")).c_str());

      u8g2.sendBuffer();
    } while (u8g2.nextPage());
  } else {
    u8g2.firstPage();
    do {
      u8g2.setCursor(0, 1);
      u8g2.print(String("EZ Starter Kit+").c_str());
      u8g2.setCursor(0, 45);
      u8g2.print(String(" 心率血氧溫度感測").c_str());
      u8g2.setCursor(0, 45);
      u8g2.print(String("請將手指放上感測器").c_str());

      u8g2.sendBuffer();
    } while (u8g2.nextPage());
    avgRed = 0;
    avgIR = 0;
    ESpO2 = MINIMUM_SPO2;
  }
}