#include <thread>
#include "stopwatch.h"
#include <chrono>
#include <iostream>

// Starts stopwatch
void Stopwatch::start(){
    start_point.push_back(std::chrono::steady_clock::now());
    points.push_back(std::chrono::steady_clock::now());
}

// Adds stop points to stoppoints
void Stopwatch::stop(){
    stop_points.push_back(std::chrono::steady_clock::now());
    points.push_back(std::chrono::steady_clock::now());
}

// Removes reinitializes start point and clears stop points
void Stopwatch::reset(){
    typedef std::chrono::steady_clock clock;
    typedef std::chrono::time_point<clock> TimePoint;
    //TimePoint();  // ms 0
    start_point.clear();
    start_point.push_back(TimePoint());
    points.clear();
}

// Calculate current duration
std::chrono::steady_clock::duration Stopwatch::get_duration(){
    std::chrono::steady_clock::duration stop_sum{}, active_sum{};    // duration 0ms
    std::chrono::steady_clock::time_point end_point;

    if(stop_points.size() == 1){
        return stop_points[0] - start_point[0];
    }else{

        bool add = true;
        for(int i = points.size()-1; i > 1; i--){
            if(add)
                active_sum += points[i] - points[i-1];
            else
                stop_sum += points[i] - points[i-1];

        }
        std::cout << "active_sum is: " << active_sum.count() << " stop_sum is: " << stop_sum.count() << std::endl; 
        return active_sum - stop_sum;
    }
}

// Return duration in minutes
double Stopwatch::get_minutes(){
    // Calculate final duration
    std::chrono::steady_clock::duration  final_dur = get_duration();

    typedef std::chrono::duration<double, std::ratio<60>> min_dur;
    std::chrono::duration<double, std::ratio<60>> final_dur_val = min_dur(final_dur);
    return min_dur(final_dur).count();
}

// Return duration in mintes
double Stopwatch::get_seconds(){
    // Calculate final duration
    std::chrono::steady_clock::duration final_dur = get_duration();

    typedef std::chrono::duration<double> sec_dur;
    std::chrono::duration<double, std::ratio<1>> final_dur_val = sec_dur(final_dur);
    return sec_dur(final_dur).count();
}

// Return duration in mintes
double Stopwatch::get_milliseconds(){
   // Calculate final duration
    std::chrono::steady_clock::duration  final_dur = get_duration();

    typedef std::chrono::duration<double, std::milli> milli_dur;
    std::chrono::duration<double, std::milli> final_dur_val = milli_dur(final_dur);
    return milli_dur(final_dur).count();
}

// Return duration in mintes
double Stopwatch::get_nanoseconds(){
    // Calculate final duration
    std::chrono::steady_clock::duration  final_dur = get_duration();

    typedef std::chrono::duration<double, std::nano> nano_dur;
    std::chrono::duration<double, std::nano> final_dur_val = nano_dur(final_dur);
    return nano_dur(final_dur).count();
}