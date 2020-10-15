// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

#include "Input.hpp"
#include "Exception.h"
#include <iostream>

using namespace std;

// ----------------------------------------------------------------------------------------------
//     Description
// --------------
//		input[0]  ==> method;
//									METHOD NAME					Attributes
//								    -------------		   -----------------------------------
// 		 			  method == 0   	 DTW                   winSize & WinRatio
// 					  method == 1     	 CIDTW                 winSize & WinRatio
// 					  method == 2     	 DISCRETEFRECHET       ------
// 				  	  method == 3  		 EDR                   winSize & WinRatio & epsilon
// 					  method == 4  		 MSM                   winSize & WinRatio & cost
// 					  method == 5  		 TWED                  winSize & WinRatio & nu & lambda
// 					  method == 6  		 SWALE                 winSize & WinRatio & eps & gapC & reward
// 					  method == 7  		 LCSS                  winSize & WinRatio & eps
// 					  method == 8  		 ERP                   winSize & winRatio & gap
// 					  method == 9  		 SSPD                  -------
// 					  method == 10 		 HAUSDORFF             -------
// 					  method == 11 		 FRECHET               -------									<<
// 					  method == 12 		 WDTW                  g & weightMax & winSize & winRatio
//
//		input[1]  ==> winsize
//		input[2]  ==> winRatio
//		input[3]  ==> epsilon
//		input[4]  ==> cost
//		input[5]  ==> lambda
//		input[6]  ==> nu
//		input[7]  ==> Number of DataSet
//		input[8]  ==> Dataset Path
//		input[9]  ==> log File Path
//		input[10] ==> eps
//		input[11] ==> gapC
//		input[12] ==> reward
//		input[13] ==> gap
//		input[14] ==> weightMax
//		input[15] ==> g
//		input[16] ==> output;
//		input[17] ==> folds Numbers In Classifier
//		input[18] ==> iteration Numbers In Classifier
//		input[19] ==> labels path
//		input[20] ==> Classifier
//									METHOD NAME					Attributes
//								 ----------------		   -----------------------------------
// 				Classifier == 0   		 1NN                   fold & iteration number
//
//		input[21]  ==> Time Series Dimension


// ----------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
void Input:: preProcessing(int argc, const char * argv[])
{
    setInputs(argc,argv);
}

//------------------------------------------------------------------------------------------------------

