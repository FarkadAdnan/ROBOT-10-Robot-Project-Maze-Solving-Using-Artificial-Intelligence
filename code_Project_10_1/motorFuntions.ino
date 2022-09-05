/*
 By:Farkad Adnan
 E-mail: farkad.hpfa95@gmail.com
 inst : farkadadnan
 #farkadadnan , #farkad_adnan , فرقد عدنان#
 FaceBook: كتاب عالم الاردوينو
 inst : arduinobook
 #كتاب_عالم_الاردوينو  #كتاب_عالم_الآردوينو 
 */
void motorStop(){
  leftServo.writeMicroseconds(1500);
  rightServo.writeMicroseconds(1500);
  delay(200);
}

void motorForward(){
  leftServo.writeMicroseconds(1500 - (power+adj));
  rightServo.writeMicroseconds(1500 + power);
}

void motorBackward(){
  leftServo.writeMicroseconds(1500 + power);
  rightServo.writeMicroseconds(1500 - power);
}

void motorFwTime (unsigned int time){
  motorForward();
  delay (time);
  motorStop();
}
void motorBwTime (unsigned int time){
  motorBackward();
  delay (time);
  motorStop();
}

void motorTurn(int direction, int degrees){
  leftServo.writeMicroseconds(1500 - (iniMotorPower+adj)*direction);
  rightServo.writeMicroseconds(1500 - iniMotorPower*direction);
  delay (round(adjTurn*degrees+1));
  motorStop();
}
void motorPIDcontrol(){
  
  int leftMotorSpeed = 1500 - (iniMotorPower+adj) - PIDvalue;
  int rightMotorSpeed = 1500 + iniMotorPower - PIDvalue;
     constrain(leftMotorSpeed, 1000, 2000);
   constrain(rightMotorSpeed, 1000, 2000);
  
  leftServo.writeMicroseconds(leftMotorSpeed);
  rightServo.writeMicroseconds(rightMotorSpeed);
}

void runExtraInch(void){
  motorPIDcontrol();
  delay(extraInch);
  motorStop();
}

void goAndTurn(int direction, int degrees){
  motorPIDcontrol();
  delay(adjGoAndTurn);
  motorTurn(direction, degrees);
}
void drivePolygon(unsigned int time, int sides) {
    for (int i = 0; i<sides; i++){
        motorFwTime (time);
        motorTurn(RIGHT, 360/sides);
    }
}
