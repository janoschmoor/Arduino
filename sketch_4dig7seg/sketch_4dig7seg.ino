// analog button pin 2
#define BUTTON_PIN 2

// 4 display pins
int d1 = 5;
int d2 = 4;
int d3 = 3;
int d4 = 2;

// 8 segments
int sa = 6;
int sb = 7;
int sc = 8;
int sd = 9;
int se = 10;
int sf = 11;
int sg = 12;
int sdp = 13;

// global variables for state determination
unsigned long start_time_millis = 0;
unsigned long default_time = 45000;
unsigned long cooldown = 0;
int state = 0;

void setup() {
  // configure output pins
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
  pinMode(sdp, OUTPUT);

  // analog input pin is input by default
}

void reset_timer() {
  start_time_millis = millis() + default_time;
}

void loop() {
  // state machine
  switch (state) {
    case 0:         // idle
      runIdle();
      break;
    case 1:         // startup
      runStartup();
      break;
    case 2:         // main countdown
      runCountdown();
      break;
    case 3:         // ending sequence
      runTheEnd();
      break;
  }
}


//
//                            RUN METHODS
//

void runCountdown() {
  unsigned long current_time_millis = millis();
  unsigned long delta = start_time_millis - current_time_millis;

  if (current_time_millis >= start_time_millis) {
    state = 3;
    cooldown = millis() + 6000;
    delta = 0;
  }

  renderCountdown(delta);
  
  if (checkReset()) {
    cooldown = millis() + 1000;
    state = 1;
  }
}
void runIdle() {
  if (checkReset()) {
    cooldown = millis() + 1000;
    state = 1;
  }
  delay(10);
}
void runStartup() {
  if (cooldown < millis()) {
    state = 2;
    reset_timer();
    delay(10);
  } else {
    renderCountdown(default_time);
  }
}
void runTheEnd() {

  unsigned long delta = cooldown - millis();

  if (millis() > cooldown) {
    state = 0;
  }
  if ((delta / 1000) % 2 == 0) {
    renderCountdown(0);
  } else {
    delay(10);
  }

  if (checkReset()) {
    state = 1;
    cooldown = millis()+1000;
  }
}




//
//                            HELPER
//
bool checkReset() {
  // check if the button is pressed
  return analogRead(BUTTON_PIN) == 0;
}











//
//                            DIGIT CONTROLLER
//

void renderCountdown(unsigned long delta) { // renders ulong (in ms) as hektoseconds: 45690 => 45.69

  for (int i = 1; i < 5; i++) {
    int d = 5-i;
    if (d == 3) {
      digitalWrite(sdp, LOW);
    }
    //int digit = (delta / ((int) pow(10, d))) % 10;
    int digit = (delta / pow10(d)) % 10;
    setDigit(digit);
    digitalWrite(d+1, HIGH);
    delay(3);
    digitalWrite(d+1, LOW);
    digitalWrite(sdp, HIGH);
    delay(1);
  }

}
unsigned long pow10(int n) { // to rid a flop error
  unsigned long result = 1;
  for (int i = 0; i < n; i++) {
    result *= 10;
  }
  return result;
}

void setDigit(int dig) { // digit encoding
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
