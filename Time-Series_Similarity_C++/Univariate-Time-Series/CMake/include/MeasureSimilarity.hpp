// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  MeasureSimilarity.hpp


#ifndef MeasureSimilarity_hpp
#define MeasureSimilarity_hpp
#include <vector>
#include <memory>
using namespace std;
class TimeSeries;

class MeasureSimilarity
{
    private :
    
    public :
        virtual ~MeasureSimilarity()=0;
        virtual void compute(TimeSeries *, TimeSeries * ,double &,int  &  )=0;
        virtual void     computeAll(vector < unique_ptr <TimeSeries> > &  )=0;
        virtual vector< vector<int>    > * addressRepoLen()=0;
        virtual vector< vector<double> > * addressRepoDist()=0;

};

#endif /* MeasureSimilarity_hpp */
