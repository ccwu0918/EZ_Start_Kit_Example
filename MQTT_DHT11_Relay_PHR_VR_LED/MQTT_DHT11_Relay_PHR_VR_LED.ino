//Generated Date: Thu, 14 Dec 2023 04:46:13 GMT

#include "Wire.h"
#include "U8g2lib.h"
#include <LWiFi.h>
#include <PubSubClient.h>
#define MQTT_SERVER_IP "broker.mqttgo.io"
#define MQTT_SERVER_PORT 1883
#define MQTT_ID ""
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#include <DHT.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
char _lwifi_ssid[] = "iPhone12Pro";
char _lwifi_pass[] = "0972866968";
String receivedTopic="";
String receivedMsg="";
bool waitForE=true;
bool ended=true;
bool pubCtrl=false;

WiFiClient mqttClient;
PubSubClient myClient(mqttClient);

DHT dht11_p10(10, DHT11);
byte r_pin=13;
byte y_pin=12;
byte g_pin=11;

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
  if (receivedTopic == "ccwu0918/relay") {
    digitalWrite(5, (receivedMsg.toInt()));
  }
  if (receivedTopic == "ccwu0918/red_led") {
    analogWrite(r_pin, (receivedMsg.toInt()));
  }
  if (receivedTopic == "ccwu0918/yellow_led") {
    analogWrite(y_pin, (receivedMsg.toInt()));
  }
  if (receivedTopic == "ccwu0918/green_led") {
    analogWrite(g_pin, (receivedMsg.toInt()));
  }

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
  myClient.subscribe(String("ccwu0918/relay").c_str());
  myClient.subscribe(String("ccwu0918/red_led").c_str());
  myClient.subscribe(String("ccwu0918/yellow_led").c_str());
  myClient.subscribe(String("ccwu0918/green_led").c_str());
  dht11_p10.begin();
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(5, OUTPUT);
  pinMode(r_pin, OUTPUT);
  pinMode(y_pin, OUTPUT);
  pinMode(g_pin, OUTPUT);
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
    u8g2.setCursor(0, 20);
    u8g2.print(String(String("PHR: ")+String(analogRead(15))).c_str());
    u8g2.setCursor(0, 30);
    u8g2.print(String(String("VR: ")+String(analogRead(16))).c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  myClient.publish(String("ccwu0918/temp").c_str(),String(String(dht11_p10.readTemperature())).c_str());
  myClient.publish(String("ccwu0918/humid").c_str(),String(String(dht11_p10.readHumidity())).c_str());
  myClient.publish(String("ccwu0918/phr").c_str(),String(String(analogRead(15))).c_str());
  myClient.publish(String("ccwu0918/vr").c_str(),String(String(analogRead(16))).c_str());
  delay(5000);
}
