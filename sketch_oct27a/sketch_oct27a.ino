//Written By Nikodem Bartnik - nikodembartnik.pl
#include <Stepper.h>

// Define the pins for the stepper motor
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

// Create a Stepper object
Stepper stepper(200, STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);

// Joystick configuration
#define JOYSTICK_X A0  // Connect the joystick's X-axis to analog pin A0
#define JOYSTICK_Y A1  // Connect the joystick's Y-axis to analog pin A1

// Minimum speed for the stepper motor (adjust as needed)
#define MIN_SPEED 5

void setup() {
  stepper.setSpeed(MIN_SPEED);  // Initial speed (set to MIN_SPEED)
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  // Read the joystick values
  int joystickX = analogRead(JOYSTICK_X);
  int joystickY = analogRead(JOYSTICK_Y);

  // Map joystick Y-axis value to the stepper speed
  int speed = map(joystickY, 0, 1023, MIN_SPEED, 100);
  stepper.setSpeed(speed);

  // Check if the X-axis is beyond the dead zone to change direction
  if (joystickX < 462 || joystickX > 562) { // Adjust these values for your joystick
    if (joystickX < 462) {
      stepper.step(1);  // Rotate stepper motor in one direction
    } else {
      stepper.step(-1);  // Rotate stepper motor in the opposite direction
    }
  }

  delay(2);  // Add a small delay for stability (adjust as needed)
}
