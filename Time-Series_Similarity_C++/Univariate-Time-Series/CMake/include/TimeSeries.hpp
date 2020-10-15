// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  TimeSeries.hpp


#ifndef TimeSeries_hpp
#define TimeSeries_hpp


#include <string>
#include <fstream>
#include <vector>

class TimeSeries
{
    private :
        size_t size;
        string label;
        size_t dimensional;
        std::ifstream readFile;
        std::string timeSerieDataPath;
        std::vector <std::string> timeSerieData;
    
        std::string getTimeSerieDataPath();
        void setTimeSerieDataPath(std::string _timeSerieDataPath);
        void openFile();
        void setTimeSerieData();

    public :
        TimeSeries();
        size_t getSize();
        size_t getDimensional();
        TimeSeries (std::string _timeSerieDataPath);
        std::vector  <std::string> getTimeSerieData();
        void setLabel(string);
        string getLabels();
   
    
};
#endif /* TimeSeries_hpp */
