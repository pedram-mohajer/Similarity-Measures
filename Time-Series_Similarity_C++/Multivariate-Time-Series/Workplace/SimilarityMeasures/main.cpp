//============================================================================
// Name        : TimeSeriesMain.cpp
// Author      : PedramMohajer
// Version     :
// Copyright   : Your copyright notice
// Description : Time-Series in C++, Ansi-style
//============================================================================


#include <iostream>
#include "Similarity.hpp"
#include <cmath>
using namespace std;

int main(int argc, const char * argv[])
{

        Similarity *similarity = new Similarity();
	system("clear");

        try
        {
            similarity->processing(argc,argv);
        }
        catch(Exception &error)
        {
            similarity->HandleException(error);
	    cout << "\n Error, Please Check Log  File \n";
	    exit(1);
        }

        similarity->freeSimilarityObject();


        cout << "\n The Program Is Successfully Finished \n";
        return 0;
}
