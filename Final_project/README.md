# Bot Shooter 

## Goal of the Project
The goal of this project was to create a simple bot shooting game that exemplifies usage of the enviro game engine.

This project was created to show:
- program autotomy - Programs ability to move, interact, and utilize the enviroment.
- Randomization  - Randomly produce assets.
- User interatction - User interaction with the enviroment and/or robots.

Brief description of how the system works:
The Program initalizes the following objects:
- Gun - User controlled allowing user to change the angle of the weapon.
- AI robot - Automated robot that tries to avoid bullets fired by the gun agent.
- Coordinator - An invisible agent that spawn blocks.

The Gun shoots bullet objects at the angle the gun was facing. Collisions are registered with the bullet and are destroyed on impact with blocks and robots. Bullets inheret their angle from the gun angle.

Instead of using sensors, bullets emit their id, position, speed, angle, and their velocity. The Ai Robot watches these bullets and remembers the bullets through a list structure.

When the bullet agents are removed from the enviroment, they stop emitting their information. The Ai Robots memory of the bullet and its id decays removing it from the list.

The Ai Robot reads these bullets locations and velocity to determine if and where the robot should dodge. 

[Provide a short explanation of the main idea or architecture of the project.]

---

## Key Challenges
During development, several challenges were encountered:

1. **Dodge Calculation**
   A major problem was calculating how to have the robot to dodge bullets and correctly dodge the correct way. Initially using sensors was the default for sensing locations of objects. However, very quickly I realized I only could take magnitude of the sensor. I could proc the sensor, gather its magnitude, take its angle but I wouldn't know where the bullet was in relation to the robot.

   Initially, I thought taking the magnitude and the angle of the sensor, I could compute the its position. How would I know where the bullet was heading? My next idea was record computed bullet locations using the recording to build a "line-of-best fit" using Least-squared regression to predict where the bullet was heading.

   I began to realize the extensive overhead and decided that having the bullet emit its location was far easier and less computationally expensive than using sensors and predicting bullet trajectory.

2. **Bullet Spawn**  
   Another issue was determing bullet spawn point in relation to the gun angle. The bullet inhereting the guns angle was simple; however, spawning the bullet in the correct location was difficult. Several times the bullet would work at shallow angles but when reaching 80+/300- degrees it would begin to hit the rear side of the gun.

   After experimentation, the equation: 
   ```cpp
    double locx = x() + (16 * cos(angle()));
    double locy = y() + (16 * sin(angle()));
   ```
   accurately spawned bullets infront of the muzzle of the gun.

   Multipication of 16 scales the y vector to adjust for gun and length.

   Explanation of the technical problem and how it affected the project.

---

## How to Run / Use the Project
### Installation

To Clone the repository use the following command:

`git clone https://github.com/eeuban/Week1.git`

traverse inside the week 1 file and run the command:

`docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.61 bash`

This will pull, build, start, and create a shell for the enviro image. 

**NOTE: It is important to use v1.61 or latest version. Using later versions could cause issues.**

navigate to the Final_project folder and run the following commands to initialize enviro:

`esm init`
`esm start`

### Running the Program

To compile the project is to simply call `make`.

To Run use the command `enviro`.

Navigate to `http://127.0.0.1` or `http://localhost` to begin playing.

This will start the simulation and display agents interacting in the environment.

---

## Acknowledgements

The following resources helped with development:

Professor Sep Makhsous helped me solve my weapon pitch issue were bullets collided with the gun agent.

Chatgpt provided debuging help for segmentation fault issues.