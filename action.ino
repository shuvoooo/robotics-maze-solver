bool turnCondition(char c) {
  if (blackCondition()) {
    endPoint();
    return true;
  }
  else if (Tcondition() || plusCondition()) {
    if (dir == 'L')
      path += 'L';
    else if (dir == 'R')
      path += 'R';

    turn(leftSign * turnSpeed, rightSign * turnSpeed);
    return true;
  }

  else if ((lastRead == 678 || lastRead == 78 || lastRead == 8) && c == 'L') { //left 90
    if (dir == 'L')
      path += 'L';
    else
      path += 'R';////////////////////S

    turn(leftSign * turnSpeed, rightSign * turnSpeed);
    return true;
  }

  else if ((lastRead == 12300000 || lastRead == 12000000 || lastRead == 10000000) && c == 'R') { //Right 90
    if (dir == 'R')
      path += 'R';
    else
      path += 'L';/////////////////////S

    turn(leftSign * turnSpeed, rightSign * turnSpeed);
    return true;
  }

  //Read == 300000 || Read == 340000 || Read == 40000 || Read == 45000 || Read == 5000
  else if (Read) {
    if ((dir == 'R' && c == 'L') || (dir == 'L' && c == 'R')) {
      path += 'S';
      onLinePID();
    }
    else if (dir == 'L' && c == 'L') {
      path += 'L';
      turn(-turnSpeed, turnSpeed);
    }
    else if (dir == 'R' && c == 'R') {
      path += 'R';
      turn(turnSpeed, -turnSpeed);
    }
    return true;
  }

  else return false;
}



bool soluationTurn(char c) {
  if (blackCondition()) {
    bool i = 1;
    while (blackCondition()) {
      sensorRead();
      motor(0, 0);
      delay(500);
      digitalWrite(led, i);
      i = !i;
    }

    digitalWrite(led, 0);

    return true;
  }
  else  if (Tcondition() || plusCondition()) {
    if (path[pathCount] == 'S') {
      onLinePID();
    }
    else if (path[pathCount] == 'R') {
      turn(turnSpeed, -turnSpeed);
    }
    else if (path[pathCount] == 'L') {
      turn(-turnSpeed, turnSpeed);
    }
    pathCount++;
    return true;
  }


  else if ((lastRead == 678 || lastRead == 78 || lastRead == 8) && c == 'L') { //left 90
    if (c == 'L' && path[pathCount] == 'L')
      turn(-turnSpeed, turnSpeed);
    else
      turn(turnSpeed, -turnSpeed);
    pathCount++;
    return true;
  }
  else if ((lastRead == 12300000 || lastRead == 12000000 || lastRead == 10000000) && c == 'R') { //Right 90
    if (c == 'R' && path[pathCount] == 'R')
      turn(turnSpeed, -turnSpeed);
    else
      turn(-turnSpeed, turnSpeed);
    pathCount++;
    return true;
  }

  else if (Read) {
    if (c == 'L' && path[pathCount] == 'L')
      turn(-turnSpeed, turnSpeed);
    else if (c == 'R' && path[pathCount] == 'R')
      turn(turnSpeed, -turnSpeed);
    else onLinePID();
    pathCount++;
    return true;
  }

  else return false;
}

void endPoint() {
  botBreak(100);
  beep(100);
  digitalWrite(led, 1);
  Serial.println(path);
  mazeSoluation();
  Serial.println(path);
  mazeSolve = true;
  scan = false;
  beep(1000);
  digitalWrite(led, 0);
  bool i = 1;
  while (!digitalRead(buttonPin)) {
    delay(500);
    digitalWrite(led, i);
    i = !i;
  }
  digitalWrite(led, 0);
  beep(500);
}

void white() {
  if (scan == true && mazeSolve == false) {
    path += 'B';
    motor(baseSpeed, baseSpeed);
    delay(150);
    turn(leftSign * turnSpeed, rightSign * turnSpeed);
  }
  else {
    botBreak(60);
    while (Read == 0) {
      motor(0, 0);
      sensorRead();
    }
  }
}

void starAction() {
  if (scan == true && mazeSolve == false) {
    if (dir == 'R')
      path += 'R';
    else
      path += 'L';
    motor(baseSpeed, baseSpeed);
    delay(130);
    turn(leftSign * turnSpeed, rightSign * turnSpeed);
  }
  else if (scan == false && mazeSolve == true) {
    if (path[pathCount] == 'R') {
      turn(turnSpeed, -turnSpeed);
    }
    else if (path[pathCount] == 'L') {
      turn(-turnSpeed, turnSpeed);
    }
    else if (path[pathCount] == 'S' && dir == 'L') {
      turn(turnSpeed, -turnSpeed);
    }
    else if (path[pathCount] == 'S' && dir == 'R') {
      turn(-turnSpeed, turnSpeed);
    }
    else onLinePID();
    pathCount++;
  }
}

void turnLeft() {
  bigRead = 0;
  for (int i = 0; i < nintyDegDelay; i++) {
    motor(baseSpeed, baseSpeed);
    sensorRead();
  }
  if (mazeSolve == false && scan == true) {
    if (turnCondition('L') == false) {
      turn(-turnSpeed, turnSpeed);
      path += 'L';
    }
  }
  else if (mazeSolve == true && scan == false) {
    if (soluationTurn('L') == false) {
      turn(-turnSpeed, turnSpeed);
      pathCount++;
    }
  }
}

void turnRight() {
  bigRead = 0;
  for (int i = 0; i < nintyDegDelay; i++) {
    motor(baseSpeed, baseSpeed);
    sensorRead();
  }
  if (mazeSolve == false && scan == true) {
    if (turnCondition('R') == false) {
      turn(turnSpeed, -turnSpeed);
      path += 'R';
    }
  }
  else if (mazeSolve == true && scan == false) {
    if (soluationTurn('R') == false) {
      turn(turnSpeed, -turnSpeed);
      pathCount++;
    }
  }
}











void turn(int left, int right) {
  botBreak(40);
  motor(left, right);
  delay(200);
  sen[3] = 0;
  sen[4] = 0;
  while (!sen[3] || !sen[4]) {
    motor(left, right);
    sensorRead();
  }
  botBreak(40);
}

