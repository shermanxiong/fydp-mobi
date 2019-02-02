/*
  Wiring forRF M4 Receiver
  Arduino Pins -> M4 Receiver
  D12 -> D3
  D11 -> D2
*/

// Pin constants
const int BUTTON_UP = 12;
const int BUTTON_DOWN = 11;

void setup() {
  pinMode(BUTTON_UP, INPUT);
  pinMode(BUTTON_DOWN, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(BUTTON_UP) == HIGH)
    Serial.print("Button up pressed\n");
  else if (digitalRead(BUTTON_DOWN) == HIGH)
    Serial.print("Button down pressed\n");
}
