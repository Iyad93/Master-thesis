#include <errorFunctions.h>

//Function that raises and error
//INPUT: -error_message: message to be displayed on the standard output
//       -error_code: 0 if a minor error occurs, 1 if a major error occurs
void raiseError(std::string error_message, int error_code)
{
    switch(error_code)
    {
        case 0: //Minor error
            printf("MINOR ERROR:\n");
            error_message += "\n-Press enter to continue\n-Press \"e\" to exit program";
            printf(error_message.c_str());
            printf("\n");
            if(std::cin.get() == '\n')
            {
            }
            else
            {
                exit(1);
            }
        break;
        case 1: //Major error
            printf("MAJOR ERROR:\n");
            throw std::runtime_error(error_message.c_str());
        break;
    }
}
