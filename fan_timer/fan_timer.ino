
// 4 display pins
#define D1 11
#define D2 12
#define D3 13
#define D4 7

// 8 segments
#define SA 8
#define SB 10
#define SC 5
#define SD 3
#define SE 2
#define SF 9
#define SG 6
#define SDP 4

// global variables for state determination
unsigned long start_time_millis = 0;
unsigned long default_time = 45000;
unsigned long cooldown = 0;
int state = 0;
bool hasLight = false;

void setup() {
  // configure output pins
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(SA, OUTPUT);
  pinMode(SB, OUTPUT);
  pinMode(SC, OUTPUT);
  pinMode(SD, OUTPUT);
  pinMode(SE, OUTPUT);
  pinMode(SF, OUTPUT);
  pinMode(SG, OUTPUT);
  pinMode(SDP, OUTPUT);

}

void reset_timer() {
  start_time_millis = millis() + default_time;
}

void loop() {
  // state machine

  checkReset();

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
}
void runIdle() {
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
}




//
//                            HELPER
//
void checkReset() {

  int lightLevel = analogRead(A0);

  if (hasLight && lightLevel > 600) {
    hasLight = false;
    // TOOD: implements Lights out animation in non blocking manner!

  } else if (!hasLight && lightLevel < 300) {
    hasLight = true;
    cooldown = millis() + 1000;
    state = 1;
  }
}
void animationLightsOut() {

  digitalWrite(SB, HIGH);
  digitalWrite(SC, HIGH);
  digitalWrite(SE, HIGH);
  digitalWrite(SF, HIGH);
  digitalWrite(SDP, HIGH);

  digitalWrite(SA, LOW); //1
  digitalWrite(SG, HIGH); //2
  digitalWrite(SD, HIGH); //3

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);

  delay(100);

  digitalWrite(SA, HIGH);
  digitalWrite(SG, LOW);

  delay(100);

  digitalWrite(SG, HIGH);
  digitlaWrite(SD, LOW);

  delay(100);

  digitalWrite(SD, HIGH);

}










//
//                            DIGIT CONTROLLER
//

void renderCountdown(unsigned long delta) { // renders ulong (in ms) as hektoseconds: 45690 => 45.69

  for (int i = 1; i < 5; i++) {
    int d = 5-i;
    if (d == 3) {
      digitalWrite(SDP, LOW);
    }
    //int digit = (delta / ((int) pow(10, d))) % 10;
    int digit = (delta / pow10(d)) % 10;
    setDigit(digit);
    switch (i) {
      case 1:
        digitalWrite(D1, HIGH);
        delay(3);
        digitalWrite(D1, LOW);
        break;
      case 2:
        digitalWrite(D2, HIGH);
        delay(3);
        digitalWrite(D2, LOW);
        break;
      case 3:
        digitalWrite(D3, HIGH);
        delay(3);
        digitalWrite(D3, LOW);
        break;
      case 4:
        digitalWrite(D4, HIGH);
        delay(3);
        digitalWrite(D4, LOW);
        break;
    }
    
    digitalWrite(SDP, HIGH);
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
      digitalWrite(SA, LOW);
      digitalWrite(SB, LOW);
      digitalWrite(SC, LOW);
      digitalWrite(SD, LOW);
      digitalWrite(SE, LOW);
      digitalWrite(SF, LOW);
      digitalWrite(SG, HIGH);
      break;

    case 1:
      digitalWrite(SA, HIGH);
      digitalWrite(SB, LOW);
      digitalWrite(SC, LOW);
      digitalWrite(SD, HIGH);
      digitalWrite(SE, HIGH);
      digitalWrite(SF, HIGH);
      digitalWrite(SG, HIGH);
      break;

    case 2:
      digitalWrite(SA, LOW);
      digitalWrite(SB, LOW);
      digitalWrite(SC, HIGH);
      digitalWrite(SD, LOW);
      digitalWrite(SE, LOW);
      digitalWrite(SF, HIGH);
      digitalWrite(SG, LOW);
      break;

    case 3:
      digitalWrite(SA, LOW);
      digitalWrite(SB, LOW);
      digitalWrite(SC, LOW);
      digitalWrite(SD, LOW);
      digitalWrite(SE, HIGH);
      digitalWrite(SF, HIGH);
      digitalWrite(SG, LOW);
      break;

    case 4:
      digitalWrite(SA, HIGH);
      digitalWrite(SB, LOW);
      digitalWrite(SC, LOW);
      digitalWrite(SD, HIGH);
      digitalWrite(SE, HIGH);
      digitalWrite(SF, LOW);
      digitalWrite(SG, LOW);
      break;

    case 5:
      digitalWrite(SA, LOW);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, LOW);
      digitalWrite(SD, LOW);
      digitalWrite(SE, HIGH);
      digitalWrite(SF, LOW);
      digitalWrite(SG, LOW);
      break;

    case 6:
      digitalWrite(SA, LOW);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, LOW);
      digitalWrite(SD, LOW);
      digitalWrite(SE, LOW);
      digitalWrite(SF, LOW);
      digitalWrite(SG, LOW);
      break;

    case 7:
      digitalWrite(SA, LOW);
      digitalWrite(SB, LOW);
      digitalWrite(SC, LOW);
      digitalWrite(SD, HIGH);
      digitalWrite(SE, HIGH);
      digitalWrite(SF, HIGH);
      digitalWrite(SG, HIGH);
      break;

    case 8:
      digitalWrite(SA, LOW);
      digitalWrite(SB, LOW);
      digitalWrite(SC, LOW);
      digitalWrite(SD, LOW);
      digitalWrite(SE, LOW);
      digitalWrite(SF, LOW);
      digitalWrite(SG, LOW);
      break;

    case 9:
      digitalWrite(SA, LOW);
      digitalWrite(SB, LOW);
      digitalWrite(SC, LOW);
      digitalWrite(SD, LOW);
      digitalWrite(SE, HIGH);
      digitalWrite(SF, LOW);
      digitalWrite(SG, LOW);
      break;
    
  }
}

