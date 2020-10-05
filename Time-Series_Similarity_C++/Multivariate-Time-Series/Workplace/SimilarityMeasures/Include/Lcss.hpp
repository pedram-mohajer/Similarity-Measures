// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Lcss.hpp


#ifndef Lcss_hpp
#define Lcss_hpp



#include "MeasureSimilarity.hpp"
#include "TimeSeries.hpp"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Lcss : public MeasureSimilarity
{
    private :
    double winRatio;
    double  epsilon;
    double  winSize;
    vector< vector<double > >     lcssDist;
    vector< vector<int    > >     lcssLen;
    
    
    public :
    virtual void     compute(TimeSeries *ts1, TimeSeries *ts2 ,double & _lcssDist,int &_lcssLen);
    virtual void     computeAll(std::vector < std::unique_ptr <TimeSeries> > &path);
    double  euclideanCalculate(vector<vector <string>> &ts1,int n1,vector<vector <string>> &ts2,int n2,int dim, int idx1,int idx2);
    virtual vector< vector<int>   >  * addressRepoLen();
    virtual vector< vector<double> > * addressRepoDist();
    virtual ~Lcss();
    double   getParam();
    Lcss(int size,double*,double*,double*);
    
    
};


#endif /* Lcss_hpp */
