#include <ESP8266WiFi.h>
#include <FirebaseArduino.h> 

#define FIREBASE_HOST "codingcamp-2020-skku.firebaseio.com" 
#define FIREBASE_AUTH ""                                  // 데이터베이스 접속 키
#define WIFI_SSID "DSLAB-2.4G"                            // 와이파이 SSID
#define WIFI_PASSWORD "dslab85216"                        // 와이파이 Password

void setup() {
  Serial.begin(9600);
  
  //와이파이 연결
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  //파이어베이스 연결
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  //아날로그값 입력 및 온도값 계산
  float temp = analogRead(A0);
  temp = round((temp*320/1024 - 50)*10)/10;
  
  Serial.print("temp : ");
  Serial.println(temp);
  
  //온도값 데이터베이스에 업로드
  Firebase.setFloat("Temperature", temp);
  if(temp > 30){
    Firebase.setString("State", "HIGH");
    Firebase.setInt("Green", 0);
    Firebase.setInt("Red", 1);
  }else{
    Firebase.setString("State", "LOW");
    Firebase.setInt("Green", 1);
    Firebase.setInt("Red", 0);
  }
  
  delay(2000);
}
