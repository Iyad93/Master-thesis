#include <ioFunctions.h>
#include <stringFunctions.h>




    //Function used to write data to a file
    void fWrite(std::string fileName, std::vector<double> data)
    {
        std::fstream file;
        //Open file
        file.open(fileName, std::fstream::out);
        std::string s = "";
        //Convert the array into string format

        for(int i = 0; i<data.size(); i++)
        {
            s += toString(data.at(i)) + "\n";
        }
        //Skip the last empty line
        s += "\b";
        //Write string data into file
        file << s;
        //Close file
        file.close();
    }

    //Function used to read data from a file
    std::vector<double> fRead(std::string fileName)
    {
        std::fstream file;
        file.open(fileName);
        std::string line;
        //Allocate the static output array
        std::vector<double> data;
        while(!file.eof())
        {
            getline(file, line);
            data.push_back(atof(line.c_str()));
        }
        data.pop_back();
        file.close();
        return data;
    }

