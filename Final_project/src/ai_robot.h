#ifndef __AI_ROBOT_AGENT__H
#define __AI_ROBOT_AGENT__H 

#include "enviro.h"
#include "bullet.h"
#include <vector>

using namespace enviro;

#define DODGEDISTANCE_X 150
#define DODGEDISTANCE_Y 30
#define ROBOSPEED 200

typedef struct {
    double x;
    double y;
    int id;
    double angle;
    cpVect speed;
    double last_seen = 10;
} seen_bullet;

class AiRobotController : public Process, public AgentInterface {

    public:
    AiRobotController() : Process(), AgentInterface() {}

    void init() {
        prevent_rotation();

        /* NOTE - Event handlers don't run during event time. Executed
           immediately. */
        watch("bullet_info", [&](Event& e){
            senseBullet(e.value());
        });
    }
    void start() {}
    void update() {
        std::cout << "in ai_robot update" << std::endl;

        std::vector<int> bullets_to_remove;
        for(int i = 0; i < bullets.size(); i++){
            bullets[i].last_seen--;
            std::cout << "bullets " << i << "last seen is " << bullets[i].last_seen << std::endl;
            // If any bullet didn't emit its status mark for removal
            if(bullets[i].last_seen <= 0)
                bullets_to_remove.push_back((int)i);
        }

        // Remove bullets marked for removal
        for(size_t i = 0; i < bullets_to_remove.size(); i++){
            std::cout << "erasing bullet " << i << std::endl;
            bullets.erase(bullets.begin() + bullets_to_remove[i]);
        }

        // Decrement bullets last seen.
        for(int i = 0; i < bullets.size(); i++){
            bullets[i].last_seen = bullets[i].last_seen--;
        }

        // Determine if dodging needed
        cpVect dodging = dodge_dir();
        omni_apply_force(dodging.x, dodging.y);
    }
    void stop() {}

    void senseBullet(json bullet_info);     // Handle Bullet Sensing
    cpVect dodge_dir();                     // Detemine doge direction
    std::vector<seen_bullet> bullets;
    cpVect dodgeDistance = {DODGEDISTANCE_X, DODGEDISTANCE_Y};
};

class AiRobot : public Agent {
    public:
    AiRobot(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    AiRobotController c;
};

#endif