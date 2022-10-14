int sensorPir = D1; // Set Sensor Pir ke Pin D1
int led1 = D4; // Set LED ke Pin D4

void setup() {
  pinMode(sensorPir, INPUT);
  pinMode(led1, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  long state = digitalRead(sensorPir);
  if (state == HIGH) {
    digitalWrite(led1, HIGH); // Led akan menyala jika gerakan terdeteksi.
    Serial.println("Gerakan Terdeteksi!");
    delay(1000);
  }
  else {
    digitalWrite(led1, LOW); // Led akan mati jika gerakan tidak terdeteksi.
    Serial.println("Gerakan Tidak Terdeteksi!");
    delay(1000);
  }
}