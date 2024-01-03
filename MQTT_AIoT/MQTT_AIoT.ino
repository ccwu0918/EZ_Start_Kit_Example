//Generated Date: Wed, 03 Jan 2024 17:15:30 GMT

#include "Wire.h"
#include "U8g2lib.h"
#include <LWiFi.h>
#include <PubSubClient.h>
#define MQTT_SERVER_IP "broker.mqttgo.io"
#define MQTT_SERVER_PORT 1883
#define MQTT_ID ""
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
char _lwifi_ssid[] = "Xiaomi_7C2C";
char _lwifi_pass[] = "082322586";
String receivedTopic="";
String receivedMsg="";
bool waitForE=true;
bool ended=true;
bool pubCtrl=false;

WiFiClient mqttClient;
PubSubClient myClient(mqttClient);

int _E6_A8_82_E4_BA_8B = 0;
int _E5_A5_B6_E8_8C_B6 = 0;
int POCKY = 0;
int _E5_8F_AF_E6_A8_82 = 0;
int _E5_85_B6_E5_AE_83 = 0;
int _E7_B8_BD_E9_87_91_E9_A1_8D = 0;
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

void connectMQTT(){
  while (!myClient.connected()){
    if (!myClient.connect(MQTT_ID,MQTT_USERNAME,MQTT_PASSWORD))
    {
      delay(5000);
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length){
  receivedTopic=String(topic);
  receivedMsg="";
  for (unsigned int myIndex = 0; myIndex < length; myIndex++)
  {
    receivedMsg += (char)payload[myIndex];
  }
  receivedMsg.trim();
  if (receivedTopic == "nquiem/other") {
    _E5_85_B6_E5_AE_83 = _E5_85_B6_E5_AE_83 + 1;
  } else if (receivedTopic == "nquiem/lays") {
    _E6_A8_82_E4_BA_8B = _E6_A8_82_E4_BA_8B + 1;
  } else if (receivedTopic == "nquiem/milk_tea") {
    _E5_A5_B6_E8_8C_B6 = _E5_A5_B6_E8_8C_B6 + 1;
  } else if (receivedTopic == "nquiem/pocky") {
    POCKY = POCKY + 1;
  } else if (receivedTopic == "nquiem/cola") {
    _E5_8F_AF_E6_A8_82 = _E5_8F_AF_E6_A8_82 + 1;
  }
  _E7_B8_BD_E9_87_91_E9_A1_8D = ((_E6_A8_82_E4_BA_8B * 30) + (_E5_A5_B6_E8_8C_B6 * 10)) + ((POCKY * 40) + (_E5_8F_AF_E6_A8_82 * 25));

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

  myClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  myClient.setCallback(mqttCallback);

  u8g2.setFont(u8g2_font_unifont_t_chinese1);
  u8g2.clearDisplay();
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 10);
    u8g2.print(String("Wi-Fi 連線中.....").c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  connectMQTT();
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 10);
    u8g2.print(String("Wi-Fi 連線成功。").c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  myClient.subscribe(String("nquiem/lays").c_str());
  myClient.subscribe(String("nquiem/milk_tea").c_str());
  myClient.subscribe(String("nquiem/pocky").c_str());
  myClient.subscribe(String("nquiem/cola").c_str());
  myClient.subscribe(String("nquiem/other").c_str());
  pinMode(A_Pin, INPUT);
  pinMode(B_Pin, INPUT);
}

void loop()
{
  myClient.loop();
  myBtnStatus=getBtnStatus();
  if (myBtnStatus=='C'){
    _E6_A8_82_E4_BA_8B = 0;
    _E5_A5_B6_E8_8C_B6 = 0;
    POCKY = 0;
    _E5_8F_AF_E6_A8_82 = 0;
    _E5_85_B6_E5_AE_83 = 0;
    _E7_B8_BD_E9_87_91_E9_A1_8D = 0;
    while(buttonPressed('C')){}
  }
  if (myBtnStatus=='A'){
    _E7_B8_BD_E9_87_91_E9_A1_8D = ((_E6_A8_82_E4_BA_8B * 30) + (_E5_A5_B6_E8_8C_B6 * 10)) + ((POCKY * 40) + (_E5_8F_AF_E6_A8_82 * 25));
    while(buttonPressed('A')){}
  }
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 5);
    u8g2.print(String(String("樂事: ")+String(_E6_A8_82_E4_BA_8B)).c_str());
    u8g2.setCursor(65, 5);
    u8g2.print(String(String("奶茶:  ")+String(_E5_A5_B6_E8_8C_B6)).c_str());
    u8g2.setCursor(0, 25);
    u8g2.print(String(String("Pocky: ")+String(POCKY)).c_str());
    u8g2.setCursor(65, 25);
    u8g2.print(String(String("可樂: ")+String(_E5_8F_AF_E6_A8_82)).c_str());
    u8g2.setCursor(0, 45);
    u8g2.print(String(String("總金額: ")+String(_E7_B8_BD_E9_87_91_E9_A1_8D)).c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  delay(200);
}
