/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 08 Nov 2021 04:28:17 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include "Wire.h"
#include "U8g2lib.h"
#include <LWiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
char _lwifi_ssid[] = "HUAWEI_E5576_A5C5";
char _lwifi_pass[] = "0972866968";
#define MQTT_SERVER_IP "broker.emqx.io"
#define MQTT_SERVER_PORT 1883
#define MQTT_ID ""
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
String receivedTopic="";
String receivedMsg="";
bool waitForE=true;
bool ended=true;
bool pubCtrl=false;

WiFiClient mqttClient;
PubSubClient myClient(mqttClient);

void connectMQTT(){
  while (!myClient.connected()){
    if (!myClient.connect(MQTT_ID,MQTT_USERNAME,MQTT_PASSWORD))
    {
      delay(5000);
    }
  }
}

DHT dht11_p10(10, DHT11);

void mqttCallback(char* topic, byte* payload, unsigned int length){
  receivedTopic=String(topic);
  receivedMsg="";
  for (unsigned int myIndex = 0; myIndex < length; myIndex++)
  {
      receivedMsg += (char)payload[myIndex];
  }
  receivedMsg.trim();

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

  u8g2.clearDisplay();
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  connectMQTT();
  dht11_p10.begin();
}


void loop()
{
  myClient.loop();
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 0);
    u8g2.print(String(String("Temp: ")+String(dht11_p10.readTemperature())).c_str());
    u8g2.setCursor(0, 10);
    u8g2.print(String(String("Humid: ")+String(dht11_p10.readHumidity())).c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  myClient.publish(String("ccwu0918/temp").c_str(),String(String(dht11_p10.readTemperature())).c_str());
  myClient.publish(String("ccwu0918/humid").c_str(),String(String(dht11_p10.readHumidity())).c_str());
  delay(15000);
}