void Input::setInputs(int argc, const char * argv[])
{

    writeInstruction();


    if(argc==1)
    {
		    cout << "Select Measuring Method        : "; cin  >> inputs[0];

		if(!inputs[0].compare("0") || !inputs[0].compare("1"))
		{
			cout << "Enter WinSize  	     : "; cin >> inputs[1];
			cout << "Enter WinRatio 	     : "; cin >> inputs[2];
		}

	 	else if( !inputs[0].compare("3") )
	    {
		    cout << "Enter WinSize     	   	 : "; cin >> inputs[1];
		    cout << "Enter WinRatio    	   	 : "; cin >> inputs[2];
		    cout << "Enter Epsilon    	   	 : "; cin >> inputs[3];
	    }

		else if( !inputs[0].compare("4") )
		{
			cout << "Enter WinSize   	     : "; cin >> inputs[1];
			cout << "Enter WinRatio  	     : "; cin >> inputs[2];
			cout << "Enter Cost     	     : "; cin >> inputs[4];
		}
		else if( !inputs[0].compare("5") )
		{
			cout << "Enter WinSize   	     : "; cin >> inputs[1];
			cout << "Enter WinRatio  	     : "; cin >> inputs[2];
			cout << "Enter lambda    	     : "; cin >> inputs[5];
			cout << "Enter nu        	     : "; cin >> inputs[6];
		}

		else if( !inputs[0].compare("6") )
		{
			cout << "Enter WinSize   	     : "; cin >> inputs[1];
			cout << "Enter WinRatio  	     : "; cin >> inputs[2];
			cout << "Enter eps       	     : "; cin >> inputs[10];
			cout << "Enter gapC      	     : "; cin >> inputs[11];
			cout << "Enter reward    	     : "; cin >> inputs[12];
		}
		else if( !inputs[0].compare("7") )
		{
			cout << "Enter WinSize 	         : "; cin >> inputs[1];
			cout << "Enter WinRatio  	     : "; cin >> inputs[2];
			cout << "Enter epc       	     : "; cin >> inputs[10];

		}

		else if( !inputs[0].compare("8") )
		{
			cout << "Enter WinSize    	     : "; cin >> inputs[1];
			cout << "Enter WinRatio   	     : "; cin >> inputs[2];
			cout << "Enter gap     	         : "; cin >> inputs[13];
		}

		else if( !inputs[0].compare("12") )
		{
			cout << "Enter WinSize  	     : ";  cin >> inputs[1];
			cout << "Enter WinRatio  	     : ";  cin >> inputs[2];
			cout << "Enter weightMax 	     : ";  cin >> inputs[14];
			cout << "Enter weightMax	     : ";  cin >> inputs[15];
		}
			cout << "Number of Dateset 	     : ";  cin >> inputs[7];
			cout << "Time Series Dimension   : ";  cin >> inputs[21];
			cout << "Dataset Path 		     : ";  cin >> inputs[8];
			cout << "log File Path 		     : ";  cin >> inputs[9];
			cout << "outPut  Path   	     : ";  cin >> inputs[16];
			cout << "label path      	     : ";  cin >> inputs[19];
			cout << "Classifier Method	     : ";  cin >> inputs[20];
			cout << "Number 0f fold (Classifier)	  : ";  cin >> inputs[17];
			cout << "Number 0f iteration (Classifier) : ";  cin >> inputs[18];
    }
    else
    {
        if(argc!=23)
            throw wrongInputNumber("argc must be 23","Input.cpp",186);

        int j=0;
        cout << "Reading Inputs From Terminal...\n";
        for (int i = 1; i < argc; ++i )
        {
            if(i==1)
                cout << "method             " << argv[i] << endl;
            else if(i==2)
                cout << "winSize            " << argv[i] << endl;
            else if(i==3)
                cout << "winRatio           " << argv[i] << endl;
            else if(i==4)
                cout << "epsilon            " << argv[i] << endl;
            else if(i==5)
                cout << "cost               " << argv[i] << endl;
            else if(i==6)
                cout << "lambda             " << argv[i] << endl;
            else if(i==7)
                cout << "nu                 " << argv[i] << endl;
            else if(i==8)
                cout << "Number of Dimension  " << argv[i] << endl;
            else if(i==9)
                cout << "Dataset Path        " << argv[i] << endl;
            else if(i==10)
                cout << "log File Path        " << argv[i] << endl;
            else if(i==11)
                cout << "eps                " << argv[i] << endl;
            else if(i==12)
                cout << "gapC               " << argv[i] << endl;
            else if(i==13)
                cout << "reward             " << argv[i] << endl;
            else if(i==14)
                cout << "gap                " << argv[i] << endl;
            else if(i==15)
                cout << "weightMax          " << argv[i] << endl;
            else if(i==16)
                cout << "g                  " << argv[i] << endl;
            else if(i==17)
                cout << "output             " << argv[i] << endl;
            else if(i==18)
            	cout << "folds Numbers      " << argv[i] << endl;
            else if(i==19)
            	cout << "iteration Numbers  " << argv[i] << endl;
            else if(i==20)
            	cout << "labels path        " << argv[i] << endl;
            else if(i==21)
               cout << "Classifier Method  " << argv[i] << endl;
            else if(i==22)
                cout << "Time Series Dimension  " << argv[i] << endl;
            
            inputs[j] = argv[i];
            ++j;
        }

    }
}
//------------------------------------------------------------------------------------------------------
 Input::Input()
{
    for (int i=0; i<22 ; ++i)
        inputs.push_back("NULL");
}
//-----------------------------------------------------------------------------------------------------
vector <string> Input::getInputs()
{
    return  inputs;
}
//-----------------------------------------------------------------------------------------------------

