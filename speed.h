/* Functions Declaration */
void CELL_START(void);
void CELL_BRAKE(void);

void CELL_START(void) {
  leftWallAvailable = 0;
  rightWallAvailable = 0;
  frontWallAvailable = 0;

  leftEncoderValue += 220;
  rightEncoderValue += 220;

  leftBase = 70;
  rightBase = 70;

  while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
    dif = leftEncoder - leftEncoderValue + 220;
    leftBase = 70 + int(dif / 2);
    rightBase = 70 + int(dif / 2);
    FORWARD_BASE();
  }

  leftBase = 180;
  rightBase = 180;

  leftEncoderValue += 267;
  rightEncoderValue += 267;

  while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
    WALL_FOLLOW();
  }

  leftEncoderValue += 150;
  rightEncoderValue += 150;

  while (leftEncoder <= leftEncoderValue || rightEncoder <= rightEncoderValue) {
    WALL_FOLLOW();

    if (tof[2] <= 180) frontWallAvailable += 1;
    else frontWallAvailable -= 1;

    if (tof[0] <= 160) leftWallAvailable += 1;
    else leftWallAvailable -= 1;

    if (tof[4] <= 160) rightWallAvailable += 1;
    else rightWallAvailable -= 1;
  }
}

void CELL_BRAKE(void) {
  leftEncoderValue += 417;
  rightEncoderValue += 417;

  leftBase = 180;
  rightBase = 180;

  while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
    WALL_FOLLOW();
  }

  leftEncoderValue += 220;
  rightEncoderValue += 220;

  if (F == true) {
    tof[2] = TOF_FRONT.readRangeSingleMillimeters();

    while (tof[2] > 52) {
      tof[2] = TOF_FRONT.readRangeSingleMillimeters();
      dif = leftEncoder - leftEncoderValue + 220;
      rightBase = 176 - int(dif * 0.75);
      leftBase = 180 - int(dif * 0.85);

      if (rightBase <= 70) rightBase = 70;
      if (leftBase <= 70) leftBase = 70;

      FORWARD_BASE();
    }

    leftBase = 70;
    rightBase = 70;

    tof[2] = TOF_FRONT.readRangeSingleMillimeters();

    while (tof[2] < 50) {
      REVERSE_BASE();
      tof[2] = TOF_FRONT.readRangeSingleMillimeters();
    }
  }

  else {
    while (rightEncoder <= rightEncoderValue || leftEncoder <= leftEncoderValue) {
      dif = leftEncoder - leftEncoderValue + 220;
      rightBase = 176 - int(dif / 2);
      leftBase = 180 - int((dif * 3) / 5);

      if (rightBase <= 70) rightBase = 70;
      if (leftBase <= 70) leftBase = 70;

      FORWARD_BASE();
    }
  }

  BRAKE();
}