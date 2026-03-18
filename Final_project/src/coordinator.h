#ifndef __COORDINATOR_AGENT__H
#define __COORDINATOR_AGENT__H 

#define NUMBLOCKS 5

#include "enviro.h"
#include <random>

// Bounds of enviroment
#define LEFTMOST -350       // LeftMost barrier location
#define RIGHTMOST 350       // RightMost barrier location
#define UPMOST 200          // Highest barrier location
#define BOTTOMMOST -200     // Lowest barrier location
#define HEALTH 10           // Health of robot

using namespace enviro;

class coordinatorController : public Process, public AgentInterface {

    public:
    coordinatorController() : Process(), AgentInterface(), health(HEALTH) {}

    void init() {

        watch("health", [&](Event &e){
            health = e.value()["health"];
        });

        // Add scoreboard
        add_agent("scoreboard", 0, 220, 0, {
            {"fill", "none"},
            {"label", "Score: 0"},
            {"label_size", "24px"},
            {"label_color", "black"}
        });

        // Generate blocks in random location
        std::random_device rd;
        std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> distrbx(LEFTMOST + 100, RIGHTMOST - 50);
        std::uniform_int_distribution<> distrby(BOTTOMMOST + 50, UPMOST - 50);

        int x = 0, y = 0;
        for(int i = 0; i < NUMBLOCKS; i++){
            x = distrbx(gen);
            y = distrby(gen);
            add_agent("block", x, y, 0, {{"fill", "black"}});
        }
    }
    void start() {}
    void update() {

        // Delete all initialized agents
        if(health <= 0){
            exit(0);

        // Bellow is attempt for level functionality
        emit(Event("reset", true));
        health = HEALTH;

        add_agent("scoreboard", 0, 220, 0, {
            {"fill", "none"},
            {"label", "Score: 0"},
            {"label_size", "24px"},
            {"label_color", "black"}
        });

        std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> distrbx(LEFTMOST + 100, RIGHTMOST - 50);
        std::uniform_int_distribution<> distrby(BOTTOMMOST + 50, UPMOST - 50);

        int x = 0, y = 0;
        for(int i = 0; i < NUMBLOCKS; i++){
            x = distrbx(gen);
            y = distrby(gen);
            add_agent("block", x, y, 0, {{"fill", "black"}});
        }

        // Call init to initiallize to generate blocks.
        // Add agents back into world
        add_agent("AiRobot", 50, 0, 0, { {"fill", "orange"}, {"stroke", "black"} });
        add_agent("Gun", -330, 0, 0, { {"fill", "red"}, {"stroke", "black"} })};
    }

    void stop() {}
    int health;
};

class coordinator : public Agent {
    public:
    coordinator(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    coordinatorController c;
};

DECLARE_INTERFACE(coordinator)

#endif