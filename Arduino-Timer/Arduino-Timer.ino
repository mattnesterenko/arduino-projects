unsigned short top;
unsigned short comp;

void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  
  TCCR2A = _BV(WGM21) | _BV(WGM20) | _BV(COM2B1);
  TCCR2B = _BV(WGM22) | _BV(CS20);

  OCR2A = 255;
  OCR2B = 128;
}

void loop() {
  TCCR2B = _BV(WGM22) | (digitalRead(8) ? _BV(CS20) : 0) | (digitalRead(9) ? _BV(CS21) : 0) | (digitalRead(10) ? _BV(CS22) : 0);
  TCCR2A = _BV(WGM21) | _BV(WGM20) | _BV(COM2B1) | (digitalRead(11) ? _BV(COM2B0) : 0);

  top = map(analogRead(0), 0, 1024, 1, 255);

  if (abs(OCR2A - top) > 5) {
    OCR2A = top;
  }

  comp = map(analogRead(1), 0, 1024, 0, top);
  OCR2B = comp;
}

