#include <DHT.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define FIREBASE_HOST "fir-android-a0541.firebaseio.com"
#define FIREBASE_AUTH "kdylsk5h4TbSHci1JjhN0DUqg1HIyL1dh3GT1hbF"
#define WIFI_SSID "DIT_FREE_WiFi"  // 와이파이 공유기 혹은 스마트폰 테더링 SSID
//#define WIFI_PASSWORD "05959720"  // 와이파이 공유기 혹은 스마트폰 테더링 접속 비밀번호
#define DHTPIN D4     
#define DHTTYPE DHT11  

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String formattedDate; // 날짜 시간을 저장하는 변수

DHT dht(DHTPIN, DHTTYPE); 

void setup() {
  Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID);
  dht.begin(9600);
  
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
   //WiFi 연결
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
   //Firebase 초기화, 연결
  timeClient.begin(); //NTP 초기화
  timeClient.setTimeOffset(32400);  // 한국은 GMT+9이므로 9*3600=32400
  }
 
void loop() {
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  formattedDate = timeClient.getFormattedDate();
  Serial.println(formattedDate);
  delay(1000);
  //인터넷에서 시간을 받아와서 String형으로 변환
  
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  StaticJsonBuffer<200> jsonbuffer;
  JsonObject& root = jsonbuffer.createObject();
  root["temperature"] = temp;
  root["humidity"] = humi;
  root["time"] = formattedDate;

  String name = Firebase.push("logDHT", root);
  if (Firebase.failed()) {
  Serial.print("pushing /logs failed:");
  Serial.println(Firebase.error());
  return;
  }
  Serial.print("pushed: /logDHT/");
  delay(5000);
}
