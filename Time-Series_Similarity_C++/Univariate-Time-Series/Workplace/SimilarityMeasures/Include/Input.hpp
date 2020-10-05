// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Input.hpp


#ifndef Input_hpp
#define Input_hpp

#include <vector>
#include <string>
using namespace std;


class Input
{
    private :

        void setInputs(int argc, const char * argv[]);
        vector <string> inputs;

    public :
        string getLogFilePath();
        string getOutputFilePath();
        vector <string> getInputs();
        void preProcessing(int argc, const char * argv[]);
        Input();
};

#endif /* Input_hpp */


