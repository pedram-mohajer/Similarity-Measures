// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Hausdorff.hpp


#ifndef Hausdorff_hpp
#define Hausdorff_hpp

#include "MeasureSimilarity.hpp"
#include "TimeSeries.hpp"
#include <string>
#include <vector>
#include <memory>


using namespace std;

class Hausdorff : public MeasureSimilarity
{
    private :
    vector< vector<double > >     hausdorffDist;
    vector< vector<int    > >     hausdorffLen;
    
    
    public :
    virtual void     compute(TimeSeries *ts1, TimeSeries *ts2 ,double & _erPDist,int &_erPLen);
    virtual void     computeAll(std::vector < std::unique_ptr <TimeSeries> > &path);
    double point2SegmentDistance(vector <double> ts1, int n1,vector <double> ts2, int n2, int dim, int idx1, int idx2);
    
    virtual vector< vector<int>   >  * addressRepoLen();
    virtual vector< vector<double> > * addressRepoDist();
    virtual ~Hausdorff();

    
    Hausdorff(int size);
    
};



#endif /* Hausdorff_hpp */
