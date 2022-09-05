/*
 By:Farkad Adnan
 E-mail: farkad.hpfa95@gmail.com
 inst : farkadadnan
 #farkadadnan , #farkad_adnan , فرقد عدنان#
 FaceBook: كتاب عالم الاردوينو
 inst : arduinobook
 #كتاب_عالم_الاردوينو  #كتاب_عالم_الآردوينو 
 */
 int mode = 0;
# define STOPPED 0
# define FOLLOWING_LINE 1
# define NO_LINE 2
# define CONT_LINE 3
# define POS_LINE 4
# define RIGHT_TURN 5
# define LEFT_TURN 6

const int power = 250;
const int iniMotorPower = 250;
const int adj = 100;
float adjTurn = 9;
int extraInch = 200;
int adjGoAndTurn = 950;

const int ledPin = 13;
const int buttonPin = 9;

const int lineFollowSensor0 = 12; 
const int lineFollowSensor1 = 18; 
const int lineFollowSensor2 = 17; 
const int lineFollowSensor3 = 16;
const int lineFollowSensor4 = 19;

const int farRightSensorPin = 0; //Analog Pin A0
const int farLeftSensorPin = 1; //Analog Pin A0
const int THRESHOLD = 200;
int farRightSensor = 0;
int farLeftSensor = 0;

int LFSensor[5]={0, 0, 0, 0, 0};

float Kp=50;
float Ki=0;
float Kd=0;

float error=0, P=0, I=0, D=0, PIDvalue=0;
float previousError=0, previousI=0;

#define RIGHT 1
#define LEFT -1

Servo leftServo;
Servo rightServo;
