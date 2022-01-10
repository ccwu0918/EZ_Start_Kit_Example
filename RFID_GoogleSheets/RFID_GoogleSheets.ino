/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 10 Jan 2022 05:22:16 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <LWiFi.h>
#include "Wire.h"
#include "U8g2lib.h"
#include <SPI.h>

#include <MFRC522.h>

char _lwifi_ssid[] = "iPhone12Pro";
char _lwifi_pass[] = "0972866968";
const char* asId="AKfycbyR-Yp-uu4nIvnjvnkILaQ5AX8yFxp-UpBO-Sqs0su3ai1N_BvQsz_Q";
String sheetId="";
String sheetTag="";

String URLEncode(const char* msg)
{
  const char *hex = "0123456789abcdef";
  String encodedMsg = "";
  while (*msg!='\0'){
      if( ('a' <= *msg && *msg <= 'z')
              || ('A' <= *msg && *msg <= 'Z')
              || ('0' <= *msg && *msg <= '9') ) {
          encodedMsg += *msg;
      } else {
          encodedMsg += '%';
          encodedMsg += hex[*msg >> 4];
          encodedMsg += hex[*msg & 15];
      }
      msg++;
  }
  return encodedMsg;
}

void  sendToGoogleSheets(const String& dateInclude,const String& data)
{
  static TLSClient sheetClient;
  const char* host="script.google.com";
  if (sheetClient.connect(host, 443)) {
      const String url = String() +"https://"+host+"/macros/s/"+asId+"/exec?type=insert&dateInclude="+dateInclude+"&sheetId="+sheetId+"&sheetTag="+sheetTag+"&data="+data;
      sheetClient.println("GET " + url + " HTTP/1.1");
      sheetClient.println(String()+"Host: "+host);
      sheetClient.println("Accept: */*");
      sheetClient.println("Connection: close");
      sheetClient.println();
      sheetClient.println();
      sheetClient.stop();
  }
}

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
String RFID[4] = {"d7ffe933", "296300b9", "500ccc63", "0492ce82643480"};

String Users[4] = {"學生01", "學生02", "學生03", "學生04"};

String Name = "";

String Status = "";

MFRC522 rfid(/*SS_PIN*/ 10, /*RST_PIN*/ UINT8_MAX);

String mfrc522_readID_nostop()
{
  String ret;
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
  {
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

    for (byte i = 0; i < rfid.uid.size; i++) {
      ret += (rfid.uid.uidByte[i] < 0x10 ? "0" : "");
      ret += String(rfid.uid.uidByte[i], HEX);
    }
  }
  return ret;
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

  Serial.begin(9600);

  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  sheetId="1VmjBke2LACMBzdjtb0nt3JX0Ub_C0jmOXeOAivrtWoE";
  sheetTag=URLEncode("簽到系統");
  sendToGoogleSheets("0",URLEncode((String() + "日期時間" + "," + "標籤" + "," + "學生姓名" + "," + "狀態").c_str()));
  u8g2.clearDisplay();
  u8g2.setFont(u8g2_font_unifont_t_chinese1);
  pinMode(6, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(5, OUTPUT);
}


void loop()
{
  if (digitalRead(6) == HIGH) {
    if (digitalRead(LED_BUILTIN) == HIGH) {
      digitalWrite(LED_BUILTIN, LOW);
      Status = " [簽退]";
    } else {
      digitalWrite(LED_BUILTIN, HIGH);
      Status = " [簽到]";
    }
    delay(60);
  }
  String RfidNo = mfrc522_readID_nostop();
  if (RfidNo != "") {
    Name = "無法識別";
    for (int i = 0; i <= sizeof(RFID)/sizeof(RFID[0]); i++) {
      if (RFID[i] == RfidNo) {
        Name = Users[i];
        digitalWrite(5, HIGH);
        delay(1000);
        digitalWrite(5, LOW);
      }
    }
    Serial.println((String("RFID: ")+String(RfidNo)));
    Serial.println((String(Name)+String(Status)));
    sendToGoogleSheets("1",URLEncode((String() + RfidNo + "," + Name + "," + Status).c_str()));
    u8g2.clearDisplay();
    u8g2.firstPage();
    do {
      u8g2.setCursor(0, 0);
      u8g2.print(String("RFID: ").c_str());
      u8g2.setCursor(0, 15);
      u8g2.print(String(RfidNo).c_str());
      u8g2.setCursor(0, 31);
      u8g2.print(String(String(Name)+String(Status)).c_str());

      u8g2.sendBuffer();
    } while (u8g2.nextPage());
  }
  delay(1000);
}