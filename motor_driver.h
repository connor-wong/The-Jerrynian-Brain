/* Motor Driver Pins */
#define L_MOTOR_IN_1 13
#define L_MOTOR_IN_2 12

#define R_MOTOR_IN_1 14
#define R_MOTOR_IN_2 27
#define L_PWM 2
#define R_PWM 4
#define MOTOR_EN 5

/* Functions Declaration */
void MOTOR_SETUP(void);
void ENABLE_MOTOR(void);
void DISABLE_MOTOR(void);
void FORWARD(void);
void REVERSE(void);
void TURN_LEFT(void);
void TURN_RIGHT(void);
void STOP(void);
void BRAKE(void);

/* Left Motor Functions */
void LEFT_FORWARD(void);
void LEFT_REVERSE(void);
void LEFT_BRAKE(void);
void LEFT_FORWARD_BASE(void);
void LEFT_REVERSE_BASE(void);

/* Right Motor Functions */
void RIGHT_FORWARD(void);
void RIGHT_REVERSE(void);
void RIGHT_BRAKE(void);
void RIGHT_FORWARD_BASE(void);
void RIGHT_REVERSE_BASE(void);

/* PWM Functions */
void WRITE_PWM(void);
void WRITE_BASE_PWM(void);

void MOTOR_SETUP(void) {
  pinMode(MOTOR_EN, OUTPUT);

  /* Left Motor */
  pinMode(L_PWM, OUTPUT);
  pinMode(L_MOTOR_IN_1, OUTPUT);
  pinMode(L_MOTOR_IN_2, OUTPUT);

  /* Right Motor */
  pinMode(R_PWM, OUTPUT);
  pinMode(R_MOTOR_IN_1, OUTPUT);
  pinMode(R_MOTOR_IN_2, OUTPUT);

  ENABLE_MOTOR();
}

void ENABLE_MOTOR(void) {
  digitalWrite(MOTOR_EN, HIGH);
}

void DISABLE_MOTOR(void) {
  digitalWrite(MOTOR_EN, LOW);
}

void LEFT_FORWARD(void) {
  digitalWrite(L_MOTOR_IN_1, HIGH);
  digitalWrite(L_MOTOR_IN_2, LOW);
}

void LEFT_REVERSE(void) {
  digitalWrite(L_MOTOR_IN_1, LOW);
  digitalWrite(L_MOTOR_IN_2, HIGH);
}

void LEFT_BRAKE(void) {
  digitalWrite(L_MOTOR_IN_1, HIGH);
  digitalWrite(L_MOTOR_IN_2, HIGH);
}

void LEFT_FORWARD_BASE(void) {
  ENABLE_MOTOR();
  LEFT_FORWARD();
  analogWrite(L_PWM, leftBase);
}

void LEFT_REVERSE_BASE(void) {
  ENABLE_MOTOR();
  LEFT_REVERSE();
  analogWrite(L_PWM, leftBase);
}

void RIGHT_FORWARD(void) {
  digitalWrite(R_MOTOR_IN_1, HIGH);
  digitalWrite(R_MOTOR_IN_2, LOW);
}

void RIGHT_REVERSE(void) {
  digitalWrite(R_MOTOR_IN_1, LOW);
  digitalWrite(R_MOTOR_IN_2, HIGH);
}

void RIGHT_BRAKE(void) {
  digitalWrite(R_MOTOR_IN_1, HIGH);
  digitalWrite(R_MOTOR_IN_2, HIGH);
}

void RIGHT_FORWARD_BASE(void) {
  ENABLE_MOTOR();
  RIGHT_FORWARD();
  analogWrite(R_PWM, rightBase);
}

void RIGHT_REVERSE_BASE(void) {
  ENABLE_MOTOR();
  RIGHT_REVERSE();
  analogWrite(R_PWM, rightBase);
}

void WRITE_PWM(void) {
  analogWrite(L_PWM, leftPWM);
  analogWrite(R_PWM, rightPWM);
}

void WRITE_BASE_PWM(void) {
  analogWrite(L_PWM, leftBase);
  analogWrite(R_PWM, rightBase);
}