# ROBOT-10-Robot-Project-Maze-Solving-Using-Artificial-Intelligence
Chapter 1 code_Project_10 The Third Part 3 of "The Arduino World Book" code_Project_10 ROBOT-10 Robot Project Maze Solving Using Artificial Intelligence
- code_Project_10

-  By:Farkad Adnan فرقد عدنان -
- https://linktr.ee/farkadadnan

 - E-mail: farkad.hpfa95@gmail.com 
- inst : farkadadnan 
- #farkadadnan , #farkad_adnan , فرقد عدنان# 
- FaceBook: كتاب عالم الاردوينو 
- inst : arduinobook
1. #كتاب_عالم_الاردوينو
2. #كتاب_عالم_الآردوينو 

* facebook : https://www.facebook.com/profile.php?id=100002145048612
* instagram:  https://www.instagram.com/farkadadnan/
* linkedin : https://www.linkedin.com/in/farkad-adnan-499972121/

 <p>
 <a href='https://mobile.twitter.com/farkadadnan'>
        <img alt="Twitter Follow" src="https://img.shields.io/twitter/follow/farkadadnan?label=%40farkadadnan&style=social" alt='Twitter' align="center"/>
    </a>
</p>

# Introduction
The majority of the labyrinths, despite the complexity of their design, were formed mainly from one wall connected by many intersections and branches. If the wall surrounding the maze objective is connected to the perimeter of the maze at the entrance, the maze can always be solved by keeping one hand in contact with the wall, regardless of the many detours that may be involved. These "simple" labyrinths are properly known as "simply connected" or "perfect labyrinth" or in other words, they do not contain loops.
![1](https://user-images.githubusercontent.com/35774039/188647381-debf428d-eeb0-46ad-8cad-2133e82d4934.PNG)

# Working ROBOT 

- (1st pass): The robot goes down the path of the black line in the maze and the robot finds its way out of an "unknown perfect maze". No matter where you put it inside the maze, it will find a "solution".
When the robot launches the first time, it discovers the environment around it.
The robot also moves by the law of the left hand.
- (2nd pass): Once the robot has found a possible solution to the maze, it must improve its solution to find the "shortest path from start to finish".

![AA2A7006@075x](https://user-images.githubusercontent.com/35774039/188648417-8985c15c-c773-4831-af13-bacb31f14550.png)

# the maze
To start, what is the difference between a labyrinth and a labyrinth? According to http://www.labyrinthos.net, it is often considered that to be a maze bird, the design must have choices in the path. Obviously, this will include many modern installations in amusement parks and attractions, including the 2D maze here. Common consensus also suggests that labyrinths have a single path that leads inevitably from the entrance to the goal, albeit often one of the most complex and winding paths.


# 7 sensors  KY-033 Line Tracking Sensor

The new array of now 7 sensors, is mounted on a way that the 5 original ones are exclusively used for PID control (and detection of the "full line", explained later) and the 2 new ones, left to be used exclusively for LEFT and RIGHT intersection detection.

As a quick review, let's remember how the 5 original "digital" sensors work:

If one sensor is centered with relation to the black line, only that specific sensor will produce a HIGH. By other side, the space between sensors should be calculated to allow that 2 sensors can cover the full width of the black line simultaneously, also producing a HIGH signal on both sensors.

![17](https://user-images.githubusercontent.com/35774039/188649289-626d04e3-2d9e-456c-be95-7fd6b3014471.PNG)
```
const int lineFollowSensor0 = 12; //Using Digital input
const int lineFollowSensor1 = 18; //Using Analog Pin A4 as Digital input
const int lineFollowSensor2 = 17; //Using Analog Pin A3 as Digital input
const int lineFollowSensor3 = 16; //Using Analog Pin A2 as Digital input
const int lineFollowSensor4 = 19; //Using Analog Pin A5 as Digital input
const int farRightSensorPin = 0;  //Analog Pin A0
const int farLeftSensorPin = 1;   //Analog Pin A1

```

Each position of the array and variables will be constantly updated with the output of each one of the sensors:

```
LFSensor[0] = digitalRead(lineFollowSensor0);
LFSensor[1] = digitalRead(lineFollowSensor1);
LFSensor[2] = digitalRead(lineFollowSensor2);
LFSensor[3] = digitalRead(lineFollowSensor3);
LFSensor[4] = digitalRead(lineFollowSensor4);
farRightSensor = analogRead(farRightSensorPin);
farLeftSensor = analogRead(farLeftSensorPin);

```

- Having 5 sensors, as saw in the Follower Line Robot project, permits the generation of an "error variable" that will help to control the robot's position over the line. Also, a variable called "mode" will be used for definition if the robot is following a line, over a continuous line, an intersection or no line at all.

 
# H 0 X X X X L 
So, implementing the above logic in the function:

void readLFSsensors()

will return the variables "mode" and "error" that will be used at the program logic.

It is important to test the logic of the sensors before following with the project. The bellow function is included in the code and can be used for testing purposes:

# algorithm 
Once we have the readLFSsensors() function modified to include the extra 2 sensors, we can re-write the Loop Function to run the algorithm as described on the last Step:

```
void loop()
{
  readLFSsensors();
  switch (mode)
  {
    case NO_LINE:
       motorStop();
       goAndTurn (LEFT, 180);
       break;
    case CONT_LINE:
       runExtraInch();
       readLFSsensors();
       if (mode == CONT_LINE) mazeEnd();
       else goAndTurn (LEFT, 90); // or it is a "T" or "Cross"). In both cases, goes to LEFT
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

```
- Some new functions appear here:

- followingLine() is the same used with the Following Line Robot where, if it is only following a line, it must calculatePID(); and control the motors depending of PID values: motorPIDcontrol();

- runExtraInch(): will push the robot forward just a little bit. How much the robot will run will depend of the time that you use in the delay function, before you command the motor to stop.

```
void runExtraInch(void)
{
  motorPIDcontrol();
  delay(extraInch);
  motorStop();
}
```
- goAndTurn (direction, angle): this special function is important because you can not turn the robot as soon you realize the type of intersection you are. Remember that we projected a Differential Robot that when making turns, it "turns around its axe" and so, to move 90o and continuously follow the line, the center of the wheels must be aligned with the center of intersection. Once the line of sensors is ahead of its axe, you must run the robot forward to align them. The constant of time adjGoAndTurn must be adjusted depending on of the distance between axe and sensor line ("d"), speed and size of the wheels (see the above picture for illustration).

```
void goAndTurn(int direction, int degrees)
{
  motorPIDcontrol();
  delay(adjGoAndTurn);
  motorTurn(direction, degrees);
}
```

At this point, the robot is in fact "solving a maze"! You just finish the "First Pass". Does not matter where you start inside a maze, you will always reach the end.

# PATH 1 and PATH 2 
![summer_14_sketches_key5](https://user-images.githubusercontent.com/35774039/188650420-e6beb7a8-0a6e-4d18-814c-b3f12b500b0a.jpg)

# direction

Here a new function was introduced: recIntersection (direction)

This function will be used for store the intersection and also to call another function simplifyPath(), that will reduce the group of 3 intersections involving an "U-Turn" as we saw before.
```
void recIntersection(char direction)
{
  path[pathLength] = direction; 
  pathLength ++;
  simplifyPath();  
}
```

#  Second Pass: Solving the Maze As Fast As Possible
The main program: loop () is simple like that:

```
void loop() 
{
  ledBlink(1);
  readLFSsensors(); 
  
  mazeSolve(); // First pass to solve the maze
  ledBlink(2);
  while (digitalRead(buttonPin) { }
  pathIndex = 0;
  status = 0;
  
  mazeOptimization(); // Second Pass: run the maze as fast as possible
  ledBlink(3);
  while (digitalRead(buttonPin) { }
  mode = STOPPED;
  status = 0; // 1st pass
  pathIndex = 0;
  pathLength = 0;
}

```
To command what to do, a new function mazeTurn(path[]) was created.

The function mazeTurn (path[]) will be:

```
void mazeTurn (char dir) 
{
  switch(dir)
  {
    case 'L': // Turn Left
       goAndTurn (LEFT, 90);      
       break;   
    
    case 'R': // Turn Right
       goAndTurn (RIGHT, 90);     
       break;   
       
    case 'B': // Turn Back
       goAndTurn (RIGHT, 800);     
       break;   
       
    case 'S': // Go Straight
       runExtraInch(); 
       break;
  }
}

```

# Using the Application
- const int power = 250;
- const int iniMotorPower = 250;
- const int adj = 0;
- float adjTurn = 8;
- int extraInch = 200;
- int adjGoAndTurn = 800;
- THRESHOLD = 150
# Flow-chart 
![2-Figure1-1](https://user-images.githubusercontent.com/35774039/188652392-ac60457f-2fb7-4d2c-a440-5b1a01bd2fbc.png)

# MAZE-SOLVING ALGORITHMS
 Some of classic maze solving algorithms usually employed are random mouse, wall follower and flood fill algorithms. The wall follower algorithm is commonly used when the position of the target point is unknown. The target is usually identified with a unique marking. On the other hand, the flood fill algorithm is commonly used when the position of the target point is geometrically known but the robot needs to find the shortest route. The following sections describe the flood fill and wall follower algorithms .


# Wall Follower Algorithm
- In wall follower algorithm, the robot will keep an eye at the right or left wall and navigate throughout the maze until it finds the target point. This algorithm is proven to be very efficient for mazes that are wall-linked to the target point . This makes it very suitable for mazes where the target point is located at the periphery, a situation where the robot almost appears like trying to escape the maze. 
- There are two types of wall follower algorithm: left-hand rule and right-hand rule. The two algorithms work the same way except turning priority will be either to the left or to the right depending on the type of rule used .

# Path Optimization
By choosing the correct navigation rule to follow, the path taken may be shorter but not necessarily the most optimum in terms of moves taken. The path may contain redundant moves. A move is considered redundant when it took the robot back to where it was before.
![16](https://user-images.githubusercontent.com/35774039/188653246-612b6e64-9f25-40e5-b4a1-0c4dd11e8b6c.PNG)

# CONCLUSION
A wall follower algorithm with selectable left-hand or righthand navigation rule can provide more flexibility and intelligence for maze navigation. The selection of the navigation rule is done dynamically based the scenario encountered by the vehicle. With the addition of path optimization done through the path shortening algorithm, the combined system can provide practical improvement to autonomous vehicles.

# REFERENCES

- Verner, I.M. and D.J. Ahlgren, Robot contest as a laboratory for experiential engineering education. J. Educ. Resour. Comput., 2004. 4(2): p. 2. 
- Achmad, B. and M.N. Karsiti. Visual-based fuzzy navigation system for mobile robot: Wall and corridor follower. in Intelligent and Advanced Systems, 2007. ICIAS 2007. International Conference on. 2007. Kuala Lumpur.
- Vignesh, S., et al., Cave Exploration of Mobile Robots using Soft Computing Algorithms. International Journal of Computer Applications 71(22):14-18, June 2013. Published by Foundation of Computer Science, New York, USA. 
- Mishra, S. and P. Bande. Maze Solving Algorithms for Micro Mouse. in Signal Image Technology and Internet Based Systems, 2008. SITIS '08. IEEE International Conference on. 2008.
- Cai, J., et al., An Algorithm of Micromouse Maze Solving, in Proceedings of the 2010 10th IEEE International Conference on Computer and Information Technology. 2010, IEEE Computer Society. p. 1995- 2000.
- Jianping, C., et al. A micromouse maze sovling simulator. in Future Computer and Communication (ICFCC), 2010 2nd International Conference on. 2010.
- Adil, M.J.S. A Comprehensive and Comparative Study of Maze-Solving Techniques by Implementing Graph Theory. 2010.
- Sharma, M. and K. Robeonics. Algorithms for Micromouse. in Future Computer and Communication, 2009. ICFCC 2009. International Conference on. 2009. 
- Elshamarka, I. and A.B.S. Saman, Article: Design and Implementation of a Robot for Maze-Solving using Flood-Fill Algorithm. International Journal of Computer Applications, 2012. 56(5): p. 6. 
- Cai, Z., L. Ye, and A. Yang. FloodFill Maze Solving with Expected Toll of Penetrating Unknown Walls. in 2012 IEEE 14th International Conference on High Performance Computing and Communications. 2012.
- Willardson, D.M., Analysis of Micromouse Maze Solving Algorithm, in Learning from Data. 2001, Portland State University.
- Babula, M. Simulated maze solving algorithms through unknown mazes. in Proceedings of XVIIIth Concurrency, Specification and Programming (CS&P) Workshop. 2009.





