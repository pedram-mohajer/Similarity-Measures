// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Twed.hpp


#ifndef Twed_hpp
#define Twed_hpp


#include "MeasureSimilarity.hpp"
#include "TimeSeries.hpp"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Twed : public MeasureSimilarity
{
    private :
    double  winRatio;
    double  lambda;
    double  winSize;
    double nu;
    vector< vector<double > >     twedDist;
    vector< vector<int    > >     twedLen;
    
    
    public :
    virtual void     compute(TimeSeries *ts1, TimeSeries *ts2 ,double & _twedDist,int &_twedLen);
    virtual void     computeAll(std::vector < std::unique_ptr <TimeSeries> > &path);
    double  euclideanCalculate(vector<vector <string>> &ts1,int n1,vector<vector <string>> &ts2,int n2,int dim, int idx1,int idx2);
    virtual vector< vector<int>   >  * addressRepoLen();
    virtual vector< vector<double> > * addressRepoDist();
    virtual ~Twed();
    double   getParam();
    Twed(int size,double*,double*,double*,double*);
    
    
};




#endif /* Twed_hpp */
