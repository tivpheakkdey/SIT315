#include <Arduino.h>
#include <Wire.h>

const uint8_t btn_pin = 2;
const uint8_t led_pin = 5;

uint8_t led_state = LOW;

void setup()
{
  Serial.begin(9600);
  
  pinMode(btn_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(btn_pin), toggle, FALLING);
}

void loop()
{ 
  delay(500);
}

void toggle(){
  led_state = !led_state;
  digitalWrite(led_pin, led_state);
  
  Serial.println(led_state);
} 