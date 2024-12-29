// #include <Wire.h>
// #include <EEPROM.h>
// #include <VL53L0X.h>
// #include <FastIMU.h>

/* Variables */
#include <variables.h>
// #include <solver_variables.h>

/* Drivers */
// #include <tof_driver.h>
#include <motor_driver.h>
// #include <encoder_driver.h>
// #include <mpu_driver.h>
// #include <dip_driver.h>

/* Functions */
#include <motor_functions.h>
// #include <pid_controller.h>
// #include <speed.h>

/* Solver */
// #include <moves.h>
// #include <floodfill.h>
// #include <solver.h>

void setup() {
  // Wire.begin();
  // Wire.setClock(400000);
  // DIP_SETUP();
  MOTOR_SETUP();
  // ENCODER_SETUP();
  Serial.begin(19200);
}

void loop() {
  FORWARD();
  delay(1000);

  REVERSE();
  delay(1000);
  // SEARCH_STATES();
}
