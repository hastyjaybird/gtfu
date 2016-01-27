//this is for arduino yun

#define LEDPIN 11    // LED connected to digital pin 11
#define MAXPWM 169   // this PWM corresponds to 3.3v with a 5v power supply
#define MINPWM 3   // this PWM is when the lights first start to light up
#define FADETIME 60 * 60 * 1000
#define DELAYVALUE FADETIME / ( MAXPWM - MINPWM )

void setup() {
  Serial.begin(300);
  pinMode(LEDPIN,OUTPUT);
  setPwmFrequency(LEDPIN,1); // divisor of 1 is probably 31250 Hz
}

void loop() {
  if (Serial.available()) {
    char readChar = Serial.read();
    Serial.println(readChar);
    if (readChar == 'r'){ // sunrise
      sunrise();
    }
    if (readChar == 's'){ // sunset
      sunset();
    }
  }
}

void sunrise() {
  for(int fadeValue = MINPWM ; fadeValue <= MAXPWM; fadeValue +=1) {
    analogWrite(LEDPIN, fadeValue);
    delay(DELAYVALUE);
  }
}

void sunset() {
   for(int fadeValue = MAXPWM ; fadeValue >= 0; fadeValue -=1) {
     analogWrite(LEDPIN, fadeValue);
     delay(DELAYVALUE);
   }
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
    case 1:
      mode = 0x01;
      break;
    case 8:
      mode = 0x02;
      break;
    case 64:
      mode = 0x03;
      break;
    case 256:
      mode = 0x04;
      break;
    case 1024:
      mode = 0x05;
      break;
    default:
      return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    }
    else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  }
  else if(pin == 3 || pin == 11) {
    switch(divisor) {
    case 1:
      mode = 0x01;
      break;
    case 8:
      mode = 0x02;
      break;
    case 32:
      mode = 0x03;
      break;
    case 64:
      mode = 0x04;
      break;
    case 128:
      mode = 0x05;
      break;
    case 256:
      mode = 0x06;
      break;
    case 1024:
      mode = 0x7;
      break;
    default:
      return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
