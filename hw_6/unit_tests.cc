#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "stopwatch.h"
#include "gtest/gtest.h"
#include <thread>
#include "elma/elma.h"
#include "filter.h"
#include "random_process.h"
#include "integrator.h"

#define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))

using json = nlohmann::json;

namespace {

    TEST(process, generalprocess){
        elma::Manager m;

        RandomProcess r("random numbers");
        Filter f("filter");
        Integrator i("integrator");
        elma::Channel link("link");

        m.schedule(r, std::chrono::milliseconds(1))
        .schedule(f, std::chrono::milliseconds(1))
        .schedule(i, std::chrono::milliseconds(1))
        .add_channel(link)
        .init()
        .run(std::chrono::milliseconds(100));
    }

    TEST(Stopwatch, milliseconds) {
        Stopwatch watch;

        watch.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        watch.stop();

        std::cout << "The time in milliseconds is " << \
        watch.get_milliseconds() << std::endl;

        watch.reset();
    }

    TEST(Stopwatch, nanoseconds) {
        Stopwatch watch;

        watch.start();
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
        watch.stop();

        std::cout << "The time in nanoseconds is " << \
        watch.get_nanoseconds() << std::endl;
    
        watch.reset();
    }

    TEST(Stopwatch, seconds) {
        Stopwatch watch;

        watch.start();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        watch.stop();

        std::cout << "The time in seconds is " << \
        watch.get_seconds() << std::endl;

        watch.reset();
    }

    TEST(Stopwatch, minutes) {
        Stopwatch watch;

        watch.start();
        std::this_thread::sleep_for(std::chrono::seconds(15));
        watch.stop();

        std::cout << "The time in minutes is " << \
        watch.get_minutes() << std::endl;

        watch.reset();
    }

    TEST(Stopwatch, general) {
        Stopwatch w; // should set the Stopwatch to 0 seconds
        w.start();
        SLEEP;
        w.stop();
        std::cout << "After first stop: " << w.get_seconds() << "\n"; // about 1.5
        SLEEP;
        std::cout << "Seconds should be same: " << w.get_seconds() << "\n"; // still about 1.5
        w.start();
        SLEEP;
        w.stop();
        std::cout << "After Second stop: " << w.get_seconds() << "\n"; // about 3.0
        w.reset();
        std::cout << "After reset: " << w.get_seconds() << "\n"; // 0.0

    }

}