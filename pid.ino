
void onLinePID() {
    error = position - setPoint;
    P = error;
    I += error;
    D = error - lastError;
    lastError = error;
    PID = Kp * P + Ki * I + Kd * D;

    leftPID = (PID > (MaxSpeed - baseSpeed)) ? (MaxSpeed - baseSpeed) : PID;
    leftPID = (PID < -(MaxSpeed + baseSpeed)) ? -(MaxSpeed + baseSpeed) : leftPID;

    rightPID = (PID < -(MaxSpeed - baseSpeed)) ? -(MaxSpeed - baseSpeed) : PID;
    rightPID = (PID > (MaxSpeed + baseSpeed)) ? (MaxSpeed + baseSpeed) : rightPID;

    motor(baseSpeed + leftPID, baseSpeed - rightPID);
}


void resetPID() {

    error = 0;
    lastError = 0;
    P = 0;
    I = 0;
    D = 0;
    PID = 0;
    leftPID = 0;
    rightPID = 0;

    sensorRead();
}


