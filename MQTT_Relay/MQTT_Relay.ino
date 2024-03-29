//Generated Date: Thu, 14 Dec 2023 04:50:44 GMT

#include <LWiFi.h>
#include <PubSubClient.h>
#define MQTT_SERVER_IP "broker.mqttgo.io"
#define MQTT_SERVER_PORT 1883
#define MQTT_ID ""
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""

char _lwifi_ssid[] = "iPhone12Pro";
char _lwifi_pass[] = "0972866968";
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
  if (receivedTopic == "ccwu0918/relay") {
    digitalWrite(5, (receivedMsg.toInt()));
  }

}

void setup()
{
  myClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  myClient.setCallback(mqttCallback);

  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  connectMQTT();
  myClient.subscribe(String("ccwu0918/relay").c_str());
  pinMode(5, OUTPUT);
}

void loop()
{
  myClient.loop();

}
