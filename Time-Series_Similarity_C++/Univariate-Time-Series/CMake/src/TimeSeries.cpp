// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include <fstream>
#include <string.h>
#include "Exception.h"
#include "Functions.hpp"
#include "TimeSeries.hpp"


using namespace std;


//------------------------------------------------------------------------------------------------

void TimeSeries::setTimeSerieData()
{
    
    string tempData;
    int j=0;
    
    while(readFile && j<14)
    {
        j++;
        readFile >> tempData;
        if(j==8)
            dimensional = stoi(tempData);
        
    }
    while(readFile)
    {
        readFile >> tempData;
        timeSerieData.push_back(tempData) ;
    }
    size=timeSerieData.size();
}


//------------------------------------------------------------------------------------------------

void TimeSeries::openFile()
{
    readFile.open(timeSerieDataPath,ios::in);
    if(!readFile)
        throw ReadFileError("File is not opened in path : ", timeSerieDataPath);
}


//------------------------------------------------------------------------------------------------

void TimeSeries::setTimeSerieDataPath(string _timeSerieDataPath)
{
    timeSerieDataPath.resize(_timeSerieDataPath.length());
    strTostr(timeSerieDataPath, _timeSerieDataPath);
}


//------------------------------------------------------------------------------------------------

string TimeSeries::getTimeSerieDataPath()
{
    return timeSerieDataPath ;
}

//------------------------------------------------------------------------------------------------

TimeSeries::TimeSeries(string _timeSerieDataPath)
{
        setTimeSerieDataPath(_timeSerieDataPath);
        openFile();
        setTimeSerieData();
}

//------------------------------------------------------------------------------------------------

vector <string> TimeSeries::getTimeSerieData()
{
    return timeSerieData;
}

//------------------------------------------------------------------------------------------------

size_t TimeSeries::getSize()
{
    return size;
}

//------------------------------------------------------------------------------------------------

size_t TimeSeries::getDimensional()
{
    return dimensional;
}

//------------------------------------------------------------------------------------------------
TimeSeries::TimeSeries()
{
    
}
//------------------------------------------------------------------------------------------------
void TimeSeries::setLabel(string _label)
{
	this->label = _label;
}

//------------------------------------------------------------------------------------------------

string TimeSeries::getLabels()
{
	return label;
}
//------------------------------------------------------------------------------------------------





