// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  DiscreteFrechet.hpp


#ifndef DiscreteFrechet_hpp
#define DiscreteFrechet_hpp

#include "MeasureSimilarity.hpp"
#include "TimeSeries.hpp"
#include <string>
#include <vector>
#include <memory>


class DiscreteFrechet : public MeasureSimilarity
{
    private :

        vector< vector<double > >     discreteFrechetDist;
        vector< vector<int    > >     discreteFrechetLen;
    
    public :
        virtual void  compute(TimeSeries *ts1, TimeSeries *ts2 ,double & _discreteFrechetDist,int &_discreteFrechetLen);
        virtual void  computeAll(vector < unique_ptr <TimeSeries> > & path);
        virtual vector< vector<int>    > * addressRepoLen();
        virtual vector< vector<double> > * addressRepoDist();
        virtual ~DiscreteFrechet();
       

        DiscreteFrechet(size_t size);
    
        double recursiveFunc(TimeSeries *Ts1,size_t n1,TimeSeries *Ts2, size_t n2,size_t dim,vector<double> ca,size_t idx1 ,size_t idx2);
};



#endif /* DiscreteFrechet_hpp */
