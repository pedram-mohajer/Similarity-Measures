// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Wdtw.hpp


#ifndef Wdtw_hpp
#define Wdtw_hpp


#include "MeasureSimilarity.hpp"
#include "TimeSeries.hpp"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Wdtw : public MeasureSimilarity
{
    private :
    double  winRatio;
    double  winSize;
    double  weightMax;
    double g;
    vector< vector<double > >     wdtwDist;
    vector< vector<int    > >     wdtwLen;
    
    
    public :
    virtual void     compute(TimeSeries *ts1, TimeSeries *ts2 ,double & _wdtwDist,int &_wdtwLen);
    virtual void     computeAll(std::vector < std::unique_ptr <TimeSeries> > &path);
    double  euclideanCalculate(vector<vector <string>> &ts1,int n1,vector<vector <string>> &ts2,int n2,int dim, int idx1,int idx2);
    virtual vector< vector<int>   >  * addressRepoLen();
    virtual vector< vector<double> > * addressRepoDist();
    virtual ~Wdtw();
    double   getParam();
    Wdtw(int size,double*,double*,double*,double*);
    
    double weightCalculate(int i, int j, int n1, int n2, double g, double weightMax);
};


#endif /* Wdtw_hpp */
