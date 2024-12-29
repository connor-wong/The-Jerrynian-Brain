/* TOF Driver */
float tof[5];

/* Encoder Driver */
unsigned long leftEncoder = 0;
unsigned long rightEncoder = 0;
unsigned long leftEncoderValue = 0;
unsigned long rightEncoderValue = 0;

/* Motor Driver */
int leftBase = 180;
int rightBase = 180;
int leftPWM = 180;
int rightPWM = 180;

/* MPU Driver */
int16_t ax, ay, az;
int16_t gx, gy, gz;

/* PID Controller */
float correction;

int dif = 0;
int test = 0;

/* Encoder PID */
float encoderP = 0.2;
float encoderD = 0;
float encoderError = 0;
float encoderLastError = 0;
float encoderDiff = 0;
float encoderCorrection = 0;

/* Wall PID */
float wallP = 0.8;
float wallD = 2.7;
float wallError = 0;
float wallLastError = 0;
float wallDiff = 0;

/* Left PID */
float leftP = 0.9;
float leftD = 3.4;
float leftError = 0;
float leftLastError = 0;
float leftDiff = 0;

/* Right PID */
float rightP = 0.9;
float rightD = 3.4;
float rightError = 0;
float rightLastError = 0;
float rightDiff = 0;

/* Walls */
int wallAvailable[3];
int cellWalls[3];

int leftWallAvailable = 0;
int rightWallAvailable = 0;
int frontWallAvailable = 0;

int rightWall = 1;
int leftWall = 1;

/* Maze Solver */
char nextMove = 'F';
int start = 0;
int cell = 0;
int jump = 0;
int timeState;
int preState = 0;

/* Dip Switch */
int selectMode = 0;