string Input::getLogFilePath()
{
    return inputs[9];
}
//-----------------------------------------------------------------------------------------------------

string Input::getOutputFilePath()
{
    return inputs[16];
}
//-----------------------------------------------------------------------------------------------------

void Input::writeInstruction()
{
	cout <<"----------------------------------------------------------------------------------------------------\n";
	cout <<"Instruction : \n";
	cout <<"----------------------------------------------------------------------------------------------------\n";
	cout <<"// 	The methods in this source code indicated with numbers.\n"; 
	cout<< "//	As an example, \"0\" indicate the \"DTW\" method, or \"7\" showing the \"LCSS\" method.\n";
	cout <<"----------------------------------------------------------------------------------------------------\n";
	cout <<"			 METHOD NAME			  Attributes			\n";
	cout <<"	           -----------------	 -----------------------------------\n";
	cout <<" method == 0   		 DTW                   winSize & WinRatio\n";
	cout <<" method == 1    	 CIDTW                 winSize & WinRatio\n";
	cout <<" method == 2    	 DISCRETEFRECHET            ------\n";
	cout <<" method == 3  		 EDR                   winSize & WinRatio & epsilon\n";
	cout <<" method == 4  		 MSM                   winSize & WinRatio & cost\n";
	cout <<" method == 5  		 TWED                  winSize & WinRatio & nu & lambda\n";
	cout <<" method == 6  		 SWALE                 winSize & WinRatio & eps & gapC & reward\n";
	cout <<" method == 7  		 LCSS                  winSize & WinRatio & eps\n";
	cout <<" method == 8  		 ERP                   winSize & winRatio & gap\n";
	cout <<" method == 9  		 SSPD                      -------\n";
	cout <<" method == 10 		 HAUSDORFF                 -------\n";
	cout <<" method == 11 		 FRECHET                   -------\n";
	cout <<" method == 12 		 WDTW                  g & weightMax & winSize & winRatio\n";
	cout <<"----------------------------------------------------------------------------------------------------\n";

	cout <<"// 	Classifiers in this source code indicated with numbers.\n";
	cout<< "//	As an example, \"0\" indicate the \"1nn\" classifier";
	cout <<"\n----------------------------------------------------------------------------------------------------\n";
	cout <<"			    METHOD NAME			  Attributes						\n";
	cout <<"	                -----------------	  -----------------------------------\n";
	cout <<" Classifier == 0    		1NN                   fold & iteration number			 \n";
	cout <<"----------------------------------------------------------------------------------------------------\n\n\n";



}





// ----------------------------------------------------------------------------------------------
/******************
// -----------------
    For debugging
// -----------------

	inputs[0]  = "0";
	inputs[1]  = "1";
	inputs[2]  = "1";

	inputs[3]  = "1";
	inputs[4]  = "1";
	inputs[5]  = "1";
	inputs[6]  = "1";

    inputs[7]  = "1";
    inputs[8]  = "/home/node1/Desktop/project/TimeSeries/data/";
    inputs[9]  = "/home/node1/Desktop/project/log.txt";

    inputs[10]  = "1";
    inputs[11]  = "1";
    inputs[12]  = "1";
    inputs[13]  = "1";
    inputs[14]  = "1";
    inputs[15]  = "1";

    inputs[16] = "/home/node1/Desktop/project/out.txt";
    inputs[17] = "10";
    inputs[18] = "1";
    inputs[19] = "NULL";
    inputs[20] = "0";
    inputs[21] = "2";

******************/
// ----------------------------------------------------------------------------------------------

