// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "ResultRepository.hpp"
#include <string>
#include <iostream>
#include <memory>

using namespace std;


//--------------------------------------------------------------------------------------------------------------------------------

void ResultRepository::addToDiagramDist( vector< vector<double> >  _resultDiagram)
{
    resultDiagramDist[numberOfMethod].resize(_resultDiagram.size());
    for (size_t i=0; i< _resultDiagram.size() ; i++ )
        resultDiagramDist[numberOfMethod][i].assign( _resultDiagram[i].begin() , _resultDiagram[i].end() );
    
}

//--------------------------------------------------------------------------------------------------------------------------------
void ResultRepository::addToDiagramLen( vector< vector<int> >  _resultDiagram)
{
    resultDiagramLen[numberOfMethod].resize(_resultDiagram.size());
    for (size_t i=0; i< _resultDiagram.size() ; i++ )
        resultDiagramLen[numberOfMethod][i].assign( _resultDiagram[i].begin() , _resultDiagram[i].end() );
    
}

//--------------------------------------------------------------------------------------------------------------------------------
void ResultRepository::increaseNumberOfMethod()
{
    numberOfMethod++;
}

//--------------------------------------------------------------------------------------------------------------------------------

ResultRepository::ResultRepository(int size)
{
	resultDiagramDist.resize(size);
	resultDiagramLen.resize(size);

    output = Output::makeOutputInstance() ;
    numberOfMethod = 0;
}

//--------------------------------------------------------------------------------------------------------------------------------

void ResultRepository::writeResultInOutput()
{
    
    output->writeInFile(resultDiagramDist, resultDiagramLen);
 
}

//--------------------------------------------------------------------------------------------------------------------------------
unique_ptr < vector <  vector< vector<double> > > >  ResultRepository::uniquePtrOfDistRepo()
{
	std::unique_ptr <vector <  vector< vector<double> > >  > ptr(&resultDiagramDist);
	return ptr;
}
//--------------------------------------------------------------------------------------------------------------------------------
