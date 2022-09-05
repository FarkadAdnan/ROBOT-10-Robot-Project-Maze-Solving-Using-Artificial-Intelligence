/*
 By:Farkad Adnan
 E-mail: farkad.hpfa95@gmail.com
 inst : farkadadnan
 #farkadadnan , #farkad_adnan , فرقد عدنان#
 FaceBook: كتاب عالم الاردوينو
 inst : arduinobook
 #كتاب_عالم_الاردوينو  #كتاب_عالم_الآردوينو 
 */
 void mazeEnd(void){
  motorStop();
  BT1.print("The End");
  mode = STOPPED;
  while (digitalRead(buttonPin))
  { 
    ledBlink();
  }
}
void followingLine(void){
   readLFSsensors(); 
   calculatePID();
   motorPIDcontrol();   
}
