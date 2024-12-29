/* Functions Declaration */
void MAZE_START(void);
void CELL_FOWARD(void);
void CELL_FAST_FORWARD(void);
void LEFT_SMOOTH_TURN(void);
void RIGHT_SMOOTH_TURN(void);
void RIGHT_TURN(void);
void LEFT_TURN(void);
void CELL_BACK(void);

void MAZE_START(void) {
  selectMode = 0;
  
  while (1) {
    TOF_START();
    TOF_START();

    if (tof[1] <= 120 && tof[2] <= 120 && tof[3] <= 120) {
      selectMode = 1;
      delay(1000);
      break;
    }
  }
  
  timeState = 0;
  while (timeState < 50) {
    TOF_START();
    TOF_START();

    if (tof[1] <= 120 && tof[2] <= 120 && tof[3] <= 120) {
      selectMode = 2;
      delay(1000);
      break;
    }

    timeState = timeState + 1;
  }

  if (selectMode == 2) {
    timeState = 0;
    while (timeState < 50) {
      TOF_START();
      TOF_START();

      if (tof[1] <= 120 && tof[2] <= 120 && tof[3] <= 120) {
        selectMode = 3;
        delay(1000);
        break;
      }

      timeState = timeState + 1;
    }
  }
}

void CELL_FOWARD(void) {
  leftWallAvailable = 0;
  rightWallAvailable = 0;
  frontWallAvailable = 0;

  leftEncoderValue = leftEncoderValue + 1123;
  rightEncoderValue = rightEncoderValue + 1123;

  while (leftEncoder <= leftEncoderValue || rightEncoder <= rightEncoderValue) {
    WALL_FOLLOW();
  }

  leftEncoderValue = leftEncoderValue + 150;
  rightEncoderValue = rightEncoderValue + 150;

  while (leftEncoder <= leftEncoderValue || rightEncoder <= rightEncoderValue) {
    WALL_FOLLOW();

    if (tof[2] <= 180) {
      frontWallAvailable = frontWallAvailable + 1;
    } else {
      frontWallAvailable = frontWallAvailable - 1;
    }
    if (tof[0] <= 160) {
      leftWallAvailable = leftWallAvailable + 1;
    } else {
      leftWallAvailable = leftWallAvailable - 1;
    }
    if (tof[4] <= 160) {
      rightWallAvailable = rightWallAvailable + 1;
    } else {
      rightWallAvailable = rightWallAvailable - 1;
    }
  }
}

void CELL_FAST_FORWARD(void) {
  leftBase = 180;
  rightBase = 180;
  leftWallAvailable = 0;
  rightWallAvailable = 0;
  frontWallAvailable = 0;
  leftEncoderValue = leftEncoderValue + 1273;
  rightEncoderValue = rightEncoderValue + 1273;

  while (leftEncoder <= leftEncoderValue || rightEncoder <= rightEncoderValue) {
    WALL_FOLLOW();
    if (tof[2] <= 240) {
      while (tof[2] > 150) {
        WALL_FOLLOW();
      }
      leftEncoder = leftEncoderValue + 1;
      rightEncoder = rightEncoderValue + 1;
      test = 2;
      break;
    }
  }
}

void LEFT_SMOOTH_TURN(void) {
  leftBase = 180;
  rightBase = 180;
  leftEncoderValue = 0;
  rightEncoderValue = 0;
  leftEncoder = 0;
  rightEncoder = 0;
  rightEncoderValue = rightEncoderValue + 300;

  while (rightEncoder <= rightEncoderValue) {
    dif = rightEncoder - rightEncoderValue + 300;
    rightBase = rightBase + int(dif * 0.1);
    leftBase = leftBase - int(dif / 3);
    FORWARD_BASE();
  }

  rightBase = 210;
  leftBase = 70;
  leftEncoderValue = 0;
  rightEncoderValue = 0;
  leftEncoder = 0;
  rightEncoder = 0;
  rightEncoderValue = rightEncoderValue + 860;

  while (rightEncoder <= rightEncoderValue) {
    FORWARD_BASE();
  }

  leftEncoderValue = 0;
  rightEncoderValue = 0;
  leftEncoder = 0;
  rightEncoder = 0;
  rightEncoderValue = rightEncoderValue + 300;

  while (rightEncoder <= rightEncoderValue) {
    dif = rightEncoder - rightEncoderValue + 300;
    rightBase = rightBase - int(dif * 0.1);
    leftBase = leftBase + int(dif / 3);
    FORWARD_BASE();
  }

  leftBase = 180;
  rightBase = 180;
  rightEncoderValue = rightEncoderValue + 200;

  while (rightEncoder <= rightEncoderValue) {
    WALL_FOLLOW();
  }
}

void RIGHT_SMOOTH_TURN(void) {
  leftBase = 180;
  rightBase = 180;
  leftEncoderValue = 0;
  rightEncoderValue = 0;
  leftEncoder = 0;
  rightEncoder = 0;
  leftEncoderValue = leftEncoderValue + 300;

  while (leftEncoder <= leftEncoderValue) {
    dif = leftEncoder - leftEncoderValue + 300;
    leftBase = leftBase + int(dif * 0.1);
    rightBase = rightBase - int(dif / 3);
    FORWARD_BASE();
  }

  leftBase = 210;
  rightBase = 70;
  leftEncoderValue = 0;
  rightEncoderValue = 0;
  leftEncoder = 0;
  rightEncoder = 0;
  leftEncoderValue = leftEncoderValue + 840;

  while (leftEncoder <= leftEncoderValue) {
    FORWARD_BASE();
  }

  leftEncoderValue = leftEncoderValue + 300;

  while (leftEncoder <= leftEncoderValue) {
    dif = leftEncoder - leftEncoderValue + 300;
    leftBase = leftBase - int(dif * 0.1);
    rightBase = rightBase + int(dif / 3);
    FORWARD_BASE();
  }

  leftBase = 180;
  rightBase = 180;
  leftEncoderValue = leftEncoderValue + 200;

  while (leftEncoder <= leftEncoderValue) {
    WALL_FOLLOW();
  }
}

void RIGHT_TURN(void) {
  CELL_BRAKE();
  RIGHT_ABOUT_TURN();
  CELL_START();
}

void LEFT_TURN(void) {
  CELL_BRAKE();
  LEFT_ABOUT_TURN();
  CELL_START();
}

void CELL_BACK(void) {
  CELL_BRAKE();
  TURN_BACK();
  CELL_START();
}
