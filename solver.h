/* Functions Declaration */
void EEPROM_CLEAR(void);
void CALCULATE_PATH(boolean runningNext);
void TRAVERSE(byte xdes, byte ydes, boolean middleSquare, boolean shortPath, boolean smooth);
void FIX_ORIENTATION(void);
void LOAD_CELLS(void);
void WRITE_CELLS(void);
void SEARCH_STATES(void);

void EEPROM_CLEAR(void) {
  for (int i = 0; i < 250; i++) {
    EEPROM.write(i, 0);
  }
}

void CALCULATE_PATH(boolean runningNext) {
  FLOOD_FILL_2();

  byte xprevious = x;
  byte yprevious = y;
  x = 0;
  y = 0;
  byte oldOrient = orient;
  orient = 0;
  cellCount = 0;

  while (flood2[y][x] != 1) {
    TO_MOVE_2();

    if (runningNext == true) pathQueue.enqueue(dir);
    if (dir == 'L') orient = ORIENTATION(orient, 'L');
    else if (dir == 'R') orient = ORIENTATION(orient, 'R');
    else if (dir == 'B') {
      orient = ORIENTATION(orient, 'L');
      orient = ORIENTATION(orient, 'L');
    }

    xprev = x;
    yprev = y;
    UPDATE_COORDINATES();
  }

  x = xprevious;
  y = yprevious;
  orient = oldOrient;
}

void TRAVERSE(byte xdes, byte ydes, boolean middleSquare, boolean shortPath, boolean smooth) {
  byte currentx = x;
  byte currenty = y;

  if (shortPath == false) {
    APPEND_DESTINATION(xdes, ydes, middleSquare);
    FLOOD_FILL_3();
    CHECK_WALLS_CELL();
    UPDATE_WALLS(x, y, orient, L, R, F);

    while (flood[y][x] != 0) {
      CHECK_WALLS_CELL();
      UPDATE_WALLS(x, y, orient, L, R, F);
      APPEND_DESTINATION(xdes, ydes, middleSquare);
      FLOOD_FILL_3();
      dir = TO_MOVE(x, y, xprev, yprev, orient);

      if (dir == 'L') {
        orient = ORIENTATION(orient, 'L');
        if (x == 0 || x == currentx) {
          if (y == 0 || y == currenty) {
            LEFT_ABOUT_TURN();
            delay(500);
            CELL_START();
            currentx = 0;
            currenty = 0;
          } else {
            LEFT_TURN();
          }
        } else {
          LEFT_TURN();
        }
      }

      else if (dir == 'R') {
        orient = ORIENTATION(orient, 'R');
        if (x == 0 || x == currentx) {
          if (y == 0 || y == currenty) {
            RIGHT_ABOUT_TURN();
            delay(500);
            CELL_START();
            currentx = 0;
            currenty = 0;
          } else {
            RIGHT_TURN();
          }
        } else {
          RIGHT_TURN();
        }
      }

      else if (dir == 'B') {
        orient = ORIENTATION(orient, 'L');
        orient = ORIENTATION(orient, 'L');
        if ((x == 0 && y == 0) || (x == currentx && y == currenty)) {
          TURN_BACK();
          delay(500);
          CELL_START();

          currentx = 0;
          currenty = 0;
        } else {
          CELL_BACK();
        }
      } else {
        if ((x == 0 && y == 0) || (x == currentx && y == currenty)) {
          CELL_START();
          currentx = 0;
          currenty = 0;
        } else {
          CELL_FOWARD();
        }
      }

      xprev = x;
      yprev = y;
      UPDATE_COORDINATES();
    }
  }

  else {
    F = false;
    R = false;
    L = false;

    if (smooth == true) {
      CALCULATE_PATH(true);

      while (!pathQueue.isEmpty()) {
        dir = pathQueue.dequeue();

        if (dir == 'L') {
          orient = ORIENTATION(orient, 'L');
          if ((x == 0 && y == 0) || (x == currentx && y == currenty)) {
            LEFT_ABOUT_TURN();
            delay(500);
            CELL_START();
            currentx = 0;
            currenty = 0;
          } else {
            LEFT_SMOOTH_TURN();
          }
        }

        else if (dir == 'R') {
          orient = ORIENTATION(orient, 'R');
          if ((x == 0 && y == 0) || (x == currentx && y == currenty)) {
            RIGHT_ABOUT_TURN();
            delay(500);
            CELL_START();
            currentx = 0;
            currenty = 0;
          } else {
            RIGHT_SMOOTH_TURN();
          }
        }

        else if (dir == 'B') {
          orient = ORIENTATION(orient, 'L');
          orient = ORIENTATION(orient, 'L');
          if ((x == 0 && y == 0) || (x == currentx && y == currenty)) {
            TURN_BACK();
            delay(500);
            CELL_START();
            currentx = 0;
            currenty = 0;
          } else {
            CELL_BACK();
          }
        }

        else {
          if ((x == 0 && y == 0) || (x == currentx && y == currenty)) {
            CELL_START();
            currentx = 0;
            currenty = 0;
          } else {
            CELL_FOWARD();
          }
        }

        xprev = x;
        yprev = y;
        UPDATE_COORDINATES();
      }
    }

    else {
      CALCULATE_PATH(true);

      while (!pathQueue.isEmpty()) {
        CHECK_WALLS_CELL();
        dir = pathQueue.dequeue();

        if (dir == 'L') {
          orient = ORIENTATION(orient, 'L');
          if ((x == 0 && y == 0)) {
            LEFT_ABOUT_TURN();
            delay(500);
            CELL_START();
          } else {
            LEFT_TURN();
          }

        }

        else if (dir == 'R') {
          orient = ORIENTATION(orient, 'R');
          if ((x == 0 && y == 0)) {
            RIGHT_ABOUT_TURN();
            delay(500);
            CELL_START();
          } else {
            RIGHT_TURN();
          }
        }

        else if (dir == 'B') {
          orient = ORIENTATION(orient, 'L');
          orient = ORIENTATION(orient, 'L');
          if ((x == 0 && y == 0)) {
            TURN_BACK();
            delay(500);
            CELL_START();
          } else {
            CELL_BACK();
          }
        }

        else {
          if ((x == 0 && y == 0)) {
            CELL_START();
          } else {
            CELL_FOWARD();
          }
        }

        xprev = x;
        yprev = y;
        UPDATE_COORDINATES();
      }
    }
  }
}

