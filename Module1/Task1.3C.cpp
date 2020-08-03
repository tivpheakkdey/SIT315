const uint8_t btn_pin = 2;
const uint8_t pir_pin = 3;
const uint8_t led_pin1 = 7;
const uint8_t led_pin2 = 6;

uint8_t led_state = LOW;


void setup()
{
  Serial.begin(9600);

  pinMode(btn_pin, INPUT_PULLUP);
  pinMode(pir_pin, INPUT_PULLUP);
  pinMode(led_pin1, OUTPUT);
  pinMode(led_pin2, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(btn_pin), toggle, FALLING);
  attachInterrupt(digitalPinToInterrupt(pir_pin), blink, RISING);
}

void loop()
{
  delay(10000); 
}


void toggle(){
  led_state = !led_state;
  digitalWrite(led_pin1, led_state);
  
  Serial.println(led_state);
} 

void blink(){
  digitalWrite(led_pin2, LOW);
  digitalWrite(led_pin2, HIGH);
  delay(100);
  digitalWrite(led_pin2, LOW);
}


