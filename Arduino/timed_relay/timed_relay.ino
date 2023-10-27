int led_pin = 2;
int relay_pin = 7;
int switch_pin = 4;

unsigned long switch_Time;
long run_Time = 120000; 


void setup() {
  switch_Time = 0;
  pinMode(relay_pin,OUTPUT);
  pinMode(led_pin,OUTPUT);
  pinMode(switch_pin, INPUT_PULLUP); 
  digitalWrite(led_pin,LOW);
  digitalWrite(relay_pin,LOW); 
}


void loop() {
  if (digitalRead(switch_pin) == LOW) 
  {
    switch_Time = millis();
    digitalWrite(relay_pin,HIGH);
    digitalWrite(led_pin,HIGH);
  }
  else if (millis() >= (switch_Time + run_Time))
  {
    switch_Time = 0; 
    digitalWrite(relay_pin,LOW); 
    digitalWrite(led_pin,LOW);
  }   
}
