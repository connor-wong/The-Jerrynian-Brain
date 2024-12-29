/* Motor Encoder Pins */
#define L_ENCODER_A 18
#define L_ENCODER_B 19
#define R_ENCODER_A 35
#define R_ENCODER_B 34

/* Functions Declaration */
void ENCODER_SETUP(void);
void UPDATE_LEFT_ENCODER(void);
void UPDATE_RIGHT_ENCODER(void);

/* Turn Control */
void TURN_BACK(void);
void LEFT_ABOUT_TURN(void);
void RIGHT_ABOUT_TURN(void);
void LEFT_HALF_TURN(void);
void RIGHT_HALF_TURN(void);

void ENCODER_SETUP(void) {
  /* Motor Encoder */
  pinMode(L_ENCODER_A, INPUT);
  pinMode(L_ENCODER_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(L_ENCODER_A), UPDATE_LEFT_ENCODER, RISING);
  attachInterrupt(digitalPinToInterrupt(L_ENCODER_B), UPDATE_LEFT_ENCODER, RISING);

  pinMode(R_ENCODER_A, INPUT);
  pinMode(R_ENCODER_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(R_ENCODER_A), UPDATE_RIGHT_ENCODER, RISING);
  attachInterrupt(digitalPinToInterrupt(R_ENCODER_B), UPDATE_RIGHT_ENCODER, RISING);
}

void UPDATE_LEFT_ENCODER(void) {
  leftEncoderValue += 1;
}

void UPDATE_RIGHT_ENCODER(void) {
  rightEncoderValue += 1;
}

void TURN_BACK(void) {
  leftEncoderValue = 0;
  rightEncoderValue = 0;

  leftEncoder = 0;
  rightEncoder = 0;

  leftEncoderValue += 100;
  rightEncoderValue += 100;

  while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
    dif = leftEncoder - leftEncoderValue + 100;
    leftBase = int(70 + 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    rightBase = int(70 + 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    TURN_RIGHT();
  }

  leftBase = 180;
  rightBase = 180;

  leftEncoderValue += 725;
  rightEncoderValue += 725;

  while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
    TURN_RIGHT();
  }

  leftEncoderValue += 100;
  rightEncoderValue += 100;

  while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
    dif = leftEncoder - leftEncoderValue + 100;
    leftBase = int(180 - 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    rightBase = int(180 - 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    TURN_RIGHT();
  }

  BRAKE();
  leftBase = 180;
  rightBase = 180;
  leftEncoderValue = 0;
  rightEncoderValue = 0;
  leftEncoder = 0;
  rightEncoder = 0;
}

void LEFT_ABOUT_TURN(void) {
  leftEncoderValue = 0;
  rightEncoderValue = 0;

  leftEncoder = 0;
  rightEncoder = 0;

  leftBase = 70;
  rightBase = 70;

  rightEncoderValue += 100;
  leftEncoderValue += 100;

  while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
    dif = leftEncoder - leftEncoderValue + 100;
    leftBase = int(70 + 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    rightBase = int(70 + 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    TURN_LEFT();
  }

  leftBase = 180;
  rightBase = 180;

  leftEncoderValue += 255;
  rightEncoderValue += 255;

  while (rightEncoder <= rightEncoderValue) {
    TURN_LEFT();
  }

  leftEncoderValue += 100;
  rightEncoderValue += 100;

  while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
    dif = leftEncoder - leftEncoderValue + 100;
    leftBase = int(180 - 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    rightBase = int(180 - 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    TURN_LEFT();
  }

  BRAKE();
  leftBase = 180;
  rightBase = 180;
  leftEncoderValue = 0;
  rightEncoderValue = 0;
  leftEncoder = 0;
  rightEncoder = 0;
}

void RIGHT_ABOUT_TURN(void) {
  leftEncoderValue = 0;
  rightEncoderValue = 0;

  leftEncoder = 0;
  rightEncoder = 0;

  leftEncoderValue += 100;
  rightEncoderValue += 100;

  leftBase = 70;
  rightBase = 70;

  while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
    dif = leftEncoder - leftEncoderValue + 100;
    leftBase = int(70 + 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    rightBase = int(70 + 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    TURN_RIGHT();
  }

  rightBase = 180;
  leftBase = 180;
  rightEncoderValue += 240;
  leftEncoderValue += 240;

  while (rightEncoder <= rightEncoderValue) {
    TURN_RIGHT();
  }
  rightEncoderValue += 100;
  leftEncoderValue += 100;

  while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
    dif = leftEncoder - leftEncoderValue + 100;
    leftBase = int(180 - 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    rightBase = int(180 - 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    TURN_RIGHT();
  }

  BRAKE();
  leftBase = 180;
  rightBase = 180;
  leftEncoderValue = 0;
  rightEncoderValue = 0;
  leftEncoder = 0;
  rightEncoder = 0;
}

void LEFT_HALF_TURN(void) {
  leftEncoderValue = 0;
  rightEncoderValue = 0;

  leftEncoder = 0;
  rightEncoder = 0;

  leftBase = 70;
  rightBase = 70;

  rightEncoderValue += 100;
  leftEncoderValue += 100;

  while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
    dif = leftEncoder - leftEncoderValue + 100;
    rightBase = int(70 + 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    leftBase = int(70 + 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    TURN_LEFT();
  }

  leftBase = 180;
  rightBase = 180;

  rightEncoderValue += 255;
  leftEncoderValue += 255;

  while (rightEncoder <= rightEncoderValue) {
    TURN_LEFT();
  }

  rightEncoderValue += 100;
  leftEncoderValue += 100;

  while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
    dif = leftEncoder - leftEncoderValue + 100;
    leftBase = int(180 - 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    rightBase = int(180 - 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    TURN_LEFT();
  }

  BRAKE();
  leftBase = 180;
  rightBase = 180;
  leftEncoderValue = 0;
  rightEncoderValue = 0;
  leftEncoder = 0;
  rightEncoder = 0;
}

void RIGHT_HALF_TURN(void) {
  leftEncoderValue = 0;
  rightEncoderValue = 0;

  leftEncoder = 0;
  rightEncoder = 0;

  rightEncoderValue += 100;
  leftEncoderValue += 100;

  rightBase = 70;
  leftBase = 70;

  while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
    dif = leftEncoder - leftEncoderValue + 100;
    rightBase = int(70 + 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    leftBase = int(70 + 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    TURN_RIGHT();
  }

  rightBase = 180;
  leftBase = 180;

  rightEncoderValue += 1;
  leftEncoderValue += 1;

  while (rightEncoder <= rightEncoderValue) {
    TURN_RIGHT();
  }

  rightEncoderValue += 100;
  leftEncoderValue += 100;

  while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
    dif = leftEncoder - leftEncoderValue + 100;
    leftBase = int(180 - 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    rightBase = int(180 - 110 / (1 + pow(2.73, ((50 - dif) * 0.05))));
    TURN_RIGHT();
  }

  BRAKE();
  leftBase = 180;
  rightBase = 180;
  leftEncoderValue = 0;
  rightEncoderValue = 0;
  leftEncoder = 0;
  rightEncoder = 0;
}