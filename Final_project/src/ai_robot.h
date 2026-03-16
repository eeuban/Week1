#ifndef __AI_ROBOT_AGENT__H
#define __AI_ROBOT_AGENT__H 

#include "enviro.h"
#include "bullet.h"
#include <vector>

using namespace enviro;

#define DODGEDISTANCE_X 150
#define DODGEDISTANCE_Y 30
#define ROBORESETSPEED 1200     // Speed to remove away from walls
#define HEALTH 1

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
    AiRobotController() : Process(), AgentInterface(), randmove(10), health(HEALTH) {}

    void init() {
        prevent_rotation();

        /* NOTE - Event handlers don't run during process(Ai Update) time.
           Executed immediately. */
        watch("bullet_info", [&](Event& e){
            senseBullet(e.value());
        });
        watch("bullet_hit", [&](Event& e){
            std::cout << "health is " << health << std::endl;
            if(health > 0)
                health--;
            emit(Event("health", {{"health", health}}));
        });
        watch("reset", [&](Event& e){
            should_reset = true;
        });
    }
    void start() {}
    void update() {

        // If need to reset, clear bullet list and return from update
        if(should_reset){
            bool destroyed = false;
            bullets.clear();
            remove_agent(id());
            return;
        }

        std::vector<int> bullets_to_remove;
        for(int i = 0; i < bullets.size(); i++){
            bullets[i].last_seen--;
            // If any bullet didn't emit its status mark for removal
            if(bullets[i].last_seen <= 0)
                bullets_to_remove.push_back((int)i);
        }

        // Remove bullets marked for removal
        for(int i = 0; i < bullets_to_remove.size(); i++){
            bullets.erase(bullets.begin() + bullets_to_remove[i]);
        }

        // Decrement bullets last seen.
        for(int i = 0; i < bullets.size(); i++){
            bullets[i].last_seen = bullets[i].last_seen--;
        }

        // Determine if dodging needed
        cpVect dodging = dodge_dir();
        omni_apply_force(dodging.x, dodging.y);

        // Prevent robot from being stuck
        if(sensor_value(0) < 10)
            omni_apply_force(0, -ROBORESETSPEED);
        else if(sensor_value(1) < 40)
            omni_apply_force(-ROBORESETSPEED-2000, 0);
        else if(sensor_value(2) < 10)
            omni_apply_force(0, ROBORESETSPEED);

        // Randomizes Bots movement
        if(randmove == 0){
            int sign = rand() % 2 == 0 ? (-1) : (1);
            omni_apply_force(sign * (rand() % 1000), sign * (rand() % 1000));
            randmove = 5;
        }
        randmove--;

    }
    void stop() {}
    cpVect dodge_dir();                     // Detemine doge direction

    bool destroyed = false;
    bool should_reset = false;
    int health;                             // Health the robot has
    int randmove;                           // Tick for bot movement
    void senseBullet(json bullet_info);     // Handle Bullet Sensing
    std::vector<seen_bullet> bullets;       // Current bullets that are seen

    // Threashold dodge distance
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