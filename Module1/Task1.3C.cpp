#include <Arduino.h>
#include <Wire.h>

const uint8_t btn_pin = 2;
const uint8_t led_pin = 6;

uint8_t led_state = LOW;

int celsius = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
  pinMode(btn_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(btn_pin), toggle, FALLING);
}

void loop()
{
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125); //Temperature adjustment implemented by zhtuhin4
  Serial.print(celsius);
  Serial.print(" Celsius,");
  
  Serial.print(" Led State:");
  Serial.println(led_state);
  
  //Light up appropriate LED accordingly to the temp
  if(celsius < 50){
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  else if(celsius >= 50 && celsius < 75){
  	digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);  
  }
  else if(celsius >= 75 && celsius < 100){
  	digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);  
  }
  else{
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);  
  }  
  delay(1000);
}

void toggle(){
  led_state = !led_state;
  digitalWrite(led_pin, led_state);
  
  Serial.println(led_state);
} 
