#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "EDIT" 
#define FIREBASE_AUTH "EDIT" 
#define WIFI_SSID     "//"
#define WIFI_PASSWORD "//"

int button_pin = 2 ; // 2 -> D4  if(pin) //0 -> D3
const int led  = 13 ; // D1
int buttonState = 0 ;
bool lastState = false;
int number = 0;
int x ;

void Initialization() {
  Serial.begin(9600); // Check connect wifi & firebase
  digitalWrite(LED_BUILTIN, OUTPUT); // esp8266  On
  pinMode(button_pin , INPUT_PULLUP);
}
// edit
void button() {
  buttonState = digitalRead(button_pin);
  if (lastState == LOW && buttonState == HIGH) {
    number += 1  ;
    digitalWrite(led , HIGH);
    Firebase.pushInt("number", number);
    Serial.println(number);
  }
  else {
    digitalWrite(led,LOW);
  }
}

void WiFiConnection() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void Check_firebase_error() {
  if (Firebase.failed()) {
    Serial.println("Connecting Error");
    Serial.println(Firebase.error());
    //delay(1000);
  }
}

void setup() {
  Initialization ();
  WiFiConnection ();
  Check_firebase_error();
 }

 void loop() {
    digitalWrite (LED_BUILTIN , HIGH);
    button();
    //Firebase.setInt("number", number++);
    //Serial.println(number);
    lastState = buttonState;
   delay(100);
  }
