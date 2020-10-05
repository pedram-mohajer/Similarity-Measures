// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Cidtw.hpp


#ifndef Cidtw_hpp
#define Cidtw_hpp


#include "MeasureSimilarity.hpp"
#include "TimeSeries.hpp"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Cidtw : public MeasureSimilarity
{
    private :
    double  winRatio;
    double  winSize;
    vector< vector<double > >     cidtwDist;
    vector< vector<int    > >     cidtwLen;
    
    public :
     virtual ~Cidtw();
     virtual void     compute(TimeSeries *ts1, TimeSeries *ts2 ,double & _dtwDist,int &_dtwLen);
     virtual void     computeAll(std::vector < std::unique_ptr <TimeSeries> > &path);
     virtual vector< vector<int>   >  * addressRepoLen();
     virtual vector< vector<double> > * addressRepoDist();
    
     double   getParam();
    
     double  euclideanCalculate(vector<vector <string>> &ts1,int n1,vector<vector <string>> &ts2,int n2,int dim, int idx1,int idx2);

     Cidtw(int size,double*,double*);
 

};

#endif /* Cidtw_hpp */
