#include <iostream>
#include "ai_robot.h"
#include <string>
#include "bullet.h"

using namespace enviro;

// Put your implementations here

// Find seen bullet and its location. Append bullet location in array
void AiRobotController::senseBullet(json bullet_info){

    int size = bullets.size();
    std::vector<int> bullets_to_remove;
    bool new_bullet = true;
    // All bullets created should emit their info. If not in array, remove
    for(size_t i = 0; i < size; i++){

        // If any bullet didn't emit its status mark for removal
        if(bullets[i].last_seen <= 0){
            bullets_to_remove.push_back((int)i);

        // If bullet has already been sensed before update info
        if(bullet_info["id"] == bullets[i].id){
            bullets[i].x = bullet_info["x"];
            bullets[i].y = bullet_info["y"];
            bullets[i].speed.x = bullet_info["vx"];
            bullets[i].speed.y = bullet_info["vy"];
            bullets[i].angle = bullet_info["angle"];
            bullets[i].last_seen = 10;             // Refresh last seen
            new_bullet = false;
            }
        }
    }

    // Remove bullets marked for removal
    for(size_t i = 0; i < bullets_to_remove.size(); i++){
        bullets.erase(bullets.begin() + bullets_to_remove[i]);
    }

    // If not recognized bullet new bullet detected
    if(new_bullet){
        seen_bullet new_bullet;
        new_bullet.id = bullet_info["id"];
        new_bullet.x = bullet_info["x"];
        new_bullet.y = bullet_info["y"];
        new_bullet.speed.x = bullet_info["vx"];
        new_bullet.speed.y = bullet_info["vy"];
        new_bullet.angle = bullet_info["angle"];
        bullets.push_back(new_bullet);
    }
}

// Determines if need to dodge bullet
cpVect AiRobotController::dodge_dir(){

    for(size_t i = 0; i < bullets.size(); i++){
        double xdist = x() - bullets[i].x;
        double ydist = y() - bullets[i].y;


        std::cout << "bullet " << i << " xdist is " << xdist << " and ydist is "\
        << ydist << std::endl;
        // Need to dodge
        if(fabs(xdist) < dodgeDistance.x && fabs(ydist) < dodgeDistance.y){
            if(ydist <= 0){  // Bullet above, move down
                std::cout << "Moving down in the world " << std::endl;
                return cpVect{0.0, -800.0};
            }else if (ydist > 0){            // Bullet bellow, move up
                std::cout << "Moving up in the world " << std::endl;
                return cpVect{0.0, 800.0};
            }else{
                return cpVect{0.0, 0.0};
            }
        }
    }
}

DECLARE_INTERFACE(AiRobot)