#define XSHUT_1 32
#define XSHUT_2 33
#define XSHUT_3 23
#define XSHUT_4 25
#define XSHUT_5 26

#define tofAddress1 0x10
#define tofAddress2 0x11
#define tofAddress3 0x12
#define tofAddress4 0x13
#define tofAddress5 0x14

VL53L0X TOF_RIGHT;           // Right Facing
VL53L0X TOF_RIGHT_DIAGONAL;  // Right Diagonal Facing
VL53L0X TOF_FRONT;           // Front Facing
VL53L0X TOF_LEFT_DIAGONAL;   // Left Diagonal Facing
VL53L0X TOF_LEFT;            // Left Facing

/* Functions Declaration */
void TOF_SETUP(void);
void TOF_PID(void);
void TOF_START(void);
void TOF_DEBUG(void);
void CHECK_WALLS_CELL(void);
void WALL_STATE_DEBUG(void);

void TOF_SETUP(void) {
  pinMode(XSHUT_1, OUTPUT);
  pinMode(XSHUT_2, OUTPUT);
  pinMode(XSHUT_3, OUTPUT);
  pinMode(XSHUT_4, OUTPUT);
  pinMode(XSHUT_5, OUTPUT);

  digitalWrite(XSHUT_1, LOW);
  digitalWrite(XSHUT_2, LOW);
  digitalWrite(XSHUT_3, LOW);
  digitalWrite(XSHUT_4, LOW);
  digitalWrite(XSHUT_5, LOW);

  /* Assign Unique Address */
  digitalWrite(XSHUT_1, HIGH);
  delay(10);
  TOF_RIGHT.init();
  TOF_RIGHT.setTimeout(10);
  TOF_RIGHT.setAddress(tofAddress1);

  digitalWrite(XSHUT_2, HIGH);
  delay(10);
  TOF_RIGHT_DIAGONAL.init();
  TOF_RIGHT_DIAGONAL.setTimeout(10);
  TOF_RIGHT_DIAGONAL.setAddress(tofAddress2);

  digitalWrite(XSHUT_3, HIGH);
  delay(10);
  TOF_FRONT.init();
  TOF_FRONT.setTimeout(10);
  TOF_FRONT.setAddress(tofAddress3);

  digitalWrite(XSHUT_4, HIGH);
  delay(10);
  TOF_LEFT_DIAGONAL.init();
  TOF_LEFT_DIAGONAL.setTimeout(10);
  TOF_LEFT_DIAGONAL.setAddress(tofAddress4);

  digitalWrite(XSHUT_5, HIGH);
  delay(10);
  TOF_LEFT.init();
  TOF_LEFT.setTimeout(10);
  TOF_LEFT.setAddress(tofAddress5);
}

void TOF_PID(void) {
  /* Ensure micronmouse move in straight line */
  tof[0] = TOF_LEFT.readRangeSingleMillimeters();   // Left Facing
  tof[2] = TOF_FRONT.readRangeSingleMillimeters();  // Front Facing
  tof[4] = TOF_RIGHT.readRangeSingleMillimeters();  // Right Facing
}

void TOF_START(void) {
  tof[1] = TOF_RIGHT_DIAGONAL.readRangeSingleMillimeters();  // Left Digonal Facing
  tof[2] = TOF_FRONT.readRangeSingleMillimeters();           // Front Facing
  tof[3] = TOF_LEFT_DIAGONAL.readRangeSingleMillimeters();   // Right Digonal Facing
}

void TOF_DEBUG(void) {
  tof[0] = TOF_LEFT.readRangeSingleMillimeters();            // Left Facing
  tof[1] = TOF_LEFT_DIAGONAL.readRangeSingleMillimeters();   // Left Diagonal Facing
  tof[2] = TOF_FRONT.readRangeSingleMillimeters();           // Front Facing
  tof[3] = TOF_RIGHT_DIAGONAL.readRangeSingleMillimeters();  // Right Diagonal Facing
  tof[4] = TOF_RIGHT.readRangeSingleMillimeters();           // Right Facing

  Serial.print(tof[0]);
  Serial.print(",  ");
  Serial.print(tof[1]);
  Serial.print(",  ");
  Serial.print(tof[2]);
  Serial.print(",  ");
  Serial.print(tof[3]);
  Serial.print(",  ");
  Serial.print(tof[4]);
  Serial.println();
  delay(150);
}

void CHECK_WALLS_CELL(void) {
  if (x == 0 && y == 0) {
    timeState = 0;

    while (timeState < 10) {
      TOF_START();

      if (tof[2] <= 180) frontWallAvailable = frontWallAvailable + 1;
      else frontWallAvailable = frontWallAvailable - 1;

      if (tof[1] <= 150) leftWallAvailable = leftWallAvailable + 1;
      else leftWallAvailable = leftWallAvailable - 1;

      if (tof[3] <= 150) rightWallAvailable = rightWallAvailable + 1;
      else rightWallAvailable = rightWallAvailable - 1;

      timeState = timeState + 1;
    }
  }

  if (frontWallAvailable >= 0) {
    cellWalls[1] = 0;
    F = true;
  } else {
    cellWalls[1] = 1;
    F = false;
  }

  if (leftWallAvailable >= 0) {
    cellWalls[0] = 1;
    L = true;
  } else {
    cellWalls[0] = 0;
    L = false;
  }

  if (rightWallAvailable >= 0) {
    cellWalls[2] = 1;
    R = true;
  } else {
    cellWalls[2] = 0;
    R = false;
  }
}

void WALL_STATE_DEBUG(void) {
  for (int i = 0; i < 3; i++) {
    Serial.print(cellWalls[i]);
    Serial.print("   ");
  }
  Serial.println("");
}