# ifndef STOPWATCH_H
# define STOPWATCH_H

#include <chrono>
#include <ratio>
#include <vector>
#include <stack>

class Stopwatch{
    public:

    //stopwatch() : _start_point(),_curr_point() {}

    void start();              // starts the timer
    void stop();               // stops the timer
    void reset();              // sets stopwatch to zero
    double get_minutes();      // number of minutes counted, as a double
    double get_seconds();      // number of seconds counted, as a double
    double get_milliseconds(); // number of milliseconds counted, as a double
    double get_nanoseconds();  // number of nanoseconds counted, as a double

    private:
    // StartPoint
    std::vector<std::chrono::steady_clock::time_point> start_point;
    // Duration of between stops points.
    std::vector<std::chrono::steady_clock::time_point>  stop_points;
    // Points in order from call.
    std::vector<std::chrono::steady_clock::time_point>   points;
    // Return curr duration.
    std::chrono::steady_clock::duration get_duration();

};

# endif