#define S1 16
#define S2 17

/* Functions Declaration */
void DIP_SETUP(void);
void UPDATE_MODE(void);
void DIP_DEBUG(void);

void DIP_SETUP(void) {
  pinMode(S1, INPUT_PULLUP);
  pinMode(S2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(S1), UPDATE_MODE, CHANGE);
  attachInterrupt(digitalPinToInterrupt(S2), UPDATE_MODE, CHANGE);
}

void UPDATE_MODE(void) {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) {
    int state1 = !digitalRead(S1);
    int state2 = !digitalRead(S2);

    if (state1 == 0 & state2 == 0) selectMode = 0;  // Neutral
    if (state1 == 1 & state2 == 0) selectMode = 1;  // Calibrate
    if (state1 == 0 & state2 == 1) selectMode = 2;  // Scout
    if (state1 == 1 & state2 == 1) selectMode = 3;  // Solve

    Serial.print("Selected Mode: ");
    Serial.println(selectMode);
  }

  last_interrupt_time = interrupt_time;
}

void DIP_DEBUG(void) {
  int state1 = !digitalRead(S1);
  int state2 = !digitalRead(S2);

  Serial.print("S1: ");
  Serial.print(state1);
  Serial.print(" S2: ");
  Serial.println(state2);

  delay(150);
}