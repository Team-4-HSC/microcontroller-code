#include "Timer.h"

Timer t;
 
int led_pin = D7;
int D0_Value = D8;
int raw_Value = A0;

int LED_State = 0;
int clap_counter = 0;
int Set_point = 120; //Nilai di ambil dari langkah 2

void setup(){
  Serial.begin(9600);
  pinMode(D0_Value, OUTPUT); // Set pin D8 sebagai digital output
  pinMode(raw_Value, INPUT); //Set pin A0 sebagai input

  t.every(2000, Reset_Clap_counter);
 //Mereset clap_counter setiap 2 detik

}

void loop(){
  int val_digital = digitalRead(D0_Value);
  int val_analog = analogRead(raw_Value );


  Serial.print(val_analog);
  Serial.print("\t");
  Serial.println(val_digital);

  digitalWrite (led_pin, LED_State); //Variabel LED_State adalah keadaan lampu LED

//Setelah 2 detik Clap_counter akan direset

  if(val_analog > Set_point){
    clap_counter ++;

      if (clap_counter == 2){
        LED_State = !LED_State;
        }
  }

  if (val_digital){
    Serial.print("The room is very noisy");
    delay(500);
    }
}

//Fungsi untuk mereset penghitung setiap 2 detik
void Reset_Clap_counter()
{
  clap_counter = 0;
}
