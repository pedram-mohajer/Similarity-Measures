// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Edr.hpp


#ifndef Edr_hpp
#define Edr_hpp

#include "MeasureSimilarity.hpp"
#include "TimeSeries.hpp"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Edr : public MeasureSimilarity
{
    private :
    double winRatio;
    double  epsilon;
    double  winSize;
    vector< vector<double > >     edrDist;
    vector< vector<int    > >     edrLen;
    
    
    public :
    virtual void     compute(TimeSeries *ts1, TimeSeries *ts2 ,double & _edrDist,int &_edrLen);
    virtual void     computeAll(std::vector < std::unique_ptr <TimeSeries> > &path);
    double  euclideanCalculate(vector<vector <string>> &ts1,int n1,vector<vector <string>> &ts2,int n2,int dim, int idx1,int idx2);
    virtual vector< vector<int>   >  * addressRepoLen();
    virtual vector< vector<double> > * addressRepoDist();
    virtual ~Edr();

    double   getParam();
    Edr(int size,double*,double*,double*);
   
    
};


#endif /* Edr_hpp */
