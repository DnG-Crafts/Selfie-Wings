
#include <Wire.h>
#include <radio.h>
#include <TEA5767.h>
TEA5767 radio;   



int led_pin = 2;
int relay_pin = 7;
int switch_pin = 4;

unsigned long switch_Time;
long run_Time = 180000; 
long pulse_Time = 80000;
long pulse_Cnt;
bool pulse_State;

void setup() {

  Wire.begin();
  radio.init();
  radio.setBandFrequency(RADIO_BAND_FM, 9571);
  radio.setMono(false);

  
  switch_Time = 0;
  pulse_Cnt = 0;
  pulse_State = false;
  pinMode(relay_pin,OUTPUT);
  pinMode(led_pin,OUTPUT);
  pinMode(switch_pin, INPUT_PULLUP); 
  digitalWrite(led_pin,LOW);
  digitalWrite(relay_pin,LOW); 
}


void loop() {
  if (digitalRead(switch_pin) == LOW) 
  {
    pulse_Cnt = 0;
    pulse_State = false;
    digitalWrite(relay_pin,HIGH);
    digitalWrite(led_pin,HIGH);
    delay(100);
    digitalWrite(led_pin,LOW);
    delay(100);
    digitalWrite(led_pin,HIGH);
    delay(100);
    digitalWrite(led_pin,LOW);
    delay(100);
    digitalWrite(led_pin,HIGH);
    delay(100);
    digitalWrite(led_pin,LOW);
    delay(100);
    digitalWrite(led_pin,HIGH);    
    switch_Time = millis();
  }
  else if (millis() >= (switch_Time + run_Time))
  {
    switch_Time = 0; 
    pulse_State = false;
    pulse_Cnt = 0;
    digitalWrite(relay_pin,LOW); 
    digitalWrite(led_pin,LOW);
  }   

  if (switch_Time > 0)
  {
    pulse_Cnt = pulse_Cnt + 1;
    if (pulse_Cnt >= pulse_Time)
    {
      pulse_Cnt = 0;
      if (pulse_State)
      {
        pulse_State = false;
        digitalWrite(led_pin,HIGH);
      }
      else
      {
        pulse_State = true;
        digitalWrite(led_pin,LOW);
      }
    }
  }
}
