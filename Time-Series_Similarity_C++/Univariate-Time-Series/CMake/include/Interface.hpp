// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

// Interface_hpp


#ifndef Interface_hpp
#define Interface_hpp

#include "OneNearestNeighbour.hpp"
#include "MeasureSimilarity.hpp"
#include "Classifier.hpp"
#include <string>
#include "TimeSeries.hpp"
#include <vector>
#include <memory>
#include "ResultRepository.hpp"


using namespace std;


class Interface
{
    private:
    
        vector < vector <unique_ptr <TimeSeries> > > timeSeries;

        unique_ptr <Classifier> 		 classifier;
        unique_ptr <MeasureSimilarity>   measureSimilarity;

        ResultRepository *resultRepository;

        vector <vector <string> >   dataPathRepository;

        vector <string>			   labelPathRepository;
        vector < vector <string> > labelRespository;

        static Interface * interfaceInstance;
        Interface(double *);
        
    public:
        static Interface * makeInterfaceInstance(double *);

        MeasureSimilarity*   buildMeasureSimilarity( int ,int ,vector<double *> );

        Classifier* buildClassifier(size_t , vector<double *> ,size_t);

        unique_ptr <TimeSeries> buildTimeSeries(string path);

        void chooseMethod(vector <string>  ,vector <double *>,int,string);

        void sendRepoToCompareClass( vector< vector<int> > * , vector< vector<double> > * ,string   _methodName);
        void doClassifier(vector <  vector< vector<double> > >  * ,string   _methodName);
        
        void readLablesPath(string,size_t);
        void checkTimeSeriesData();
        void createTimeSeriesInstances();
        void readDataset(string,size_t);

        void setTimeSeriesLabels(size_t );

        void freeMeasureSimilarityInstance();

        void swap(string &, string &) ;
        void bubbleSort(vector <string> &) ;
        void writeInOutput();
        ~ Interface();

};


#endif /* Interface_hpp */
