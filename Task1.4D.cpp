//Pins
const uint8_t btn_pin = PD2;
const uint8_t led_pin = PD6;
const uint8_t ledYellow_pin = PD5;
const uint8_t ledOrange_pin = PD4;
const uint8_t ledRed_pin = PD3;
const uint8_t ledBlink_pin = PB5;

//Counter and compare values
const uint16_t t1_load = 0;
const uint16_t t1_comp = 31250;

//Global variable
int celsius = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(A1, INPUT);
  
  //Set btn_pin to input with pull up
  DDRD &= ~_BV(btn_pin);
  PORTD |= _BV(btn_pin); 
    
  //Set led_pin to output
  DDRD |= _BV(led_pin);
  DDRD |= _BV(ledYellow_pin);
  DDRD |= _BV(ledOrange_pin);
  DDRD |= _BV(ledRed_pin);
  DDRB |= _BV(ledBlink_pin);
  
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
  
  //Set INT0 to interrupt by Falling edge
  EICRA |= _BV(ISC01);
  EICRA &= ~_BV(ISC00);
   
  //Enable INT0
  EIMSK |= _BV(INT0);
  
  //Enable global interrupt
  sei();  
}

void loop()
{
  //Temperature adjustment implemented by zhtuhin4
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  
  //Read led state
  int led_state = (PIND & _BV(led_pin)) >> led_pin;
  int ledBlink_state = (PINB & _BV(ledBlink_pin)) >> ledBlink_pin;
  
  
  Serial.print(celsius);
  Serial.print(" Celsius,");
  
  Serial.print(" Led State:");
  Serial.println(led_state);
  
  
  //Light up appropriate LED accordingly to the temp
  if(celsius < 50){
    PORTD &= ~_BV(ledYellow_pin);
    PORTD &= ~_BV(ledOrange_pin);
    PORTD &= ~_BV(ledRed_pin);
  }
  else if(celsius >= 50 && celsius < 75){
  	PORTD |= _BV(ledYellow_pin);
    PORTD &= ~_BV(ledOrange_pin);
    PORTD &= ~_BV(ledRed_pin);  
  }
  else if(celsius >= 75 && celsius < 100){
    PORTD |= _BV(ledYellow_pin);
    PORTD |= _BV(ledOrange_pin);
    PORTD &= ~_BV(ledRed_pin);
  }
  else{
    PORTD |= _BV(ledYellow_pin);
    PORTD |= _BV(ledOrange_pin);
    PORTD |= _BV(ledRed_pin);
  }  
  delay(1000);
}

//ISR for INT0
ISR(INT0_vect){
  PORTD ^= _BV(led_pin);
}

//ISR for TIMER1 compare
ISR(TIMER1_COMPA_vect){
  TCNT1 = t1_load;
  PORTB ^= _BV(ledBlink_pin);
}