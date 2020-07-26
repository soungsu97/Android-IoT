#include <DHT.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "hello-firebase-62034.firebaseio.com"
#define FIREBASE_AUTH "CTUJ0ByEB4Tt1Df7czvu3KBM5LaeUk3q4dnqUMt3"
#define WIFI_SSID "fourfoot"  // 와이파이 공유기 혹은 스마트폰 테더링 SSID
#define WIFI_PASSWORD "05959720"  // 와이파이 공유기 혹은 스마트폰 테더링 접속 비밀번호
#define DHTPIN D4     
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE); 

void setup() {
  Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  dht.begin(9600);
  
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
 
void loop() {
    float temp = dht.readTemperature();
    float humi = dht.readHumidity();
    Firebase.pushFloat("temperature", temp);
    Firebase.pushFloat("humidity", humi);
    if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
    }
    Serial.print("pushed: /logDHT/");
    delay(5000);
}
