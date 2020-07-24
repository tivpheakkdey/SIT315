#include <Arduino.h>
#include <Wire.h>

int celsius = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125); //Temperature adjustment implemented by zhtuhin4
  Serial.print(celsius);
  Serial.println(" Celsius");
  
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
