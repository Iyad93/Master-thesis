#include <timingFunctions.h>

//Get the current time in seconds, with sub-ms precision, by means of a high resolution clock
//INPUT:
double getTime()
{
    using namespace std::chrono;
    //Get the time_point related to the current time instant
    time_point<high_resolution_clock, duration<double>> timePoint =  high_resolution_clock::now();

    duration<double> dur = timePoint.time_since_epoch();
    dur = duration_cast<microseconds>(dur);
    double time = dur.count();
    return time;
}

//Function that used getTime() to wait for a precise amount of time
//INPUTS: -t: waiting period, expressed in seconds
void wait(double t)
{
    double t_0 = getTime();
    while(getTime()-t_0<t)
    {
    }
}