void FIX_ORIENTATION(void) {
  while (orient != 0) {
    LEFT_ABOUT_TURN();
    orient = ORIENTATION(orient, 'L');
    delay(500);
  }
}

void LOAD_CELLS(void) {
  for (int i = 0; i < 14; i++) {
    for (int j = 0; j < 14; j++) {
      cells[j][i] = EEPROM.read(i * 14 + j);
    }
  }
}

void WRITE_CELLS(void) {
  for (int i = 0; i < 14; i++) {
    for (int j = 0; j < 14; j++) {
      EEPROM.write(i * 14 + j, cells[j][i]);
    }
  }
}

void SEARCH_STATES(void) {
  byte searchState = EEPROM.read(200);

  if (searchState == 3) {
    searchState = 0;
  }

  LOAD_CELLS();

  if (searchState == 0) {
    MAZE_START();

    if (selectMode == 1) {
      TRAVERSE(0, 0, true, false, false);
      L = false;
      R = false;
      F = false;

      CENTER();
      CELL_BRAKE();

      delay(3000);
      WRITE_CELLS();
      TRAVERSE(13, 0, false, false, false);
      CELL_BRAKE();

      TRAVERSE(0, 0, false, false, false);
      CELL_BRAKE();

      FIX_ORIENTATION();
      delay(3000);
      MAZE_START();

      if (selectMode == 2) {
        WRITE_CELLS();
        EEPROM.write(200, searchState + 1);
      } else if (selectMode == 3) {
        EEPROM_CLEAR();
        delay(1000);
      }
    }

    else if (selectMode == 2) {
      TRAVERSE(0, 0, true, true, false);
      L = false;
      R = false;
      F = false;
      CENTER();
      CELL_BRAKE();

      delay(3000);
      TRAVERSE(0, 0, false, false, false);
      CELL_BRAKE();

      FIX_ORIENTATION();
      delay(3000);
      MAZE_START();

      if (selectMode == 2) {
        WRITE_CELLS();
      } else if (selectMode == 3) {
        EEPROM_CLEAR();
        delay(1000);
      }
    } else if (selectMode == 3) {
      EEPROM_CLEAR();
      delay(1000);
    }
  }

  else if (searchState == 1) {
    MAZE_START();

    if (selectMode == 1) {
      TRAVERSE(0, 0, true, false, false);

      L = 0;
      R = 0;
      F = 0;

      CELL_BRAKE();
      CENTER();
      TRAVERSE(0, 13, false, false, false);
      CELL_BRAKE();

      delay(500);

      TRAVERSE(0, 0, false, false, false);
      CELL_BRAKE();
      FIX_ORIENTATION();
      MAZE_START();

      if (selectMode == 2) {
        WRITE_CELLS();
        EEPROM.write(200, searchState + 1);
      } else if (selectMode == 3) {
        EEPROM_CLEAR();
      }
    } else if (selectMode == 2) {
      FLOOD_FILL_2();
      TRAVERSE(0, 0, true, true, false);

      L = 0;
      R = 0;
      F = 0;

      CELL_BRAKE();
      CENTER();

      delay(500);
      TRAVERSE(0, 0, false, false, false);
      CELL_BRAKE();
      FIX_ORIENTATION();
      MAZE_START();

      if (selectMode == 2) {
        WRITE_CELLS();
      } else if (selectMode == 3) {
        EEPROM_CLEAR();
        delay(1000);
      }
    } else if (selectMode == 3) {
      EEPROM_CLEAR();
      delay(1000);
    }
  }

  else if (searchState == 2) {
    MAZE_START();

    if (selectMode == 1) {
      TRAVERSE(0, 0, true, false, false);

      L = 0;
      R = 0;
      F = 0;

      CELL_BRAKE();
      CENTER();

      delay(500);
      TRAVERSE(13, 13, false, false, false);
      CELL_BRAKE();

      delay(500);
      TRAVERSE(0, 0, false, false, false);
      CELL_BRAKE();
      FIX_ORIENTATION();
      MAZE_START();

      if (selectMode == 2) {
        WRITE_CELLS();
        EEPROM.write(200, searchState + 1);
      } else if (selectMode == 3) {
        EEPROM_CLEAR();
      }
    } else if (selectMode == 2) {
      FLOOD_FILL_2();
      TRAVERSE(0, 0, true, true, false);

      L = 0;
      R = 0;
      F = 0;

      CELL_BRAKE();
      CENTER();

      delay(500);

      TRAVERSE(0, 0, false, false, false);
      CELL_BRAKE();
      FIX_ORIENTATION();
      MAZE_START();

      if (selectMode == 2) {
        WRITE_CELLS();
      } else if (selectMode == 3) {
        EEPROM_CLEAR();
        delay(1000);
      }

    } else if (selectMode == 3) {
      EEPROM_CLEAR();
      delay(1000);
    }
  }
}