#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set Konfigurasi Firebase
#define FIREBASE_HOST "freeroom-box-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "W7x9bMZ*************************************"
#define WIFI_SSID "AndroidAP"
#define WIFI_PASSWORD "1*********"

String myString;
String motion = "Detected";
String nomotion = "Not Detected";

int sdata = 0;
int sensorPir = D1;
int status = D4;



void setup() {
  Serial.begin(9600);
  pinMode(sensorPir, INPUT);
  pinMode(status, OUTPUT);
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
  sdata = digitalRead(sensorPir);
  myString = String(sdata);
  Serial.println(myString);
  Firebase.setString("Variabel/Value",myString);
  delay(1000);

  long state = digitalRead(sensorPir);
  if(state ==  HIGH) {
    digitalWrite (status, HIGH);
    Serial.println("Gerakan Terdeteksi!");
    Serial.println(state);
    Firebase.setString("state/alert", motion);
    delay(1000);
  }
  else {
    digitalWrite (status, LOW);
    Serial.println("Gerakan Tidak Terdeteksi");
    Firebase.setString("state/alert", nomotion);
    delay(1000);
  }
  
}