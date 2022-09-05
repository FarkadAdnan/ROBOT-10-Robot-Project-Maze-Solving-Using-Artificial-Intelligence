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
SoftwareSerial BT1(10, 11); // El pin 10 es Rx y el pin 11 es Tx

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
  Serial.print("check the PID constants to be sent to Robot");
  BT1.println('\n');
  
  while (digitalRead(buttonPin) && !mode){  
    checkBTcmd(); 
    manualCmd ();    
    command = "";  
  }  
  checkPIDvalues();
  mode = STOPPED;
  status = 0; // 1st pass
}
void loop() {
  ledBlink(1);
  BT1.println("Start First Pass");
  Serial.println("Start First Pass");
  readLFSsensors();  
  mazeSolve(); 
  ledBlink(2);
  BT1.println("End First Pass"); 
  Serial.println("End First Pass"); 
  
   while (digitalRead(buttonPin) && !mode) {  
    checkBTcmd();
    manualCmd ();    
    command = "";  
  }
  
  BT1.println("Starting 2nd Pass"); 
  Serial.println("Starting 2nd Pass"); 
  pathIndex = 0;
  status = 0;
  mazeOptimization();
  ledBlink(3);
  BT1.println("End 2nd Pass"); 
  Serial.println("End 2nd Pass"); 
  
  while (digitalRead(buttonPin) && !mode){  
    checkBTcmd();
    manualCmd ();    
    command = "";  
  }
  
  mode = STOPPED;
  status = 0; 
  pathIndex = 0;
  pathLength = 0;
}
