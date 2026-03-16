#ifndef __SCOREBOARD_AGENT__H
#define __SCOREBOARD_AGENT__H

#include "enviro.h"
#define HEALTH 1

using namespace enviro;

class ScoreboardController : public Process, public AgentInterface {

public:
    ScoreboardController() : Process(), AgentInterface(), health(HEALTH) {}

    void init() {

        watch("health", [&](Event &e){
            health = e.value()["health"];
        });
        watch("reset", [&](Event& e){
            should_reset = true;
        });
    }
    void start() {}

    void update() {
        // If need to reset, clear bullet list and return from update
        if(should_reset){
            remove_agent(id());
            return;
        }

        label("Health: " + std::to_string(health), 0, 0);
    }

    void stop() {}

    int health;
    bool should_reset = false;
};

class Scoreboard : public Agent {
public:
    Scoreboard(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }

private:
    ScoreboardController c;
};

#endif