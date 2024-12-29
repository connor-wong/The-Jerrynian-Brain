/* Functions Declaration */
void FORWARD(void);
void REVERSE(void);
void BRAKE(void);
void FORWARD_BASE(void);
void REVERSE_BASE(void);
void TURN_RIGHT(void);
void TURN_LEFT(void);

void FORWARD(void) {
  LEFT_FORWARD();
  RIGHT_FORWARD();
  WRITE_PWM();
}

void REVERSE(void) {
  LEFT_REVERSE();
  RIGHT_REVERSE();
  WRITE_PWM();
}

void BRAKE(void) {
  LEFT_BRAKE();
  RIGHT_BRAKE();
  delay(75);
}

void FORWARD_BASE(void) {
  LEFT_FORWARD();
  RIGHT_FORWARD();
  WRITE_BASE_PWM();
}

void REVERSE_BASE(void) {
  LEFT_REVERSE();
  RIGHT_REVERSE();
  WRITE_BASE_PWM();
}

void TURN_RIGHT(void) {
  LEFT_FORWARD();
  RIGHT_REVERSE();
  WRITE_BASE_PWM();
}

void TURN_LEFT(void) {
  LEFT_REVERSE();
  RIGHT_FORWARD();
  WRITE_BASE_PWM();
}