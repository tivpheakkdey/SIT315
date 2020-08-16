//Pins
const uint8_t btn_pin1 = PD2;
const uint8_t btn_pin2 = PD3;
const uint8_t btn_pin3 = PD4;

const uint8_t led_pin1 = PD5;
const uint8_t led_pin2 = PD6;
const uint8_t led_pin3 = PD7;

const uint8_t ledBlink_pin = PB5;

//Counter and compare values
const uint16_t t1_load = 0;
const uint16_t t1_comp = 31250;

void setup()
{
  Serial.begin(9600);
  
  //Set btn_pin to input with pull up
  DDRD &= ~_BV(btn_pin1);
  PORTD |= _BV(btn_pin1);
  
  DDRD &= ~_BV(btn_pin2);
  PORTD |= _BV(btn_pin2); 
  
  DDRD &= ~_BV(btn_pin3);
  PORTD |= _BV(btn_pin3); 
  
  //Set led_pin to output
  DDRD |= _BV(led_pin1);
  DDRD |= _BV(led_pin2);
  DDRD |= _BV(led_pin3);
  DDRB |= _BV(ledBlink_pin);
  
  //------------------------------------//
  //Enable PCINT on port D
  PCICR |= _BV(PCIE2);
  
  //Enable interrupt on Pin...
  PCMSK2 |= _BV(PD2);
  PCMSK2 |= _BV(PD3);
  PCMSK2 |= _BV(PD4);
  
  //------------------------------------//
  
  //Reset Timer1 Control Reg A
  TCCR1A = 0;
  
  //Set Timer1 prescalar to 256
  TCCR1B |= _BV(CS12);
  TCCR1B &= ~_BV(CS11);
  TCCR1B &= ~_BV(CS10);
   
  //Reset Timer1 and set compare value
  TCNT1 = t1_load;
  OCR1A = t1_comp;
  
  //Enable Timer compare interrupt
  TIMSK1 |= _BV(OCIE1A);
    
  //------------------------------------//
    
  //Enable global interrupt
  sei();
}

void loop()
{
  delay(1000);
}

//ISR for PCINT2
ISR(PCINT2_vect)
{
  int led_state1 = (PIND & _BV(btn_pin1)) >> btn_pin1;
  int led_state2 = (PIND & _BV(btn_pin2)) >> btn_pin2;
  int led_state3 = (PIND & _BV(btn_pin3)) >> btn_pin3;
  
  if(led_state1 == 0) PORTD ^= _BV(led_pin1);  
  if(led_state2 == 0) PORTD ^= _BV(led_pin2);  
  if(led_state3 == 0) PORTD ^= _BV(led_pin3);   
}


//ISR for TIMER1 compare
ISR(TIMER1_COMPA_vect)
{
  TCNT1 = t1_load;
  PORTB ^= _BV(ledBlink_pin);
}