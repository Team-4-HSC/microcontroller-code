#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set Konfigurasi Firebase
#define FIREBASE_HOST "freeroom-box-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "W7x9b********************************"
#define WIFI_SSID "AndroidAP"
#define WIFI_PASSWORD "**********"

String myPir;
String mySound;
String sound = "Sound Detected";
String nosound = "Sound Not-Detected";
String motion = "Motion Detected";
String nomotion = "Motion Not-Detected";

int spdata = 0; // Menampung nilai sensor pir
int ssdata = 0; // Menampung nilai sensor suara
int sensorPir = D1;
int statusPir = D4;
int sound_digital = D0;
int sound_analog = A0;
int statusSound = D5;



void setup() {
  Serial.begin(9600);
  pinMode(sensorPir, INPUT);
  pinMode(statusPir, OUTPUT);
  int val = 0;
  // Menghubungkan ke wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Menghubungkan...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Terhubung: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {
  // val_kyd = digitalRead(sound_digital);
  // val_kya = analogRead(sound_analog);
  ssdata = digitalRead(sound_digital);
  spdata = digitalRead(sensorPir);
  myPir = String(spdata);
  mySound = String(ssdata);
  Serial.println(mySound);
  Serial.print("/t");
  Serial.println(myPir);
  // Serial.print("/t");
  // Serial.println(val_kya);
  // Serial.print("/t");
  // Serial.println(val_kyd);
  Firebase.setString("Variabel/Value",mySound);
  delay(1000);
  Firebase.setString("Variabel/Value",myPir);
  delay(1000);

  long stateSound = digitalRead(sound_digital);
  if(stateSound == HIGH) {
    digitalWrite (statusSound, HIGH);
    Serial.print("Suara Terdeteksi!");
    Serial.println(stateSound);
    Firebase.setString("state/alert", sound);
    delay(1000);
  }
  else {
    digitalWrite (statusSound, LOW);
    Serial.print("Suara Tidak Terdeteksi!");
    Firebase.setString("state/alert", nosound);
  }

  delay(10000);

  long statePir = digitalRead(sensorPir);
  if(statePir ==  HIGH) {
    digitalWrite (statusPir, HIGH);
    Serial.print("Gerakan Terdeteksi!");
    Serial.println(statePir);
    Firebase.setString("state/alert", motion);
    delay(1000);
  }
  else {
    digitalWrite (statusPir, LOW);
    Serial.print("Gerakan Tidak Terdeteksi!");
    Firebase.setString("state/alert", nomotion);
    delay(1000);
  }
  
}