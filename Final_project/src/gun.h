#ifndef __GUN_AGENT__H
#define __GUN_AGENT__H 

#include "enviro.h"
#include <iostream>
#include <vector>

using namespace enviro;

class GunController : public Process, public AgentInterface {

    public:
    GunController() : Process(), AgentInterface(), delta{0.0}, cooloff(0) {}

    void init() {

        ignore_collisions_with("bullet");
        
        watch("keydown", [&](Event &e){
            string k = e.value()["key"].get<std::string>();
            std::cout << k << std::endl;
            if( k == "w") {
                delta += step;
            } else if( k == "s"){
                delta -= step;
            } else if( k == " " && cooloff == 0){

                
                double locx = x() + (16 * cos(angle()));
                double locy = y() + (16 * sin(angle()));
                add_agent("bullet", locx, locy, angle(),
                    json::object({{"fill","yellow"},{"stroke","black"}})
                );
                cooloff = 6;
            }
        });
        watch("keyup", [&](Event &e){
            string k = e.value()["key"].get<std::string>();
            std::cout << k << std::endl;
            if( k == "w") {
                delta = 0;
            } else if( k == "s"){
                delta = 0;
            }
        });
        watch("reset", [&](Event& e){
            should_reset = true;
        });
    }

    void start() {}
    void update() {

        // Removes element if game is reset.
        if(should_reset){
            bool destroyed = false;
            remove_agent(id());
        }

        track_velocity(0, delta);

        if(cooloff > 0)
            cooloff--;

    }
    void stop() {}

    bool destroyed = false;         // Should be destroyed 
    bool should_reset = false;      // Should be reset
    double delta;                   // Current angle of gun
    const double step = 1.5;        // Step of gun angular velocity
    cpVect bulletSpeed = {400, 0};  // Using cpVect to define bullet speed
    u_int cooloff;                  // Cooloff time between shots
};

class Gun : public Agent {
    public:
    Gun(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    GunController c;
};

DECLARE_INTERFACE(Gun)

#endif