// author
/**
 * @file robotics-maze-solver.ino
 *
 * @brief This code is work for Arduino Mega
 *
 * @ingroup Maze solving implementation for line follower robot
 * @author Shuvo
 * Contact: shuvo.punam@gmail.com
 *
 */

#define BlackSerface  1
#define MX motor(baseSpeed,baseSpeed);
#define TEST(x) MX delay(x); sensorRead();


//==================Sensor Array===================
int sen[8], onBlack;
const int senArrPin[8] = {A0, A1, A2, A3, A4, A5, A6, A7};
long int Read = 0, lastRead = 0, bigRead = 0;
int ref[8] = {342, 403, 412, 377, 480, 453, 373, 377};

int leftWheel, rightWheel;
//==================Motor Driver Pin===================
const int inA = 6, inB = 5, inC = 9, inD = 10;
int lastSpeedL, lastSpeedR;
int leftSign, rightSign;

//==================Button=============================
const int buttonPin = 13;
const int bazzer = 11;
const int led = 2;

//=================PID Variable========================
float Ki = 0, Kd = 442, baseSpeed = 150, MaxSpeed = 220, setPoint = 4.5, ForMax = 4.5;
float Kp = (MaxSpeed + baseSpeed) /
           ForMax, position = 0, error = 0, lastError = 0, P = 0, I = 0, D = 0, PID = 0, leftPID = 0, rightPID = 0;
//=================Algorithm Rule==========================
const String leftRule[7][2] = {{"LBR", "B"},
                               {"LBS", "R"},
                               {"LBL", "S"},
                               {"SBL", "R"},
                               {"SBS", "B"},
                               {"RBL", "B"}};

const String rightRule[7][2] = {{"RBL", "B"},
                                {"RBS", "L"},
                                {"RBR", "S"},
                                {"SBR", "L"},
                                {"SBS", "B"},
                                {"LBR", "B"}};
const char dir = 'R';
String path = "";


//=================General Variable===================
int nintyDegDelay = 150, turnSpeed = 120, mazeSolve = false, scan = true, pathCount = 0;


void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 8; i++)
        pinMode(senArrPin[i], INPUT);
    pinMode(buttonPin, INPUT);
    pinMode(bazzer, OUTPUT);
    pinMode(inA, OUTPUT);
    pinMode(inB, OUTPUT);
    pinMode(inC, OUTPUT);
    pinMode(inD, OUTPUT);
    pinMode(led, OUTPUT);

    beep(100);
    delay(200);
    beep(100);
    delay(200);
    beep(400);

    if (dir == 'R') {
        leftSign = 1;
        rightSign = -1;
    } else if (dir == 'L') {
        leftSign = -1;
        rightSign = 1;
    }


    while (!digitalRead(buttonPin))
        delay(10);
    //autoCal();
    beep(500);
    //while (!digitalRead(buttonPin))
    //delay(10);

}


void loop() {
    sensorRead();

    if (Read == 0) {
        TEST(10);
        if (Read == 0) {
            TEST(10)
            if (Read == 0) {
                white();
            }
        }
    } else if (blackCondition()) {
        TEST(10);
        if (blackCondition()) {
            TEST(10);
            if (blackCondition()) {
                turnLeft();
            }
        }
    } else if (starCondtiton()) {
        TEST(10);
        if (starCondtiton()) {
            TEST(10);
            if (starCondtiton()) {
                starAction();
            }
        }
    } else if (left90()) {
        TEST(10);
        if (left90()) {
            TEST(5);
            if (left90()) {
                turnLeft();
            }
        }
    } else if (right90()) {
        TEST(10);
        if (right90()) {
            TEST(5);
            if (right90()) {
                turnRight();
            }
        }
    } else onLinePID();

}

