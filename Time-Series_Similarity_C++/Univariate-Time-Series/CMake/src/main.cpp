//============================================================================
// Name        : TimeSeriesMain.cpp
// Author      : PedramMohajer
// Version     :
// Copyright   : Your copyright notice
// Description : Time-Series in C++, Ansi-style
//============================================================================


#include <iostream>
#include "Similarity.hpp"


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
        }

        similarity->freeSimilarityObject();

        cout << "\n finsihed \n";
        return 0;
}
