// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "Log.hpp"
#include <iostream>

using namespace std;

//----------------------------------------------------------------------------------------------------
void Log::writeExceptionInLogFile()
{
    logWriteStream << exception.get_msg() << endl;
    logWriteStream << "This error is in File : " << exception.get_fileName() << endl;
    logWriteStream << "This error is in Line : " << exception.get_line()     << endl;
}
//----------------------------------------------------------------------------------------------------
Log::Log()
{
    
}

//----------------------------------------------------------------------------------------------------

void Log::setPath(string _path)
{
    
    path.push_back(_path);
}

//----------------------------------------------------------------------------------------------------

void Log::preProcessing(string _path)
{
    setPath(_path);
    openLogFile();
}

//----------------------------------------------------------------------------------------------------

void Log::openLogFile()
{
    logWriteStream.open(path.back());
    path.pop_back();

}

//----------------------------------------------------------------------------------------------------

void Log::setException(Exception _exception)
{
    exception = _exception;
}

//----------------------------------------------------------------------------------------------------

void Log::setExceptionNull()
{
    exception.makeNull();
}

//----------------------------------------------------------------------------------------------------

