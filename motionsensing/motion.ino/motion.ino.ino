const int sensorPin = 2; // Assuming the sensor output is connected to digital pin 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorPin, INPUT); // Set the sensor pin as input
  pinMode(3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = digitalRead(sensorPin); // Read the digital input from the sensor
  
  Serial.println(sensorValue); // Print the sensor value to the serial monitor
  digitalWrite(3, (sensorValue == 1) ? HIGH : LOW);

  delay(20);
}
