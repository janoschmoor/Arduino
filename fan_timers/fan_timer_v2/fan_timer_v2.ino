//
//                            SETUP
//


// 4 display pins
#define D1 2
#define D2 5
#define D3 6
#define D4 13
// 8 segments
#define SA 3
#define SB 7
#define SC 11
#define SD 9
#define SE 8
#define SF 4
#define SG 12
#define SDP 10
// global variables for state determination
unsigned long start_time_millis = 0;
unsigned long final_start_time_millis = 0;
unsigned long default_time = 45000;
unsigned long cooldown = 0;
int state = 0;
bool hasLight = false;
int selectedMessageIndex[] = {0,0};

// messages
const char* messages[] = {
  "i   ", "see ", "you ",
  "init", "poop",
  "poop", "poop", "poop",
  "god ", "sees", "you ",
  "plop", "plop", "plop",
  "load", "drop", "done",
  "ohh ", "nooo", "poop",
  "pee ", "and ", "go  ",
  "free", "up  ", "soon",
  "nice", "dude",
  "haha", "did ", "it  ",
  "hold", "nose", "now ",
  "not ", "done", "yet ",
  "go  ", "fast", "bro ",
  "nope", "not ", "yet ",
  "ohoh", "thts", "bad ",
  "dont", "use ", "so  ", "long",
  "stop", "it  ", "soon",
  "gg  ",
  "bye ", "bye ",
  "bust", "it  ", "out ",
  "i   ", "hear", "your", "fart",
  "call ", "117 ", "pls ",
  "nice", "butt",
  "snif", "snif", "yaay",
  "rush", "hour", "yay ",
  "nose", "clip", "on  ",
  "stay", "safe", "bro ",
  "u   ", "stnk", "dude",
  "u ok", "in  ", "here",
  "wow ", "its ", "so  ", "long", "pal ",
};
const int messageIndex[] = {
  0,3,
  3,2,
  5,3,
  8,3,
  11,3,
  14,3,
  17,3,
  20,3,
  23,3,
  26,2,
  28,3,
  31,3,
  34,3,
  37,3,
  40,3,
  43,3,
  46,4,
  50,3,
  53,1,
  54,2,
  56,3,
  59,4,
  63,3,
  66,2,
  68,3,
  71,3,
  74,3,
  77,3,
  80,3,
  83,3,
  86,5,
};

int numMessages = sizeof(messageIndex) / sizeof(messageIndex[0]) / 2;

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

  // Serial.begin(9600);

}

void reset_timer() {
  start_time_millis = millis() + default_time;
  final_start_time_millis = millis();
}



//
//                          LOOP
//

