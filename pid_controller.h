/* Functions Declaration */
void LEFT_PID(void);
void RIGHT_PID(void);
void WALL_PID(void);
void ENCODER_PID(void);
void WALL_FOLLOW(void);

void LEFT_PID(void) {
  leftError = 85 - tof[0];  // Left Facing
  leftDiff = leftError - leftLastError;

  if (leftDiff > 50) {
    leftError = 10;
    leftDiff = 5;
  }

  else if (leftDiff < -50) {
    leftError = -10;
    leftDiff = -5;
  }

  correction = (leftError * leftP) + (leftDiff * leftD);
  leftLastError = leftError;

  if (correction > 50) correction = 15;
  else if (correction < -50) correction = -15;

  leftPWM = leftBase + correction;
  rightPWM = rightBase - correction;
}

void RIGHT_PID(void) {
  rightError = 80 - tof[4];  // Right Facing
  rightDiff = rightError - rightLastError;

  if (rightDiff > 50) {
    rightError = 10;
    rightDiff = 5;
  }

  else if (rightDiff < -50) {
    rightError = -10;
    rightDiff = -5;
  }

  correction = (rightError * rightP) + (rightDiff * rightD);
  rightLastError = rightError;

  if (correction > 50) correction = 15;
  else if (correction < -50) correction = -15;

  leftPWM = leftBase - correction;
  rightPWM = rightBase + correction;
}

void WALL_PID(void) {
  wallError = tof[0] - (tof[4] - 8);
  rightLastError = 58 - tof[4];
  leftLastError = 50 - tof[0];
  wallDiff = wallError - wallLastError;

  if (wallDiff > 50) {
    wallError = 10;
    wallDiff = 5;
  }

  else if (wallDiff < -50) {
    wallError = -10;
    wallDiff = -5;
  }

  correction = (wallError * wallP) + (wallDiff * wallD);
  wallLastError = wallError;

  if (correction > 50) correction = 10;
  else if (correction < -50) correction = -10;

  leftPWM = leftBase - correction;
  rightPWM = rightBase + correction;
}

void ENCODER_PID(void) {
  encoderError = leftEncoderValue - rightEncoderValue;

  if (encoderError > 50) encoderError = 10;
  else if (encoderError < -50) encoderError = -10;

  encoderCorrection = float(encoderError * encoderP) + float(encoderLastError * encoderD);
  encoderLastError = encoderError;
  leftPWM = leftBase - encoderCorrection;
  rightPWM = rightBase + encoderCorrection;

  FORWARD();
}

void WALL_FOLLOW(void) {
  TOF_PID();

  if (tof[0] <= 135 && tof[4] <= 135) {
    state = 0;

    if (state != preState) {
      jump = 5;
      wallLastError = 0;
    }

    if (jump > 0) {
      ENCODER_PID();
      jump = jump - 1;
    } else {
      WALL_PID();
      FORWARD();
    }
  }

  else if (tof[0] > 135 && tof[4] <= 135) {
    state = 1;

    if (state != preState) {
      jump = 5;
      rightLastError = 0;
    }

    if (jump > 0) {
      ENCODER_PID();
      jump = jump - 1;
    } else {
      RIGHT_PID();
      FORWARD();
    }
  }

  else if (tof[0] <= 135 && tof[4] > 135) {
    state = 2;

    if (state != preState) {
      jump = 5;
      leftLastError = 0;
    }

    if (jump > 0) {
      ENCODER_PID();
      jump = jump - 1;
    } else {
      LEFT_PID();
      FORWARD();
    }
  }

  else if (tof[0] > 135 && tof[4] > 135) {
    state = 3;
    ENCODER_PID();
    wallLastError = 0;
  }

  preState = state;
}