// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Wdtw.hpp


#ifndef OneNearestNeighbour_hpp
#define OneNearestNeighbour_hpp


#include <string>
#include <vector>
#include <memory>
#include "Classifier.hpp"
#include "Output.hpp"


using namespace std;

class OneNearestNeighbour : public Classifier
{
    private :
		vector <  vector< vector<double> > > resultDiagramDist;

        int foldNumber;
        int iterationNumber;
        Output *output;


    public :
        void classifying(vector <  vector< vector<double> > >* ,string , vector < vector <string> >  );


        OneNearestNeighbour(double *_iterationNumber, double *_foldNumber,size_t  );

        void addToDiagramDist( vector <  vector< vector<double> > > & _resultDiagram);

        void writeResult(vector <double > &);

        void do_1NN(vector < vector <string> > , vector <double > & );
};


#endif /* OneNearestNeighbour_hpp */
