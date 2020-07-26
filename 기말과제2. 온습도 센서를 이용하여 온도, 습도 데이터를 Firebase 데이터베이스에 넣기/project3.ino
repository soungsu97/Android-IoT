#include <DHT.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "mydhtsensor-b6a50.firebaseio.com"
#define FIREBASE_AUTH "vM9734JvyveoZBGPGp5J1iG1UVW914nR43TJgCZa"
#define WIFI_SSID "SK_WiFi1627"  // 와이파이 공유기 혹은 스마트폰 테더링 SSID
#define WIFI_PASSWORD "1303022313"  // 와이파이 공유기 혹은 스마트폰 테더링 접속 비밀번호
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
  Serial.print("Temperature = ");
  Serial.println(temp);
  Serial.print("Humidity = ");
  Serial.println(humi);     

  StaticJsonBuffer<200> jsonbuffer;
  JsonObject& root = jsonbuffer.createObject();
  root["temperature"] = temp;
  root["humidity"] = humi;

  String name = Firebase.push("logDHT", root);
  
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logDHT/");
  Serial.println(name);
  
  delay(5000);
}
