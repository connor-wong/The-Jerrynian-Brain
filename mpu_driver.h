#define MPU_ADDRESS 0x68  //Change to the address of the IMU

MPU6500 IMU;
calData calib = { 0 };  //Calibration data
AccelData accelData;    //Sensor data
GyroData gyroData;

/* Functions Declaration */
void MPU_SETUP(void);
void MPU_CALIBRATE(void);
void MPU_DEBUG(void);

void MPU_SETUP(void) {
  int err = IMU.init(calib, MPU_ADDRESS);

  if (err != 0) {
    Serial.print("Error initializing IMU: ");
    Serial.println(err);
    while (true) { ; }
  }
}

void MPU_CALIBRATE(void) {
  Serial.println("Keep MPU level.");
  delay(3000);

  IMU.calibrateAccelGyro(&calib);
  Serial.println("MPU Calibrated!");

  Serial.println("Accel biases X/Y/Z: ");
  Serial.print(calib.accelBias[0]);
  Serial.print(", ");
  Serial.print(calib.accelBias[1]);
  Serial.print(", ");
  Serial.println(calib.accelBias[2]);
  
  Serial.println("Gyro biases X/Y/Z: ");
  Serial.print(calib.gyroBias[0]);
  Serial.print(", ");
  Serial.print(calib.gyroBias[1]);
  Serial.print(", ");
  Serial.println(calib.gyroBias[2]);

  delay(3000);
  IMU.init(calib, MPU_ADDRESS);
}

void MPU_DEBUG(void) {
  IMU.update();

  // Read Acceleration Data
  IMU.getAccel(&accelData);
  Serial.print(accelData.accelX);
  Serial.print("\t");
  Serial.print(accelData.accelY);
  Serial.print("\t");
  Serial.print(accelData.accelZ);
  Serial.print("\t");

  // Read Gyroscope Data
  IMU.getGyro(&gyroData);
  Serial.print(gyroData.gyroX);
  Serial.print("\t");
  Serial.print(gyroData.gyroY);
  Serial.print("\t");
  Serial.print(gyroData.gyroZ);
  Serial.println("");
  delay(150);
}