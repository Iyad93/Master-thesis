#include <MyTimer.h>
#include <errorFunctions.h>

//Constructors implementation--------------
MyTimer::MyTimer()
{
    is_stopped = true;
    is_paused = false;
    pause_period = 0;
}
//Destructor implementation---------------
/*
MyTimer::~MyTimer()
{
    delete[] is_stopped;
    delete[] is_paused;
    delete[] start_time;
    delete[] last_pause_time;
    delete[] pause_period;
}
*/
//Public functions implementation-----------
//Start the timer
void MyTimer::start()
{
    if(isRunning())
    {
        error_message = "Timer is already running";
        raiseError(error_message, 0);
    }
    else
    {
        is_stopped = false;
        start_time = get();
    }
}
//Stop the timer
//OUTPUT: the current time
double MyTimer::stop()
{
    if(isRunning())
    {
        is_stopped = true;
        is_paused = false;
        pause_period = 0;
        return get();
    }
    else
    {
        error_message = "Timer has already been stopped";
        raiseError(error_message, 0);
    }
}
//Pause the timer until resume() is called
void MyTimer::pause()
{
    if(isRunning() && !isPaused())
    {
       last_pause_time = get();
       is_paused = true;
    }
    else if(!isRunning())
    {
        error_message = "Cannot pause, timer has been stopped";
        raiseError(error_message, 1);
    }
    else
    {
        error_message = "Cannot pause, timer has already been paused";
        raiseError(error_message, 1);
    }
}

//Resume the timer, if and only if the timer has been paused
void MyTimer::resume()
{
    if(isPaused() && isRunning())
    {
        is_paused = false;
        pause_period += (get()-last_pause_time);
    }
    else if(!isPaused())
    {
        error_message = "Cannot resume, timer has not been paused";
        raiseError(error_message, 0);
    }
    else
    {
        error_message = "Cannot resume, timer has been permanently stopped";
        raiseError(error_message, 1);
    }
}
//Check if the timer is running
//OUTPUT: true if and only if the timer is running
bool MyTimer::isRunning()
{
    return !is_stopped;
}
//Check if the timer has been paused
//OUTPUT: true if and only if the timer is paused
bool MyTimer::isPaused()
{
    return is_paused;
}
//Get the current time in seconds, with sub-ms precision, by means of a high resolution clock
//OUPUT: current time in seconds
double MyTimer::get()
{
    if(isRunning())
    {
        using namespace std::chrono;
        //Get the time_point related to the current time instant
        time_point<high_resolution_clock, duration<double>> timePoint =  high_resolution_clock::now();
        duration<double> dur = timePoint.time_since_epoch();
        dur = duration_cast<microseconds>(dur);
        double time = dur.count();
        return (time-start_time)-pause_period;
    }
    else
    {
        error_message = "Cannot take the time, timer has been stopped";
        raiseError(error_message, 0);
    }
}
//Function that returns the start time of the timer
double MyTimer::getStartTime()
{
    return start_time;
}
//Function that uses get() to block the program runtime for a precise amount of time
//INPUTS: -t: waiting period, expressed in seconds
void MyTimer::wait(double t)
{
    //This is a special mode, it does not pause the timer while the runtime is physically blocked
    if(isRunning())
    {
        bool was_paused = isPaused();
        is_paused = false; //Hack the pause mode to be able to execute get()
        double t_0 = get();
        while(get()-t_0<t)
        {
        }
        if(was_paused)
        {
            is_paused = true;
        }
    }
    else
    {
        error_message = "Cannot perform \"wait\" task, timer has been stopped";
        raiseError(error_message, 1);
    }
}
//Function that uses get() to freeze the program and the timer for a precise amount of time
//INPUTS: -t: freeze period, expressed in seconds
void MyTimer::freeze(double t)
{
    //This is a special mode, it pauses the timer while the runtime is physically blocked
    if(isRunning())
    {
        bool was_paused = isPaused();
        if(!was_paused)
        {
            pause();
        }
        is_paused = false; //Hack the pause mode to be able to execute get()
        double t_0 = get();
        while(get()-t_0<t)
        {
        }
        is_paused = true;
        if(!was_paused)
        {
            resume();
        }
    }
    else
    {
        error_message = "Cannot perform \"freeze\" task, timer has been stopped";
        raiseError(error_message, 1);
    }
}

