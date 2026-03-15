#ifndef __BULLET_AGENT__H
#define __BULLET_AGENT__H 

#include "enviro.h"
#include <chrono>

using namespace enviro;

class bulletController : public Process, public AgentInterface {

    public:
    bulletController() : Process(), AgentInterface(), counter(0){
        IdealVelocity = {60, 0};   // Default starting speed.
    }

    void init() {
            notice_collisions_with("AiRobot",[&](Event &e){
                remove_agent(id());
            });

        track_velocity(60, 0, 60, 60);
        IdealVelocity = {60, 60 * sin(angle())};   // Default starting speed.
    }
    void start() {}

    void update() {
        // Check if bullet needs to be destroyed.
        if(NeedToDestroy())
            this->remove_agent(id());

        json bullet_info = {
                {"x", x()},
                {"y", y()},
                {"id", id()},
                {"angle", angle()},
                {"vx", velocity().x},
                {"vy", velocity().y}
            };

        emit(Event("bullet_info", bullet_info));

    }

    void stop() {}

    // If bullet is has extremly low velocity destroy it.
    bool NeedToDestroy(){

        // If bullet has been alive longer than 15 updates, destroy it.
        if( counter++ > 15){
            return true;
        }
        return false;
    }

    std::chrono::high_resolution_clock::time_point minVelocitythreshold;
    cpVect IdealVelocity;
    int counter;
};

class bullet : public Agent {
    public:
    bullet(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    bulletController c;
};


#endif