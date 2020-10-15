// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Dtw.hpp


#ifndef Dtw_hpp
#define Dtw_hpp

#include "MeasureSimilarity.hpp"
#include "TimeSeries.hpp"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Dtw : public MeasureSimilarity
{
    private :
        double  winRatio;
        double  winSize;
        vector< vector<double > >     dtwDist;
        vector< vector<int    > >     dtwLen;
        
    public :
        virtual void  compute(TimeSeries *ts1, TimeSeries *ts2 ,double & _dtwDist,int &_dtwLen);
        virtual void     computeAll(std::vector < std::unique_ptr <TimeSeries> > &path);
        virtual vector< vector<int>   >  * addressRepoLen();
        virtual vector< vector<double> > * addressRepoDist();
        virtual ~Dtw();
        
        double   getParam();
        double euclideanCalculate(vector <double> ts1,int n1,vector <double> ts2,int n2,int dim, int idx1,int idx2);

    
        Dtw(int size,double *,double *);
      
};



#endif /* Dtw_hpp */
