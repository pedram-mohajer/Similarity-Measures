// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Sspd.hpp


#ifndef Sspd_hpp
#define Sspd_hpp

#include "MeasureSimilarity.hpp"
#include "TimeSeries.hpp"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Sspd : public MeasureSimilarity
{
    private :
    
    vector< vector<double > >     sspdDist;
    vector< vector<int    > >     sspdLen;
    
    
    public :
    virtual void     compute(TimeSeries *ts1, TimeSeries *ts2 ,double & _erPDist,int &_erPLen);
    virtual void     computeAll(std::vector < std::unique_ptr <TimeSeries> > &path);
    double point2SegmentDistance(double *ts1, int n1, double *ts2, int n2, int dim, int idx1, int idx2);

    virtual vector< vector<int>   >  * addressRepoLen();
    virtual vector< vector<double> > * addressRepoDist();
    virtual ~Sspd();
    
    Sspd(int size);
    
};





#endif /* Sspd_hpp */
