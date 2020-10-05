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
        Interface(int  );

        
    public:
        static Interface * makeInterfaceInstance(int  );

        MeasureSimilarity*   buildMeasureSimilarity( int ,int ,vector<double *> );

        Classifier* buildClassifier(size_t , vector<double *> ,size_t);

        unique_ptr <TimeSeries> buildTimeSeries(string path,  size_t Dim);

        void chooseMethod(vector <string>  ,vector <double *>,int,string);

        void sendRepoToCompareClass( vector< vector<int> > * , vector< vector<double> > * ,string   _methodName);
        void doClassifier(vector <  vector< vector<double> > >  * ,string   _methodName);
        
        void readLablesPath(string,size_t numberOfDataset=1);
        void checkTimeSeriesData();
        void createTimeSeriesInstances( size_t Dim);
        void readDataset(string,size_t numberOfDataset=1);

        void setTimeSeriesLabels(size_t numberOfDataset);

        void freeMeasureSimilarityInstance();

        void swap(string &, string &) ;
        void bubbleSort(vector <string> &) ;
        void writeInOutput();



        ~ Interface();

};


#endif /* Interface_hpp */
