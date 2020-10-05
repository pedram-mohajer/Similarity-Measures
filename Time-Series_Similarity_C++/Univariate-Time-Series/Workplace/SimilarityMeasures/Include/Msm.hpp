// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Msm.hpp


#ifndef Msm_hpp
#define Msm_hpp

#include "MeasureSimilarity.hpp"
#include "TimeSeries.hpp"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Msm : public MeasureSimilarity
{
    private :
    double  winRatio;
    double  cost;
    double  winSize;
    vector< vector<double > >    msmDist;
    vector< vector<int    > >    msmLen;
    
    
    public :
    virtual void     compute(TimeSeries *ts1, TimeSeries *ts2 ,double & _msmDist,int &_msmLen);
    virtual void     computeAll(std::vector < std::unique_ptr <TimeSeries> > &path);
    double euclideanCalculate(double *ts1,int n1,double *ts2,int n2,int dim, int idx1,int idx2);
    virtual vector< vector<int>   >  * addressRepoLen();
    virtual vector< vector<double> > * addressRepoDist();
    virtual ~Msm();
    double msmCost(double *tsA, int nA, double *tsB, int nB, double *tsC, int nC, int dim, double cost, int idxA, int idxB, int idxC);
    
    double  getParam();
    Msm(int size,double*,double*,double*);
    
};

#endif /* Msm_hpp */
