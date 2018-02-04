#include <NIDAQmx.h>
#include <vector>
#include <string>

#ifndef MYDAQSESSION_H
#define MYDAQSESSION_H

#endif // MYDAQSESSION_H

class MyDAQSession
{
    //Define static variables---------------------
    private:
        TaskHandle task_handle;
        double min_voltage;
        double max_voltage;
        double rate;
        std::vector<int> analog_input_channels;
        std::vector<int> analog_output_channels;
        std::vector<int> digital_channels;
    //Define constructor and functions-----------
    public:
        //Constructor
        //Empty
        MyDAQSession();
        //INPUTS: (analog_input_channels, analog_output_channels, digital_channels)
        MyDAQSession(std::vector<int>,  std::vector<int>, std::vector<int>);
        //INPUTS: (analog_input_channels, analog_output_channels, digital_channels, rate)
        MyDAQSession(std::vector<int>,  std::vector<int>, std::vector<int>, double);
        //Destructor

        //Public functions
        void setChannels();
        std::vector<int> getAIChannels();
        std::vector<int> getAOChannels();
        std::vector<int> getDigChannels();
        float64 readSingle();
        //INPUTS: (analog_output_data[one per channel], digital_output_data[one per channel])
        void writeSingle(std::vector<float64>, std::vector<float64>);


};
