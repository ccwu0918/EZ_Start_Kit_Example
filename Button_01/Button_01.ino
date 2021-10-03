/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sat, 02 Oct 2021 07:15:05 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel plusPixels = Adafruit_NeoPixel(3,4,NEO_GRB + NEO_KHZ800);

byte buzz_pin=14;

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
  pinMode(A_Pin, INPUT);
  pinMode(B_Pin, INPUT);
}


void loop()
{
  myBtnStatus=getBtnStatus();
  if (myBtnStatus=='A'){
    tone(buzz_pin, 262);
    while(buttonPressed('A')){}
  }
  if (myBtnStatus=='B'){
    tone(buzz_pin, 294);
    while(buttonPressed('B')){}
  }
  if (myBtnStatus=='C'){
    noTone(buzz_pin);
    while(buttonPressed('C')){}
  }
}