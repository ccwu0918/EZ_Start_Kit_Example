/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 07 Nov 2021 15:42:59 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

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

void mqttCallback(char* topic, byte* payload, unsigned int length){
  receivedTopic=String(topic);
  receivedMsg="";
  for (unsigned int myIndex = 0; myIndex < length; myIndex++)
  {
      receivedMsg += (char)payload[myIndex];
  }
  receivedMsg.trim();
  digitalWrite(12,(receivedMsg == "On"));

}

void setup()
{
  myClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  myClient.setCallback(mqttCallback);

  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  connectMQTT();
  myClient.subscribe(String("ccwu0918/ButtonR").c_str());
  for (int count = 0; count < 3; count++) {
    digitalWrite(13,(!(HIGH)));
    delay(200);
    digitalWrite(13,(!(LOW)));
    delay(200);
  }
  digitalWrite(13,(!(HIGH)));
  pinMode(12,OUTPUT);
  pinMode(0,INPUT);
}


void loop()
{
  myClient.loop();
  if (!digitalRead(0)){
    digitalWrite(12,((digitalRead(12)) ? false : true));
    while(!digitalRead(0)){}
  }
}