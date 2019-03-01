/*
  Wiring for RF M4 Receiver
  Arduino Pins => M4 Receiver
  D8 => D0 (Button D)
  D9 => D1 (Button C)
  D10 => D2 (Button B)
  D11 => D3 (Button A)

  Wiring for Motor Controller
  Arduino Pins => Motor Controller
  D2 => DIR1
  D3 => PWM1
*/

// Pin constants
#define DIR_1 2
#define PWM_1 3
#define DIR_2 4
#define PWM_2 5
#define BUTTON_A_UP 11
#define BUTTON_B_DOWN 10
#define BUTTON_D_LOCK 8

// Other constants
#define MOTOR_STOP 0
#define MOTOR_MAX 255

// Globals
bool locked = true;
bool button_A_pressed = false;
bool button_B_pressed = false;
bool button_C_pressed = false;
bool button_D_pressed = false;
bool printedVars = false;
byte motor_speed = MOTOR_STOP;

void setup() {
  // Input pins
  pinMode(BUTTON_A_UP, INPUT);
  pinMode(BUTTON_B_DOWN, INPUT);
  pinMode(BUTTON_D_LOCK, INPUT);

  // Output pins
  pinMode(DIR_1, OUTPUT);
  pinMode(PWM_1, OUTPUT);
  pinMode(DIR_2, OUTPUT);
  pinMode(PWM_2, OUTPUT);

  // Serial output baud rate initialization
  Serial.begin(9600);
  printVars();
}

void printVars() {
  if (printedVars)
    return;
  Serial.print("locked: ");
  Serial.println(locked);
  Serial.print("button_A_pressed: ");
  Serial.println(button_A_pressed);
  Serial.print("button_B_pressed: ");
  Serial.println(button_B_pressed);
  Serial.print("button_C_pressed: ");
  Serial.println(button_C_pressed);
  Serial.print("button_D_pressed: ");
  Serial.println(button_D_pressed);
  Serial.print("motor_speed: ");
  Serial.println(motor_speed);
  printedVars = true;
}

void loop() {
  printedVars = false;
  // do nothing while locked - user needs to push unlock first
  if (digitalRead(BUTTON_D_LOCK) == HIGH) {
    locked = false;
    button_D_pressed = true;
    if (motor_speed == MOTOR_STOP)
      motor_speed = MOTOR_MAX;
    while (button_D_pressed) {
      printVars();
      if (digitalRead(BUTTON_D_LOCK) == LOW) {
        button_D_pressed = false;
        printedVars = false;
      }
    }
  }

  while (!locked) {
    while (digitalRead(BUTTON_A_UP) == HIGH) {
      button_A_pressed = true;
      digitalWrite(DIR_1, digitalRead(BUTTON_A_UP));
      analogWrite(PWM_1, motor_speed);
      while (button_A_pressed) {
        printVars();
        if (digitalRead(BUTTON_A_UP) == LOW) {
          analogWrite(PWM_1, MOTOR_STOP);
          button_A_pressed = false;
          printedVars = false;
        }
      }
    }

    while (digitalRead(BUTTON_B_DOWN) == HIGH) {
      button_B_pressed = true;
      digitalWrite(DIR_1, !digitalRead(BUTTON_B_DOWN));
      analogWrite(PWM_1, motor_speed);
      while (button_B_pressed) {
        printVars();
        if (digitalRead(BUTTON_B_DOWN) == LOW) {
          analogWrite(PWM_1, MOTOR_STOP);
          button_B_pressed = false;
          printedVars = false;
        }
      }
    }

    while (digitalRead(BUTTON_D_LOCK) == HIGH) {
      button_D_pressed = true;
      locked = true;
      while (button_D_pressed) {
        printVars();
        if (digitalRead(BUTTON_D_LOCK) == LOW) {
          button_D_pressed = false;
          printedVars = false;
        }
      }
    }
  }
}
