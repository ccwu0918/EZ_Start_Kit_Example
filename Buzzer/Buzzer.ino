/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sat, 02 Oct 2021 07:35:08 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel plusPixels = Adafruit_NeoPixel(3,4,NEO_GRB + NEO_KHZ800);

byte buzz_pin=14;

void setup()
{
  plusPixels.begin();
  plusPixels.setBrightness(30);
  plusPixels.show();
  plusPixels.setPixelColor(0,plusPixels.Color(0,0,0));
  plusPixels.setPixelColor(1,plusPixels.Color(0,0,0));
  plusPixels.setPixelColor(2,plusPixels.Color(0,0,0));
  plusPixels.show();
  plusPixels.show();
}


void loop()
{
  tone(buzz_pin, 262);
  delay(300);
  tone(buzz_pin, 330);
  delay(300);
  tone(buzz_pin, 392);
  delay(300);
  noTone(14);
  delay(3000);
}