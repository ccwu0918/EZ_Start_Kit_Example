/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 03 Oct 2021 16:27:38 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include "Wire.h"
#include "U8g2lib.h"
#include <LWiFi.h>
#include <LRTC.h>
#include <WiFiUdp.h>
#include <ctime>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
char _lwifi_ssid[] = "HUAWEI_A5C5";
char _lwifi_pass[] = "0972866968";

void set_rtc_from_time_string(const String& time_str) {
  // field_index [0,1,2,3,4,5] = [Year,Month,Day,Hour,Minute,Sec]
  int fields[6] = {0};
  sscanf(time_str.c_str(), "%d-%d-%dT%d:%d:%d+08",
          &fields[0], &fields[1], &fields[2],
          &fields[3], &fields[4], &fields[5]);
  LRTC.set(fields[0], fields[1], fields[2],
           fields[3], fields[4], fields[5]);
}

const char *NTP_server = "time.stdtime.gov.tw";
const int NTP_PACKET_SIZE = 48;                   // NTP time stamp is in the first 48 bytes of the message
static byte packetBuffer[NTP_PACKET_SIZE] = {0};  //buffer to hold incoming and outgoing packets
const unsigned int localPort = 2390;              // local port to listen for UDP packets
static WiFiUDP Udp;                               // A UDP instance to let us send and receive packets over UDP

String getNetworkTime() {
  Udp.begin(localPort);
  sendNTPpacket(NTP_server); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);
  if (Udp.parsePacket()) {
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:
    const unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    const unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    const unsigned long secsSince1900 = highWord << 16 | lowWord;
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    const unsigned long epoch = secsSince1900 - seventyYears;
    // Taiwan is UTC+8 = 8 * 60 * 60 seconds
    const time_t taiwan_time = epoch + (8 * 60 * 60);
    // const tm* pTime = gmtime(&taiwan_time);
    static char time_text[] = "YYYY-MM-DDTHH:MM:SS+08";
    strftime(time_text, sizeof(time_text), "%Y-%m-%dT%H:%M:%S+08", gmtime(&taiwan_time));
    return String((const char*)time_text);
  }

  return String("Connection error");
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(const char* host) {
	//Serial.println("1");
	// set all bytes in the buffer to 0
	memset(packetBuffer, 0, NTP_PACKET_SIZE);
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	//Serial.println("2");
	packetBuffer[0] = 0b11100011;   // LI, Version, Mode
	packetBuffer[1] = 0;     // Stratum, or type of clock
	packetBuffer[2] = 6;     // Polling Interval
	packetBuffer[3] = 0xEC;  // Peer Clock Precision
	// 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer[12]  = 49;
	packetBuffer[13]  = 0x4E;
	packetBuffer[14]  = 49;
	packetBuffer[15]  = 52;

	//Serial.println("3");

	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp:
	Udp.beginPacket(host, 123); //NTP requests are to port 123
	//Serial.println("4");
	Udp.write(packetBuffer, NTP_PACKET_SIZE);
	//Serial.println("5");
	Udp.endPacket();
	//Serial.println("6");

	return 0;
}

String get_time_from_RTC() {
  // get time from the RTC module
  LRTC.get();

  // format to time string
  static char buffer[] = "YYYY-MM-DDTHH:MM:SS+08";
  sprintf(buffer, "%04ld-%02ld-%02ldT%02ld:%02ld:%02ld+08",
    LRTC.year(),
    LRTC.month(),
    LRTC.day(),
    LRTC.hour(),
    LRTC.minute(),
    LRTC.second());

  return String(buffer);
}

const float pi = 3.14159267 ;
int x_old;
int y_old;
int x_new;
int y_new;

void draw_second(int second){
   y_old= (24*cos(pi-(2*pi)/60*second))+clock_center_y;
   x_old =(24*sin(pi-(2*pi)/60*second))+clock_center_x;
   u8g2.drawCircle(x_old, y_old, 2);
}

void draw_hour(int hour, int minute){
   y_old= (18*cos(pi-(2*pi)/12*hour-(2*PI)/720*minute))+clock_center_y;
   x_old =(18*sin(pi-(2*pi)/12*hour-(2*PI)/720*minute))+clock_center_x;
   y_new=(18*cos(pi-(2*pi)/12*hour-(2*PI)/720*minute))+clock_center_y+1;
   x_new=(18*sin(pi-(2*pi)/12*hour-(2*PI)/720*minute))+clock_center_x+1;
   u8g2.drawLine(clock_center_x,clock_center_y,x_old,y_old);
   u8g2.drawLine(clock_center_x+1,clock_center_y+1,x_new,y_new);
}

void draw_minute(int minute){
   y_old= (24*cos(pi-(2*pi)/60*minute))+clock_center_y;
   x_old =(24*sin(pi-(2*pi)/60*minute))+clock_center_x;
   u8g2.drawLine(clock_center_x,clock_center_y,x_old,y_old);
}

void draw_clock_face(void){
  u8g2.drawDisc(clock_center_x, clock_center_y,3);
  for (int i=0;i<12;i++){
     y_old= (32*cos(pi-(2*pi)/12*i))+clock_center_y;
     x_old =(32*sin(pi-(2*pi)/12*i))+clock_center_x;
     y_new= (28*cos(pi-(2*pi)/12*i))+clock_center_y;
     x_new =(28*sin(pi-(2*pi)/12*i))+clock_center_x;
     u8g2.drawLine(x_new,y_new,x_old,y_old);
  }
  u8g2.setCursor(clock_center_x-3,clock_center_y-32);
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.println("12");
}

void runClock(){
  draw_clock_face();
  LRTC.get();
  draw_second(LRTC.second());
  draw_minute(LRTC.minute());
  draw_hour(LRTC.hour(),LRTC.minute());
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

  LRTC.begin();
  u8g2.setFont(u8g2_font_unifont_t_chinese1);
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 1);
    u8g2.print(String("EZ Starter Kit+").c_str());
    u8g2.setCursor(0, 17);
    u8g2.print(String("Wi-Fi connection......").c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 1);
    u8g2.print(String("EZ Starter Kit+").c_str());
    u8g2.setCursor(0, 17);
    u8g2.print(String("Wi-Fi connected ").c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  set_rtc_from_time_string(getNetworkTime());
}


void loop()
{
  for (int count = 0; count < 10; count++) {
    u8g2.firstPage();
    do {
      u8g2.setCursor(0, 1);
      u8g2.print(String("EZ Starter Kit+").c_str());
      u8g2.setCursor(0, 17);
      u8g2.print(String(String("時間: ")+String(get_time_from_RTC())).c_str());

      u8g2.sendBuffer();
    } while (u8g2.nextPage());
    delay(1000);
  }
  for (int count2 = 0; count2 < 10; count2++) {
    u8g2.firstPage();
    do {
      runClock();

      u8g2.sendBuffer();
    } while (u8g2.nextPage());
    delay(1000);
  }
}