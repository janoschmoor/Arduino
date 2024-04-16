
#define BUTTON_PIN 2

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
int sdp = 13;

unsigned long start_time_millis = 0;
unsigned long default_time = 45000;
unsigned long cooldown = 0;
int state = 0;
// 0 is idle
// 1 is startup
// 2 is running


void setup() {
  // put your setup code here, to run once:

  //Serial.begin(9600);

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

  reset_timer();
}

void reset_timer() {
  start_time_millis = millis() + default_time;
}

void loop() {
  switch (state) {
    case 0:
      runIdle();
      break;
    case 1:
      runStartup();
      break;
    case 2:
      runCountdown();
      break;
    case 3:
      runTheEnd();
      break;
  }
}

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



bool checkReset() {
  float buttonValue = analogRead(BUTTON_PIN);
  //Serial.println(buttonValue);
  // if (buttonValue > BUTTON_PRESSED_THRESHOLD) {
  //   Serial.println("Button released");
  //   // Additional code to execute when the button is released
  // } else if (buttonValue < BUTTON_RELEASED_THRESHOLD) {
  //   Serial.println("Button pressed");
  //   // Additional code to execute when the button is pressed
  // }
  if (buttonValue == 0) {
    return true;
  }
  return false;
}











//
//                            DIGIT CONTROLLER
//

void renderCountdown(unsigned long delta) {

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
