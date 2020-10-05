// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Log.hpp


#ifndef Log_hpp
#define Log_hpp


#include <fstream>
#include <string>
#include "Exception.h"
#include <vector>

using namespace std;



class Log
{
    private :
        ofstream logWriteStream;
        vector <string> path;
        Exception exception;
        void setPath(string );
    public :
        void preProcessing(string );
        void writeExceptionInLogFile();
        void openLogFile();
        void setException(Exception _exception);
        void setExceptionNull(); 
        Log();
    
};
#endif /* Log_hpp */
