#include <Wire.h>
#include <WiFi.h>
#include "RTClib.h"
#include "time.h"

//========================================================================

//WiFi Details
const char* ssid       = "The Internet";
const char* password   = "The Password";

//-RTC-
RTC_DS3231 rtc;

int yr = 0;
int mt = 0;
int dy = 0;
int hr = 0;
int mi = 0;
int se = 0;

// NTP server to request time
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 0;


// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}


// Function that gets time from NTP Server and syncs RTC clock
unsigned long getTime() {

  struct tm timeinfo;
  getLocalTime(&timeinfo);

  yr = timeinfo.tm_year + 1900;
  mt = timeinfo.tm_mon + 1;
  dy = timeinfo.tm_mday;
  hr = timeinfo.tm_hour;
  mi = timeinfo.tm_min;
  se = timeinfo.tm_sec;

  rtc.adjust(DateTime(yr, mt, dy, hr, mi, se));

    //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

}

void setup() {
  Serial.begin(115200);
  rtc.begin(); //Start RCT

  //Wifi
  initWiFi();

  //Time Server
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  getTime();
}

void loop() {

  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.println();
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  Serial.print(now.unixtime());
  Serial.println();

  delay(1000);

}
