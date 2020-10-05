// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Erp.hpp


#ifndef Erp_hpp
#define Erp_hpp

#include "MeasureSimilarity.hpp"
#include "TimeSeries.hpp"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Erp : public MeasureSimilarity
{
    private :
    double  winRatio;
    double  winSize;
    double * gap;
    vector< vector<double > >     erpDist;
    vector< vector<int    > >     erpLen;

    
    public :
    virtual void     compute(TimeSeries *ts1, TimeSeries *ts2 ,double & _erPDist,int &_erPLen);
    virtual void     computeAll(std::vector < std::unique_ptr <TimeSeries> > &path);

    double  euclideanCalculate(vector<vector <string>> &ts1,int n1,vector<vector <string>> &ts2,int n2,int dim, int idx1,int idx2);
    
    virtual vector< vector<int>   >  * addressRepoLen();
    virtual vector< vector<double> > * addressRepoDist();
    virtual ~Erp();
    double getParam();
    
    
    Erp(int size,double * ,double * ,double *);
    
};


#endif /* Erp_hpp */
