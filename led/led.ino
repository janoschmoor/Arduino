
int r = 13;
int g = 11;
int b = 12;

int i = 2;
int j = 3;
int k = 4;


void setup() {
  
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);

}

void loop() {

  k = (k + 1) % 100;
  
  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);

  digitalWrite(r, HIGH);
  delay(i);  
  digitalWrite(r, LOW);

  digitalWrite(g, HIGH);
  delay(j);  
  digitalWrite(g, LOW);

  digitalWrite(b, HIGH);
  delay(k);  
  digitalWrite(b, LOW);
  

  // for (int n = 0; n < 256; n++) {
  //   if (n = i) {
  //     digitalWrite(r, LOW);
  //   }
  //   if (n = j) {
  //     digitalWrite(g, LOW);
  //   }
  //   if (n = k) {
  //     digitalWrite(b, LOW);
  //   }

  
  // }



}
