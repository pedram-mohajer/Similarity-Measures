// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Swale.hpp


#ifndef Swale_hpp
#define Swale_hpp


#include "MeasureSimilarity.hpp"
#include "TimeSeries.hpp"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Swale : public MeasureSimilarity
{
    private :
    double  winRatio;
    double  winSize;
    double  eps;
    double gapC;
    double reward;
    vector< vector<double > >     swaleDist;
    vector< vector<int    > >     swaleLen;
    
    
    public :
    virtual void     compute(TimeSeries *ts1, TimeSeries *ts2 ,double & _swaleDist,int &_swaleLen);
    virtual void     computeAll(std::vector < std::unique_ptr <TimeSeries> > &path);
    double euclideanCalculate(vector <double>  ts1,int n1,vector <double>  ts2,int n2,int dim, int idx1,int idx2);
    virtual vector< vector<int>   >  * addressRepoLen();
    virtual vector< vector<double> > * addressRepoDist();
    virtual ~Swale();
    double   getParam();
    Swale(int size,double*,double*,double*,double*,double*);
    
    
};


#endif /* Swale_hpp */
