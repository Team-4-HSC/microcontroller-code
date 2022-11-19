#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set Konfigurasi Firebase
#define FIREBASE_HOST "freeroom-fa4a6-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "kd560tu***********************************"
#define WIFI_SSID "My Home"
#define WIFI_PASSWORD "****************"

int sensorPir = D1;
int sensorSuara = A0;
int spdata = 0; // Menampung nilai sensor pir

const int sampleWindow = 50;
unsigned int sample;

String myPir;
String mySound;
String sound = "Sound Detected";
String nosound = "Sound Not-Detected";
String motion = "Motion Detected";
String nomotion = "Motion Not-Detected";

void setup() {
  Serial.begin(9600);
  pinMode(sensorPir, INPUT);
  pinMode(sensorSuara, INPUT);

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


void loop() {
  unsigned long startMillis= millis();
  float peakToPeak = 0;

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  while (millis() - startMillis < sampleWindow) {
    sample = analogRead(sensorSuara);
    if (sample < 1024) {
      if (sample > signalMax) {
        signalMax = sample;
      }
      else if (sample < signalMin) {
        signalMin = sample;
      }
    }
  }
  
  peakToPeak = signalMax - signalMin;
  int db = map(peakToPeak,20,900,49.5,90);

  myPir = String(spdata);
  mySound = String(db);

  Firebase.setString("Variabel/Value_Sound",mySound);
  delay(1000);
  Firebase.setString("Variabel/Value_Motion",myPir);
  delay(1000);

  // long stateSound = digitalRead(sensorSuara);
  if(db > 60 && db < 85) {
    // digitalWrite (statusSound, HIGH);
    Serial.println("Suara Terdeteksi!");
    Firebase.setString("state/alert_sound", sound);
    delay(1000);
  }
  else if(db <= 60) {
    // digitalWrite (statusSound, LOW);
    Serial.println("Suara Tidak Terdeteksi!");
    Firebase.setString("state/alert_sound", nosound);
  }
  // Serial.print("Kebisingan: ");
  // Serial.print(db);
  // Serial.println("dB");
  // if (db <= 60) {
  //   Serial.println("Level: Diam");
  // }
  // else if (db > 60 && db < 85){
  //   Serial.println("Level: Sedang");
  // }
  // else if (db>=85){
  //   Serial.println("Level: Bising");
  // }

  // Serial.print("Value Motion:");
  // Serial.println(myPir);

  // delay(2000);
  long statePir = digitalRead(sensorPir);
  if(statePir ==  HIGH) {
    // digitalWrite (statusPir, HIGH);
    Serial.println(" Gerakan Terdeteksi!");
    Firebase.setString("state/alert_motion", motion);
    delay(1000);
  }
  else {
    // digitalWrite (statusPir, LOW);
    Serial.println("Gerakan Tidak Terdeteksi!");
    Firebase.setString("state/alert_motion", nomotion);
    delay(1000);
  }
}