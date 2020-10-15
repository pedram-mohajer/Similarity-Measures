// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Output.hpp


#ifndef Output_hpp
#define Output_hpp

#include <string>
#include <fstream>
#include <vector>

using namespace std;


class Output
{
    private :
    
        Output();
        ofstream outputFileStream;
        static Output * outputInstance;
    public :
        static Output * makeOutputInstance();
        void preProcessing(string);
        void openOutputFileStream(string);
        void writeInFile(vector <  vector< vector<double   > > >,vector <  vector< vector<int   > > >);
        void writeClassifierInFile(const vector <double > &  ,  string );
};





#endif /* Output_hpp */
