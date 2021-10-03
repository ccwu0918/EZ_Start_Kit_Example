/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sat, 02 Oct 2021 10:11:53 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel plusPixels = Adafruit_NeoPixel(3,4,NEO_GRB + NEO_KHZ800);

void setup()
{
  plusPixels.begin();
  plusPixels.setBrightness(30);
  plusPixels.show();
  plusPixels.setPixelColor(0,plusPixels.Color(0,0,0));
  plusPixels.setPixelColor(1,plusPixels.Color(0,0,0));
  plusPixels.setPixelColor(2,plusPixels.Color(0,0,0));
  plusPixels.show();

}


void loop()
{
  for (int i = 0; i <= 2; i++) {
    plusPixels.setPixelColor(i,plusPixels.Color(255,0,0));
    plusPixels.show();
  }
  delay(500);
  for (int i = 0; i <= 2; i++) {
    plusPixels.setPixelColor(i,plusPixels.Color(51,255,51));
    plusPixels.show();
  }
  delay(500);
  for (int i = 0; i <= 2; i++) {
    plusPixels.setPixelColor(i,plusPixels.Color(51,51,255));
    plusPixels.show();
  }
  delay(500);
}