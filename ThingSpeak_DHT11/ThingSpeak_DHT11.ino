/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 08 Nov 2021 05:29:04 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include "Wire.h"
#include "U8g2lib.h"
#include <LWiFi.h>
#include <DHT.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
char _lwifi_ssid[] = "HUAWEI_E5576_A5C5";
char _lwifi_pass[] = "0972866968";
DHT dht11_p10(10, DHT11);

void invokeThingSpeak(const String& key, const String& p1, const String& p2, const String& p3, const String& p4, const String& p5, const String& p6, const String& p7, const String& p8)
{
  // Initialize the Ethernet client library
  // with the IP address and port of the server
  // that you want to connect to (port 80 is default for HTTP):
  static WiFiClient client;

  if (client.connect("api.thingspeak.com", 80)) {
  const String payload = String() + "{\"api_key\":\"" + key
                        + "\",\"field1\":\"" + p1
                        + "\",\"field2\":\"" + p2
                        + "\",\"field3\":\"" + p3
                        + "\",\"field4\":\"" + p4
                        + "\",\"field5\":\"" + p5
                        + "\",\"field6\":\"" + p6
                        + "\",\"field7\":\"" + p7
                        + "\",\"field8\":\"" + p8
                        + "\"}";

      const String url = String() + "https://api.thingspeak.com/update";

      client.println(String() + "POST " + url + " HTTP/1.1");
      client.println("Host: api.thingspeak.com");
      client.println("User-Agent: BlocklyDuino/1.0");
      client.println("Content-Type: application/json;charset=utf-8");
      client.print("Content-Length: ");
      client.println(payload.length());
      client.println("User-Agent: BlocklyDuino/1.0");
      client.println("Accept: */*");
      client.println("Connection: close");

      client.println();
      client.print(payload);

      client.println();
      delay(300);
  } else {
    // Serial.println("failed to connect to ThingSpeak");
  }

  // wait for server response
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
      char c = client.read();
      // Serial.print(c);
      delay(1);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
      //Serial.println();
      //Serial.println("disconnecting from server passively.");
      client.stop();
  } else {
    // otherwise we actively stop the connection. we'll reconnect next time.
    //Serial.println("disconnecting from server.");
    client.stop();
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

  u8g2.clearDisplay();
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  dht11_p10.begin();
}


void loop()
{
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 0);
    u8g2.print(String(String("Temp: ")+String(dht11_p10.readTemperature())).c_str());
    u8g2.setCursor(0, 10);
    u8g2.print(String(String("Humid: ")+String(dht11_p10.readHumidity())).c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  invokeThingSpeak("LF5SWKAZ4MS24P2B", String(dht11_p10.readTemperature()), String(dht11_p10.readHumidity()), String(0), String(0), String(0), String(0), String(0), String(0));
  delay(15000);
}