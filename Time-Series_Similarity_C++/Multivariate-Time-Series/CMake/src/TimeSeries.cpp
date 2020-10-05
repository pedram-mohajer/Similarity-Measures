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

void TimeSeries::setTimeSerieData(size_t Dim)
{
	timeSerieData.resize(Dim);

    string tempData;
    int j=1;
    
    while(j<8)
    {
        getline(readFile, tempData);
        if(j==4)
        {
            dimensional = stoi( tempData.substr(tempData.find(" ")+1));
            if(Dim  != dimensional )
            	throw  WrongDimension("Dimension entered does not match with data\n","TimeSeries.cpp");
        }
        j++;
    }



    for( int currentDimInt = 0; currentDimInt<Dim; ++currentDimInt)
    {
    	string dimension     = string("Dim").append( to_string(currentDimInt+1) );
		string nextDimension = string("Dim").append( to_string(currentDimInt+2) );

		while(tempData.compare(dimension) != 0)
			readFile >> tempData;

		while( readFile >> tempData)
		{
			if(tempData.compare(nextDimension) == 0 )
					break;

			timeSerieData[currentDimInt].push_back(tempData) ;


			size = timeSerieData[currentDimInt].size();

		}

    }
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
    timeSerieDataPath.resize(_timeSerieDataPath.length() );
    strTostr(timeSerieDataPath, _timeSerieDataPath);
}


//------------------------------------------------------------------------------------------------

string TimeSeries::getTimeSerieDataPath()
{
    return timeSerieDataPath ;
}

//------------------------------------------------------------------------------------------------

TimeSeries::TimeSeries(string _timeSerieDataPath ,size_t Dim)
{
        setTimeSerieDataPath(_timeSerieDataPath);
        openFile();
        setTimeSerieData(Dim);
}

//------------------------------------------------------------------------------------------------

vector <vector <string>> TimeSeries::getTimeSerieData()
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





