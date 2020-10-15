// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Classifier.hpp


#ifndef Classifier_hpp
#define Classifier_hpp

#include <vector>
#include <memory>

using namespace std;

class TimeSeries;

class Classifier
{
    private :
    
    public :
        virtual ~Classifier()=0;
        virtual void classifying(  vector <  vector< vector<double> > >   *,string ,vector < vector <string> >  )=0;


};

#endif /* Classifier_hpp */
