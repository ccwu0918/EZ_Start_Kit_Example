//Generated Date: Thu, 14 Dec 2023 04:52:28 GMT

#include <Adafruit_NeoPixel.h>

#include "Wire.h"
#include "U8g2lib.h"
#include "TinyGsmClientSIM7020.h"
#include <Am7020PubSubClient.h>
#include <DHT.h>

unsigned long timer = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(3, 4,NEO_GRB + NEO_KHZ800);

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
typedef TinyGsmSim7020 TinyGsm;
typedef TinyGsmSim7020::GsmClientSim7020 TinyGsmClient;

TinyGsm       modem(Serial1, 3);

void nbConnect(void)
{
    Serial.println(F("Initializing modem..."));
    while (!modem.init() || !modem.nbiotConnect("iot4ga2", 28)) {
        Serial.print(F("."));
    }

    Serial.print(F("Waiting for network..."));
    while (!modem.waitForNetwork()) {
        Serial.print(F("."));
    }
    Serial.println(F(" success"));
}

const char* broker = "broker.mqttgo.com";
const int port = 1883;
const char* mqtt_id = "";
const char* mqtt_username = "";
const char* mqtt_password = "";

String topic_buff;

String msg_buff;

TinyGsmClient tcpClient(modem);
Am7020PubSubClient  mqttClient(broker, port, tcpClient);

void mqttConnect(void)
{
    Serial.print(F("Connecting to "));
    Serial.print(broker);
    Serial.print(F("..."));

    while (!mqttClient.connect(mqtt_id, mqtt_username, mqtt_password)) {
        Serial.print(F(" fail"));
    }
    Serial.println(F(" success"));
}

DHT dht11_p10(10, DHT11);

void mqttCallback(char *topic, byte *payload, unsigned int len)
{
    topic_buff = String(topic);
    msg_buff = "";

    for (int ii = 0;ii < (int)len;ii++) {
        msg_buff += (char)(*(payload + ii));
    }
    Serial.print(F("Message arrived ["));
    Serial.print(topic_buff);
    Serial.print(F("]: "));
    Serial.println(msg_buff);

  if (topic_buff == "ccwu0918/msg") {
    u8g2.firstPage();
    do {
      u8g2.setCursor(0, 0);
      u8g2.print(String(msg_buff).c_str());

      u8g2.sendBuffer();
    } while (u8g2.nextPage());
  }

}

void setup()
{
  pixels.begin();

  pixels.setBrightness(30);

  Serial.begin(115200);

  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);

  Serial1.begin(115200);

  randomSeed(analogRead(16));

  topic_buff.reserve(100);

  msg_buff.reserve(100);

  mqttClient.setCallback(mqttCallback);

  mqttClient.setKeepAlive(270);

  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 0);
    u8g2.print(String("AM7020 Init ...").c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  nbConnect();
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 0);
    u8g2.print(String("NBIoT Connecting...").c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  mqttConnect();
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 0);
    u8g2.print(String("MQTT Connecting...").c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  mqttClient.subscribe(String("ccwu0918/msg").c_str());
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 0);
    u8g2.print(String("MQTT Connected !").c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  dht11_p10.begin();

}

void loop()
{
  if (!modem.isNetworkConnected()) {
    nbConnect();
  }
  if (!mqttClient.connected()) {
    mqttConnect();
    mqttClient.subscribe(String("ccwu0918/msg").c_str());
  }
  mqttClient.loop();
  u8g2.firstPage();
  do {
    u8g2.firstPage();
    do {
      u8g2.setCursor(0, 0);
      u8g2.print(String(String("Temperature: ")+String(dht11_p10.readTemperature())).c_str());
      u8g2.setCursor(0, 12);
      u8g2.print(String(String("Humidity: ")+String(dht11_p10.readHumidity())).c_str());
      delay(1000);

      u8g2.sendBuffer();
    } while (u8g2.nextPage());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  if (millis() >= timer) {
    timer = millis() + 60000;
    mqttClient.publish(String("ccwu0918/temperature").c_str(), String(dht11_p10.readTemperature()).c_str());
    mqttClient.publish(String("ccwu0918/humidity").c_str(), String(dht11_p10.readHumidity()).c_str());
    Serial.println((String("Temperature: ")+String(dht11_p10.readTemperature())));
    Serial.println((String("Humidity: ")+String(dht11_p10.readHumidity())));
  }
}
