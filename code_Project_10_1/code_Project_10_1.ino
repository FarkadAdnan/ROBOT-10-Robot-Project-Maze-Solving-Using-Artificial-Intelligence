/*
 By:Farkad Adnan
 E-mail: farkad.hpfa95@gmail.com
 inst : farkadadnan
 #farkadadnan , #farkad_adnan , فرقد عدنان#
 FaceBook: كتاب عالم الاردوينو
 inst : arduinobook
 #كتاب_عالم_الاردوينو  #كتاب_عالم_الآردوينو 
 */
#include <Servo.h>
#include "robotDefines.h"

String command;
String device;
 
#include <SoftwareSerial.h>
SoftwareSerial BT1(10, 11);  

 void setup() {
  Serial.begin(9600);
  BT1.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
    pinMode(lineFollowSensor0, INPUT);
  pinMode(lineFollowSensor1, INPUT);
  pinMode(lineFollowSensor2, INPUT);
  pinMode(lineFollowSensor3, INPUT);
  pinMode(lineFollowSensor4, INPUT);
  
  leftServo.attach(5);
  rightServo.attach(3);

  BT1.print("check the PID constants to be sent to Robot");
  BT1.println('\n');
  while (digitalRead(buttonPin) && !mode) {  
    checkBTcmd(); 
    manualCmd ();    
    command = "";  
  }
  motorFwTime (3000); 
  checkPIDvalues();
  mode = STOPPED;
}
void loop() {
  readLFSsensors();  
  switch (mode)  {   
    case NO_LINE:  
      motorStop();
      goAndTurn (LEFT, 180);
      break;
    case CONT_LINE: 
      runExtraInch();
      readLFSsensors();
      if (mode == CONT_LINE) mazeEnd();
      else goAndTurn (LEFT, 90); 
      break;

   case RIGHT_TURN: 
      runExtraInch();
      readLFSsensors();
      if (mode == NO_LINE) goAndTurn (RIGHT, 90); 
      break;   
   case LEFT_TURN: 
      goAndTurn (LEFT, 90); 
      break;   
   
   case FOLLOWING_LINE: 
      followingLine();
      break;         
  }
}
