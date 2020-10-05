// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Frechet.hpp


#ifndef Frechet_hpp
#define Frechet_hpp

#include "MeasureSimilarity.hpp"
#include "TimeSeries.hpp"
#include <string>
#include <vector>
#include <memory>


using namespace std;

class Frechet : public MeasureSimilarity
{
    private :
    vector< vector<double > >     frechetDist;
    vector< vector<int    > >     frechetLen;
    
    
    public :
    virtual void     compute(TimeSeries *ts1, TimeSeries *ts2 ,double & _erPDist,int &_erPLen);
    virtual void     computeAll(std::vector < std::unique_ptr <TimeSeries> > &path);
   
    double point2SegmentDistance(double *ts1, int n1, double *ts2, int n2, int dim, int idx1, int idx2);
    
    
    void criticValCalculate(double *ts1, int n1, double *ts2, int n2, int dim, double *criticVal, int *criticSize);
    
    void circleLineIntersectCalculation(double *ts1, int n1, double *ts2, int n2, int dim, double radius, int idx1, int idx2,
                                        double * matrix[] , int _column);

    void freelineCalculate(double *ts1, int n1, double *ts2, int n2, int dim, double eps, int idx1, int idx2, double *valPt1, double *valPt2);

    void freespaceCalculate(double *ts1, int n1, double *ts2, int n2, int dim, double eps, double ***LF, double ***BF);
    
    bool reachableCalculate(double *ts1, int n1, double *ts2, int n2, int dim, double eps);

    
    virtual vector< vector<int>   >  * addressRepoLen();
    virtual vector< vector<double> > * addressRepoDist();
    virtual ~Frechet();

    
    Frechet(int size);
    
};



#endif /* Frechet_hpp */
