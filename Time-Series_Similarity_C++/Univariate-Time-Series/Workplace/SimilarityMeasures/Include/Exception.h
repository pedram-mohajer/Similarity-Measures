// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Exception.h


#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
using namespace std;


class Exception

{
    protected :
        string fileName;
        string msg;
        int line;
    public:
        string get_msg();
        int    get_line();
        string get_fileName();
        void   makeNull();
};

class ReadFileError : public Exception
{
    
    public :
        ReadFileError (string _msg,string _fileName=" ",int _line=-1) ;
    
};

class ErrorInTsdHeaderFile : public Exception
{
    
    public :
        ErrorInTsdHeaderFile (string _msg,string _fileName=" ",int _line=-1);

};

class ErrorInTsdFooterFile : public Exception
{
 
    public :
        ErrorInTsdFooterFile (string _msg,string _fileName=" ",int _line=-1);

};
class WrongInput : public Exception
{
    public :
        WrongInput (string _msg,string _fileName=" ",int _line=-1);

};

class WrongExecution : public Exception
{
    public :
    WrongExecution (string _msg,string _fileName=" ",int _line=-1);
    
};

class InequalityInNumberOFLabelsAndData : public Exception
{
    public :
	InequalityInNumberOFLabelsAndData (string _msg,string _fileName=" ",int _line=-1);

};

class OutputFileError : public Exception
{
    public :
	OutputFileError (string _msg,string _fileName=" ",int _line=-1);

};



#endif /* Exception_h */
