#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "fir-with-andoridtwo.firebaseio.com" // 데이터 베이스 호스트 이름
#define FIREBASE_AUTH "s5UBMP91oSGncqXagxGL1s7I6BlP0OC1mQsiPWCu" // 데이터 베이스 비밀번호

#define WIFI_SSID "KT_GiGA_2G_Wave2_CD94" // Wi-Fi 설정
#define WIFI_PASSWORD "!@#whtj404" // Wi-Fi 설정

String led_status = ""; 
int led_pin = D4;
                                                              
void setup() {
  Serial.begin(9600);
  delay(1000);    
  pinMode(led_pin, OUTPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);           // 와이파이 실행                              
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // 입력된 호스트와 비밀번호를 기반으로 파이어베이스 실행 Firebase.setString("led_status", "OFF");
}

void loop() 
{
  led_status = Firebase.getString("led_status");  // 데이터베이스의 led_status 값 받아오기
  if (led_status == "ON")   {                     // led_status 값 비교 및 점/소등
    Serial.println("LED Turned ON");                                                        
    digitalWrite(led_pin, HIGH);
  } else if (led_status == "OFF") {
    Serial.println("LED Turned OFF");
    digitalWrite(led_pin, LOW);
  } else {
    Serial.println("데이터베이스 값 오류발생, 확인 후 수정바랍니다.");
  }
  delay(2000);
}
