/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sat, 02 Oct 2021 10:03:37 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


byte r_pin=13;
byte y_pin=12;
byte g_pin=11;

void setup()
{

  pinMode(r_pin, OUTPUT);
  pinMode(y_pin, OUTPUT);
  pinMode(g_pin, OUTPUT);
}


void loop()
{
  for (int i = 0; i <= 255; i++) {
    analogWrite(r_pin, i);
    delay(1);
  }
  for (int i = 255; i >= 0; i--) {
    analogWrite(r_pin, i);
    delay(1);
  }
  for (int i = 0; i <= 255; i++) {
    analogWrite(y_pin, i);
    delay(1);
  }
  for (int i = 255; i >= 0; i--) {
    analogWrite(y_pin, i);
    delay(1);
  }
  for (int i = 0; i <= 255; i++) {
    analogWrite(g_pin, i);
    delay(1);
  }
  for (int i = 255; i >= 0; i--) {
    analogWrite(g_pin, i);
    delay(1);
  }
}