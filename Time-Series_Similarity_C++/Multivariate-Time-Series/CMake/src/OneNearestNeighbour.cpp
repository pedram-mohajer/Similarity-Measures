// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------



#include "OneNearestNeighbour.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include "Output.hpp"

using namespace std;


//--------------------------------------------------------------------------------------------------------------------------------

void OneNearestNeighbour::addToDiagramDist(  vector <  vector< vector<double> > >  &_resultDiagram)
{
	resultDiagramDist.clear();

	for (size_t i=0; i< _resultDiagram.size() ; i++ )
		resultDiagramDist.push_back(_resultDiagram[i]);

}

//--------------------------------------------------------------------------------------------------------------------------------

OneNearestNeighbour::OneNearestNeighbour(double *_iterationNumber, double *_foldNumber,size_t size) : iterationNumber( _iterationNumber[0]), foldNumber(_foldNumber[0])
{
	resultDiagramDist.resize(size);
    this->output = Output::makeOutputInstance() ;

}
//--------------------------------------------------------------------------------------------------------------------------------
void OneNearestNeighbour::do_1NN( vector < vector <string> >  labelPathRepository, vector <double > &percentage )
{

	 int size = (int) resultDiagramDist.size();

	std::vector <vector <int> > indexVectorOfMins(size);


    double positive_infinity(std::numeric_limits<double>::infinity());
    double negative_infinity(-std::numeric_limits<double>::infinity());

	double max    = negative_infinity,
		   min    = positive_infinity,
		   maxAll = negative_infinity, temp;



	vector <int> tempVector;


	// --------------------------------------

    for(int k=0; k<size ; k++)
		for (int i=0;  i<resultDiagramDist[k].size() ; i++ )
		{
			for (int j=0; j < resultDiagramDist[k][i].size() ; j++ )
			{
				temp  = resultDiagramDist[k][i][j];
				if(temp>max)
					max = temp;
			}
			if (maxAll < max)
				maxAll = max;
		}

    // --------------------------------------


    for(int k=0; k<size ; k++)
		for (int i=0;  i<resultDiagramDist[k].size() ; i++ )
			for (int j=0; j < resultDiagramDist[k][i].size() ; j++ )
			{
				if( i == j )
					resultDiagramDist[k][i][j] = maxAll+1;
    			if( i < j )
    				resultDiagramDist[k][j][i] = resultDiagramDist[k][i][j] ;
			}

    // --------------------------------------

    for(int k=0; k<size ; k++)
    {
    	tempVector.resize( resultDiagramDist[k].size() );

		for (int i=0;  i<resultDiagramDist[k].size() ; i++ )
		{
			for (int j=0; j < resultDiagramDist[k][i].size() ; j++ )
			{
				if( i != j )
				{
					temp = resultDiagramDist[k][i][j];
					if(temp < min)
					{
						tempVector[i] = j;


						min = temp;
					}
				}
			}
			min    = positive_infinity;
		}


		indexVectorOfMins[k] = tempVector;
		tempVector.clear();

    }


	// --------------------------------------


	percentage.resize( indexVectorOfMins.size() );

	int count=0;

	for(int i=0 ; i<indexVectorOfMins.size() ; i++)
		{
			for(int j=0 ; j<indexVectorOfMins[i].size() ; j++)
				if(indexVectorOfMins[i][j] ==  stoi( labelPathRepository[i][j])  )
					count++;
			percentage[i] = 100 * ((double) count/ indexVectorOfMins[i].size()) ;
			count = 0 ;
		}

}
//--------------------------------------------------------------------------------------------------------------------------------

void OneNearestNeighbour::classifying(vector <  vector< vector<double> > > * dtwDistRepo,string _methodName ,vector < vector <string> > labelRepository )
{
	vector <double > accuracy;

	addToDiagramDist(*dtwDistRepo);

	do_1NN(labelRepository, accuracy );

	writeResult(accuracy);


}

//--------------------------------------------------------------------------------------------------------------------------------
void OneNearestNeighbour::writeResult(vector <double > &accu)
{
	string classifierName= "1NN";
	output->writeClassifierInFile(accu, classifierName );
}
//--------------------------------------------------------------------------------------------------------------------------------





//--------------------------------------------------------------------------------------------------------------------------------


