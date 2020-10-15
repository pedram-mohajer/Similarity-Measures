// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include <iomanip>
#include "Output.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//------------------------------------------------------------------------------------------------

Output * Output::outputInstance=0;

//------------------------------------------------------------------------------------------------
Output * Output::makeOutputInstance()
{
    if( outputInstance == 0 )
        outputInstance = new Output();
    return outputInstance;
}
//------------------------------------------------------------------------------------------------
void Output::preProcessing(string path)
{
    openOutputFileStream(path);
}
//------------------------------------------------------------------------------------------------

void Output::openOutputFileStream(string path)
{
	remove(path.c_str());
	outputFileStream.open(path,std::ios::app);

}
//------------------------------------------------------------------------------------------------
Output::Output()
{
    
}
//------------------------------------------------------------------------------------------------
 void Output::writeInFile(vector <  vector< vector<double>>> resultDiagramDist,vector <vector< vector<int>>> resultDiagramLen)
{
    outputFileStream << "Distance Matrix : \n" ;
	outputFileStream << "------------------------------------------------------------------------------------------ \n" ;

    double temp;

    for (size_t k=0;  k<resultDiagramDist.size() ; k++ )
    {	outputFileStream << "\n Dataset " << k+1 << " : \n";
		for (size_t i=0;  i<resultDiagramDist[k].size() ; i++ )
		{
			for (size_t j=0; j < resultDiagramDist[k][i].size() ; j++ )
			{
				outputFileStream <<resultDiagramDist[k][i][j] << "\t\t";
				if(i==0 && j == resultDiagramDist[k][i].size()-1)
						temp = resultDiagramDist[k][i][j];
			}
				outputFileStream << endl;
		}
		 outputFileStream << "------------------------------------------------------------------------------------------ \n" ;

    }
    outputFileStream << "\n\n\n\n";

    outputFileStream <<"Length Matrix : \n" ;
	outputFileStream << "------------------------------------------------------------------------------------------ \n" ;


    for (size_t k=0;  k<resultDiagramDist.size() ; k++ )
    {	outputFileStream << "\n Dataset " << k+1 << " : \n";

		for (size_t i=0;  i<resultDiagramDist[k].size() ; i++ )
		{
			for (size_t j=0; j < resultDiagramDist[k][i].size() ; j++ )
			{
				 outputFileStream << resultDiagramLen[k][i][j] << "\t\t";
				 if(i==0 && j == resultDiagramDist[k][i].size()-1)
					 temp = resultDiagramDist[k][i][j];
			}
			outputFileStream << endl;
		}
	    outputFileStream << "\n------------------------------------------------------------------------------------------ \n" ;

    }

}
//------------------------------------------------------------------------------------------------

 void Output::writeClassifierInFile(const vector <double > & result, string classifierName)
 {
	    outputFileStream << "\n------------------------------------------------------------------------------------------ \n" ;
	 outputFileStream << classifierName << " Result :  \n";
	 for (size_t i=0; i<result.size(); i++)
	 	 outputFileStream <<  "Dataset " << i+1 << " : " << result[i]  << "%" <<endl;
	    outputFileStream << "\n------------------------------------------------------------------------------------------ \n" ;

 }
 //------------------------------------------------------------------------------------------------



