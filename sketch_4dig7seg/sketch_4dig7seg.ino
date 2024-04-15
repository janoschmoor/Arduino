
int d1 = 5;
int d2 = 4;
int d3 = 3;
int d4 = 2;

int sa = 6;
int sb = 7;
int sc = 8;
int sd = 9;
int se = 10;
int sf = 11;
int sg = 12;

unsigned long start_time_millis = 0;
int state = 0;


void setup() {
  // put your setup code here, to run once:

  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);

  pinMode(sa, OUTPUT);
  pinMode(sb, OUTPUT);
  pinMode(sc, OUTPUT);
  pinMode(sd, OUTPUT);
  pinMode(se, OUTPUT);
  pinMode(sf, OUTPUT);
  pinMode(sg, OUTPUT);

  reset_timer();
}

void reset_timer() {
  start_time_millis = millis() + 48000;
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(d1, HIGH);

  unsigned long current_millis = millis();
  unsigned long delta = start_time_millis - current_time_millis;

  int dig = delta % 1000;
  setDigit(time_hs);

  delay(1);
}

void setDigit(int dig) {
  switch (dig) {
    case 0:
      digitalWrite(sa, LOW);
      digitalWrite(sb, LOW);
      digitalWrite(sc, LOW);
      digitalWrite(sd, LOW);
      digitalWrite(se, LOW);
      digitalWrite(sf, LOW);
      digitalWrite(sg, HIGH);
      break;

    case 1:
      digitalWrite(sa, HIGH);
      digitalWrite(sb, LOW);
      digitalWrite(sc, LOW);
      digitalWrite(sd, HIGH);
      digitalWrite(se, HIGH);
      digitalWrite(sf, HIGH);
      digitalWrite(sg, HIGH);
      break;

    case 2:
      digitalWrite(sa, LOW);
      digitalWrite(sb, LOW);
      digitalWrite(sc, HIGH);
      digitalWrite(sd, LOW);
      digitalWrite(se, LOW);
      digitalWrite(sf, HIGH);
      digitalWrite(sg, LOW);
      break;

    case 3:
      digitalWrite(sa, LOW);
      digitalWrite(sb, LOW);
      digitalWrite(sc, LOW);
      digitalWrite(sd, LOW);
      digitalWrite(se, HIGH);
      digitalWrite(sf, HIGH);
      digitalWrite(sg, LOW);
      break;

    case 4:
      digitalWrite(sa, HIGH);
      digitalWrite(sb, LOW);
      digitalWrite(sc, LOW);
      digitalWrite(sd, HIGH);
      digitalWrite(se, HIGH);
      digitalWrite(sf, LOW);
      digitalWrite(sg, LOW);
      break;

    case 5:
      digitalWrite(sa, LOW);
      digitalWrite(sb, HIGH);
      digitalWrite(sc, LOW);
      digitalWrite(sd, LOW);
      digitalWrite(se, HIGH);
      digitalWrite(sf, LOW);
      digitalWrite(sg, LOW);
      break;

    case 6:
      digitalWrite(sa, LOW);
      digitalWrite(sb, HIGH);
      digitalWrite(sc, LOW);
      digitalWrite(sd, LOW);
      digitalWrite(se, LOW);
      digitalWrite(sf, LOW);
      digitalWrite(sg, LOW);
      break;

    case 7:
      digitalWrite(sa, LOW);
      digitalWrite(sb, LOW);
      digitalWrite(sc, LOW);
      digitalWrite(sd, HIGH);
      digitalWrite(se, HIGH);
      digitalWrite(sf, HIGH);
      digitalWrite(sg, HIGH);
      break;

    case 8:
      digitalWrite(sa, LOW);
      digitalWrite(sb, LOW);
      digitalWrite(sc, LOW);
      digitalWrite(sd, LOW);
      digitalWrite(se, LOW);
      digitalWrite(sf, LOW);
      digitalWrite(sg, LOW);
      break;

    case 9:
      digitalWrite(sa, LOW);
      digitalWrite(sb, LOW);
      digitalWrite(sc, LOW);
      digitalWrite(sd, LOW);
      digitalWrite(se, HIGH);
      digitalWrite(sf, LOW);
      digitalWrite(sg, LOW);
      break;
    
  }
}
