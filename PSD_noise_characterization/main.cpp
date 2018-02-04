//Headers for data acquisition
#include <NIDAQmx.h>
#include <stdio.h>
//Custom headers
#include <ioFunctions.h>
#include <stringfunctions.h>
#include <timingFunctions.h>

/*This function acquires data from the NIDAQPad, to later measure the
  properties of the noise of the PSD, both due to the
internal noise of the sensor and to "normal" background illumination
*/

//Define an error flag function, whenever something goes wrtong with the data acquisiton

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) ; else

int main(void)
{
   //Define variables for data acquisition------------
    int32 error=0;
    TaskHandle taskHandle=0;
    int32 read;
    char errBuff[2048]={'\0'};
    //Define data vectors
    int n = 1000; //#samples to be acquired
    std::vector<float64> V_SUM(n);
    std::vector<float64> time(n);
   //-------------------------------------
    //Prepare for data acquisition---------------------
    // DAQmx analog voltage channel and timing parameters

    DAQmxErrChk (DAQmxCreateTask("", &taskHandle));
    DAQmxErrChk(DAQmxCreateAIVoltageChan(taskHandle, "Dev1/ai9", "", DAQmx_Val_Cfg_Default, -10.0, 10.0, DAQmx_Val_Volts, NULL));
    DAQmxErrChk(DAQmxCfgSampClkTiming(taskHandle, "", 10000.0, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, n));
    // DAQmx Start Code
    DAQmxErrChk(DAQmxStartTask(taskHandle));
    //----------------------------
    //Start an acquisition loop-----------
    double t_0 = getTime(); //Start time
    double waitTime = 0.0001;
    for(int i = 0; i<n; i++)
    {
        time.at(i) = getTime()-t_0; //Elapsed time in seconds
        //Single read from the DAQ
        DAQmxErrChk(DAQmxReadAnalogF64(taskHandle, 1, 10.0, DAQmx_Val_GroupByChannel, &V_SUM.at(i), n, &read, NULL));
        wait(waitTime);
    }
    //------------------------
    //Save data into a file----------
    std::string fileName = "V_SUM.txt";
    fWrite(fileName, V_SUM);
    fileName = "time.txt";
    fWrite(fileName, time);
    //--------------------
    /*
//Implement data acquisition error function-------------------
Error:
       if (DAQmxFailed(error))
              DAQmxGetExtendedErrorInfo(errBuff,2048);
       if(taskHandle!=0)
       {
              DAQmxStopTask(taskHandle);
              DAQmxClearTask(taskHandle);
       }
       if(DAQmxFailed(error))
              printf("DAQmx Error: %s\n",errBuff);
              */
//--------------------------------------
   return 0;
}





