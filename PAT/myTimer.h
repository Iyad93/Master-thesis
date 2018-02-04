#include <chrono>
#include <string>
#include <vector>

#ifndef TIMINGFUNCTIONS_H
#define TIMINGFUNCTIONS_H

#endif // TIMINGFUNCTIONS_H

class MyTimer
{
//Define static variables---------------------
private:
    bool is_paused;
    bool is_stopped;
    double start_time;
    double last_pause_time;
    double pause_period;
    std::string error_message;
//Define constructor and functions-----------
public:
    //Constructor
    MyTimer();
    //Destructor
   // ~MyTimer();
    //Public functions
    void start();
    double stop();
    void pause();
    void resume();
    bool isRunning();
    bool isPaused();
    double get();
    double getStartTime();
    void wait(double t);
    void freeze(double t);
};