void loop() {
  checkReset();
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
    // Remove the case 4 and the call to the runFunkyText() function
    // case 4:         // funky text - decommisioned
    //   runFunkyText();
    //   break;
    case 5:         // count up
      runCountup();
      break;
  }
}
void runCountdown() {
  unsigned long current_time_millis = millis();
  unsigned long delta = start_time_millis - current_time_millis;

  if (current_time_millis >= start_time_millis) {
    state = 3;
    cooldown = millis() + 1500;
    delta = 0;
    chooseMessage();
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
// void runTheEnd() {

//   unsigned long delta = cooldown - millis();

//   if (millis() > cooldown) {
//     state = 5; // here was 4 to render funky text
//     cooldown = millis() + 10000;
//   }
//   if ((delta / 1000) % 2 == 0) {
//     // renderCountdown(0);
//     renderText();
//   } else {
//     delay(10);
//   }
// }

void runTheEnd() {

  if (millis() > cooldown) {
    // advance to next message
    if (!(++selectedMessageIndex[0] < selectedMessageIndex[1])) {
      state = 5;
    } else {
      cooldown = millis() + 1500;
    }
  } else if (millis() + 500 < cooldown) {
    renderWord(messages[selectedMessageIndex[0]]);
  }
}

// void runFunkyText() {

//   if (millis() + 3000 > cooldown) {
//     renderText();
//   }

//   if (millis() > cooldown) {
//     state = 0;
//   }
// }
void runCountup() {

  unsigned long current_time_millis = millis();
  unsigned long delta = final_start_time_millis - current_time_millis;

  renderCountdownMinutes(-delta);
  
}




//
//                            HELPER
//
void chooseMessage() {
  int index = random(0, numMessages) * 2;
  selectedMessageIndex[0] = messageIndex[index];
  selectedMessageIndex[1] = selectedMessageIndex[0] + messageIndex[index+1];
}
void checkReset() {

  int lightLevel = analogRead(A3);

  if (hasLight && lightLevel > 600) {
    hasLight = false;

    if (state > 0) {
      animationLightsOut();
    }

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

  digitalWrite(SA, HIGH); //1
  digitalWrite(SG, HIGH); //2
  digitalWrite(SD, HIGH); //3

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);

  unsigned long target;
  
  for (int i = 0; i < 3; i++) {
    target = millis() + 100;
    digitalWrite(SA, LOW);
    while (millis() < target) {
      checkReset();
      if (state == 1) {return;}
      delay(10);
    }

    digitalWrite(SA, HIGH);
    digitalWrite(SG, LOW);

    target = millis() + 100;
    while (millis() < target) {
      checkReset();
      if (state == 1) {return;}
      delay(10);
    }

    digitalWrite(SG, HIGH);
    digitalWrite(SD, LOW);

    target = millis() + 100;
    while (millis() < target) {
      checkReset();
      if (state == 1) {return;}
      delay(10);
    }

    digitalWrite(SD, HIGH);
  }

  state = 0;

}










//
//                            DIGIT CONTROLLER
//
void renderWord(const char* word) {
  for (int i = 0; i < 4; i++) {
    renderLetter(word[i]);
    switch (i) {
      case 0:
        digitalWrite(D1, HIGH);
        delay(3);
        digitalWrite(D1, LOW);
        break;
      case 1:
        digitalWrite(D2, HIGH);
        delay(3);
        digitalWrite(D2, LOW);
        break;
      case 2:
        digitalWrite(D3, HIGH);
        delay(3);
        digitalWrite(D3, LOW);
        break;
      case 3:
        digitalWrite(D4, HIGH);
        delay(3);
        digitalWrite(D4, LOW);
        break;
    }
  }

}
void renderCountdownMinutes(unsigned long delta) {
  unsigned long minutes = delta / 60000;
  unsigned long seconds = (delta % 60000) / 1000;

  // Render minutes
  int digit1 = minutes / 10;
  int digit2 = minutes % 10;
  setDigit(digit1);
  digitalWrite(D1, HIGH);
  delay(3);
  digitalWrite(D1, LOW);
  setDigit(digit2);
  digitalWrite(SDP, LOW);
  digitalWrite(D2, HIGH);
  delay(3);
  digitalWrite(SDP, HIGH);
  digitalWrite(D2, LOW);

  // Render seconds
  digit1 = seconds / 10;
  digit2 = seconds % 10;
  setDigit(digit1);
  digitalWrite(D3, HIGH);
  delay(3);
  digitalWrite(D3, LOW);
  setDigit(digit2);
  digitalWrite(D4, HIGH);
  delay(3);
  digitalWrite(D4, LOW);
}
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

void renderText() {
  //String test = "POOP";
  
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);

  digitalWrite(SA, LOW);
  digitalWrite(SB, LOW);
  digitalWrite(SC, HIGH);
  digitalWrite(SD, HIGH);
  digitalWrite(SE, LOW);
  digitalWrite(SF, LOW);
  digitalWrite(SG, LOW);

  delay(5);

  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);

  digitalWrite(SA, LOW);
  digitalWrite(SB, LOW);
  digitalWrite(SC, LOW);
  digitalWrite(SD, LOW);
  digitalWrite(SE, LOW);
  digitalWrite(SF, LOW);
  digitalWrite(SG, HIGH);

  delay(5);
  
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);

  delay(5);

  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);

  digitalWrite(SA, LOW);
  digitalWrite(SB, LOW);
  digitalWrite(SC, HIGH);
  digitalWrite(SD, HIGH);
  digitalWrite(SE, LOW);
  digitalWrite(SF, LOW);
  digitalWrite(SG, LOW);

  delay(5);

  digitalWrite(D4, LOW);

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
void renderLetter(char c) {
  switch(c) {
    case '0':
      setDigit(0);
      break;
    case '1':
      setDigit(1);
      break;
    case '2':
      setDigit(2);
      break;
    case '3':
      setDigit(3);
      break;
    case '4':
      setDigit(4);
      break;
    case '5':
      setDigit(5);
      break;
    case '6':
      setDigit(6);
      break;
    case '7':
      setDigit(7);
      break;
    case '8':
      setDigit(8);
      break;
    case '9':
      setDigit(9);
      break;

    case 'a':
      digitalWrite(SA, LOW);
      digitalWrite(SB, LOW);
      digitalWrite(SC, LOW);
      digitalWrite(SD, HIGH);
      digitalWrite(SE, LOW);
      digitalWrite(SF, LOW);
      digitalWrite(SG, LOW);
      break;
    case 'b':
      digitalWrite(SA, HIGH);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, LOW);
      digitalWrite(SD, LOW);
      digitalWrite(SE, LOW);
      digitalWrite(SF, LOW);
      digitalWrite(SG, LOW);
      break;
    case 'c':
      digitalWrite(SA, HIGH);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, HIGH);
      digitalWrite(SD, LOW);
      digitalWrite(SE, LOW);
      digitalWrite(SF, HIGH);
      digitalWrite(SG, LOW);
      break;
    case 'd':
      digitalWrite(SA, HIGH);
      digitalWrite(SB, LOW);
      digitalWrite(SC, LOW);
      digitalWrite(SD, LOW);
      digitalWrite(SE, LOW);
      digitalWrite(SF, HIGH);
      digitalWrite(SG, LOW);
      break;
    case 'e':
      digitalWrite(SA, LOW);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, HIGH);
      digitalWrite(SD, LOW);
      digitalWrite(SE, LOW);
      digitalWrite(SF, LOW);
      digitalWrite(SG, LOW);
      break;
    case 'f':
      digitalWrite(SA, LOW);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, HIGH);
      digitalWrite(SD, HIGH);
      digitalWrite(SE, LOW);
      digitalWrite(SF, LOW);
      digitalWrite(SG, LOW);
      break;
    case 'g':
      digitalWrite(SA, LOW);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, LOW);
      digitalWrite(SD, LOW);
      digitalWrite(SE, LOW);
      digitalWrite(SF, LOW);
      digitalWrite(SG, HIGH);
      break;
    case 'h':
      digitalWrite(SA, HIGH);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, LOW);
      digitalWrite(SD, HIGH);
      digitalWrite(SE, LOW);
      digitalWrite(SF, LOW);
      digitalWrite(SG, LOW);
      break;
    case 'i':
      digitalWrite(SA, HIGH);
      digitalWrite(SB, LOW);
      digitalWrite(SC, LOW);
      digitalWrite(SD, HIGH);
      digitalWrite(SE, HIGH);
      digitalWrite(SF, HIGH);
      digitalWrite(SG, HIGH);
      break;
    case 'l':
      digitalWrite(SA, HIGH);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, HIGH);
      digitalWrite(SD, LOW);
      digitalWrite(SE, LOW);
      digitalWrite(SF, LOW);
      digitalWrite(SG, HIGH);
      break;
    case 'n':
      digitalWrite(SA, HIGH);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, LOW);
      digitalWrite(SD, HIGH);
      digitalWrite(SE, LOW);
      digitalWrite(SF, HIGH);
      digitalWrite(SG, LOW);
      break;
    case 'o':
      digitalWrite(SA, HIGH);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, LOW);
      digitalWrite(SD, LOW);
      digitalWrite(SE, LOW);
      digitalWrite(SF, HIGH);
      digitalWrite(SG, LOW);
      break;
    case 'p':
      digitalWrite(SA, LOW);
      digitalWrite(SB, LOW);
      digitalWrite(SC, HIGH);
      digitalWrite(SD, HIGH);
      digitalWrite(SE, LOW);
      digitalWrite(SF, LOW);
      digitalWrite(SG, LOW);
      break;
    case 'r':
      digitalWrite(SA, HIGH);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, HIGH);
      digitalWrite(SD, HIGH);
      digitalWrite(SE, LOW);
      digitalWrite(SF, HIGH);
      digitalWrite(SG, LOW);
      break;
    case 's':
      digitalWrite(SA, LOW);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, LOW);
      digitalWrite(SD, LOW);
      digitalWrite(SE, HIGH);
      digitalWrite(SF, LOW);
      digitalWrite(SG, LOW);
      break;
    case 't':
      digitalWrite(SA, HIGH);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, HIGH);
      digitalWrite(SD, LOW);
      digitalWrite(SE, LOW);
      digitalWrite(SF, LOW);
      digitalWrite(SG, LOW);
      break;
    case 'u':
      digitalWrite(SA, HIGH);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, LOW);
      digitalWrite(SD, LOW);
      digitalWrite(SE, LOW);
      digitalWrite(SF, HIGH);
      digitalWrite(SG, HIGH);
      break;
    case 'y':
      digitalWrite(SA, HIGH);
      digitalWrite(SB, LOW);
      digitalWrite(SC, LOW);
      digitalWrite(SD, LOW);
      digitalWrite(SE, HIGH);
      digitalWrite(SF, LOW);
      digitalWrite(SG, LOW);
      break;
    default:
      digitalWrite(SA, HIGH);
      digitalWrite(SB, HIGH);
      digitalWrite(SC, HIGH);
      digitalWrite(SD, HIGH);
      digitalWrite(SE, HIGH);
      digitalWrite(SF, HIGH);
      digitalWrite(SG, HIGH);
      break;
  }
}