

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email : pedram.mohajer@outlook.com
//	       pmohaje@g.clemson.edu
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//  1. prerequisite
//  2. Description
//  3. Data rules 
//  4. Run by CMake 
//  5. Run in IDE

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 1.prerequisite
// -----------------

// 	As “boost library” is used in this source code and does not accompany with c++ packages, this library should be added manually.
//	Instruction for installing boost on Ubuntu :	
		1. Type this command “sudo apt-get install libboost-all-dev” at terminal.



// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  2.Description :
// -----------------
//		

//      When this program is executing, you will be asked to enter "Input Parameters" which are saved in "input" array in the source code respectively.
//      The first element is showing which method is going to be used, after choosing the method, you will be asked to enter its corresponding parameters.
// 	The methods in this source code indicated with numbers. As an example. "0" indicate the "DTW" method, or "7" showing the "LCSS" method.

//	To more clarifying, when you run this program, this sentence "Select The Measuring Method : " is appeared waiting for getting the method number. 
//	if "0" is entered, the selected method is "DTW", then you will be asked to enter its corresponding parameters which are winSize & WinRatio.

// 	The methods name and their corresponding parameters are listing below.

//	Label folder is used for classfying, so if there is no label folder and classification, please type "NULL" for "Classifier", "iteration number", 
//	"Fold number" and "Label path".

// 	"output path" indicates where the result will be saved. This file will be created by program. for example, "\home\user\Desktop\result.out. 
//	In the result file, two matrices will be written, named "Distance Matrix" and "Len Matrix".

// 	"log file path" indicates where the errors will be saved. This file will be created by program. for example, "\home\user\Desktop\log.out

//		------------------------------------------------------------------------------------------------------------------
//		input[0]  ==> method
//					 			METHOD NAME	        Attributes
//							       -------------	     -----------------------------------
// 		 			  method == 0   	 DTW                   winSize & WinRatio
// 					  method == 1            CIDTW                 winSize & WinRatio
// 					  method == 2     	 DISCRETE_FRECHET      ———
// 				  	  method == 3  		 EDR                   winSize & WinRatio & epsilon
// 					  method == 4  		 MSM                   winSize & WinRatio & cost
// 					  method == 5  		 TWED                  winSize & WinRatio & nu & lambda
// 					  method == 6  		 SWALE                 winSize & WinRatio & eps & gapC & reward
// 					  method == 7  		 LCSS                  winSize & WinRatio & eps
// 					  method == 8  		 ERP                   winSize & winRatio & gap
// 					  method == 9  		 SSPD                  -------
// 					  method == 10 		 HAUSDORFF             -------
// 					  method == 11 		 FRECHET               -------
// 					  method == 12 		 WDTW                  g & weightMax & winSize & winRatio
//		-------------------------------------------------------------------------------------------------------------------
//		input[1]  ==> winSize
//		-------------------------------------------------------------------------------------------------------------------
//		input[2]  ==> winRatio
//		-------------------------------------------------------------------------------------------------------------------
//		input[3]  ==> epsilon
//		-------------------------------------------------------------------------------------------------------------------
//		input[4]  ==> cost
//		-------------------------------------------------------------------------------------------------------------------
//		input[5]  ==> lambda
//		-------------------------------------------------------------------------------------------------------------------
//		input[6]  ==> nu
//		-------------------------------------------------------------------------------------------------------------------
//		input[7]  ==> Number of Dataset
//		-------------------------------------------------------------------------------------------------------------------
// 		input[8]  ==> The Path which in datasets are located
//		-------------------------------------------------------------------------------------------------------------------
//		input[9]  ==> The path which in the “log.txt” file will will be located, All different errors will be written in this file.
//		-------------------------------------------------------------------------------------------------------------------
//		input[10] ==> eps
//		-------------------------------------------------------------------------------------------------------------------
//		input[11] ==> gapC
//		-------------------------------------------------------------------------------------------------------------------
//		input[12] ==> reward
//		-------------------------------------------------------------------------------------------------------------------
//		input[13] ==> gap
//		-------------------------------------------------------------------------------------------------------------------
//		input[14] ==> weightMax
//		-------------------------------------------------------------------------------------------------------------------
//		input[15] ==> g
//		-------------------------------------------------------------------------------------------------------------------
// 		input[16] ==> The path which in the “out.txt” file will be located, the final results will be written.
//		-------------------------------------------------------------------------------------------------------------------
//		input[17] ==> folds Numbers, this parameter can be used in Classifier like 1NN. 
//		-------------------------------------------------------------------------------------------------------------------
//		input[18] ==> iteration Numbers	this parameter can be used in Classifier like 1NN. 
//		-------------------------------------------------------------------------------------------------------------------
//		input[19] ==> The path which in the labels are located, 
//		-------------------------------------------------------------------------------------------------------------------
//		input[20] ==> Classifier
//								METHOD NAME			Attributes
//								----------------		-----------------------------------
// 				Classifier == 0   		 1NN                   		fold & iteration number
// 		------------------------------------------------------------------------------------------------------------------
//		input[21] ==> Time Series Dimensions
//		------------------------------------------------------------------------------------------------------------------
//
	

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//   3.Data rules :
// -----------------

//	1. For this program, we introduce a new file extension, “tsd” extension(Time Series Data). Each “tsd” file show a Time Series.



// 	2. This program takes several datasets as input, and each dataset has several Time Series data(tsd) files.
//
//	   The variable “input[8]” holds dataset folder path, as an example “input[8] = /Users/userName/Desktop/Dataset/“.
//	   In this folder, Each dataset must have obey the naming convention, starting with “TSD” word, and ending in numbers like TSD01,TSD02, etc.
//
//	   Each dataset folder has several times series data(tsd)files. Each data file in this folder must have obey the naming convention, ending in “.tsd”.
//     	   To exemplify, the folder “/Users/userName/Desktop/Labels/TSD01/“ has tsdFile01.tsd, tsdFile02.tsd, tsdFile02.tsd, etc.
//
//	   The variable “input[19]” consist of label folder, as an example “input[19] = /Users/userName/Desktop/Labels/“. 
//         Each data file in this folder must have obey the naming convention, ending in “.tsd”.
//     	   To exemplify, the folder “/Users/userName/Desktop/Labels/“ has label01.tsd which is labels of the TSD01 dataset. 



//	3. There is a code snippet, named “CSV_to_TSD.cpp”, which converting each “CSV” dataset to separated corresponding “tsd” files. 
//	   Each “CSV” is equivalent to a “TSD” folder such as TSD01, TSD02, etc. And its data will be converted to different “tsd” files like 
//	   tsdFile01.tsd, tsdFile02.tsd, etc.
//	   This code snippet takes 3 arguments as input. The first one is “CSV dataset path”, the next one is “Enter Output Path”, and 
//	   the last one is “Separator” indicating with which character the data in CSV is separated, by default is ",".


	
	
//	4. An example of tsd files is like below showing a Multivariate Time Series which has three dimensions(a 3D TimeSeries).

//

		VERSION 0.01			// Version of tsd format
		FIELDS X Y X			// The feature of time series 
		SIZE 8 8 8			// Size
		COUNT 3				// The number of time series features
		TYPE 1 1 1			// INT = 0 , DOUBLE = 1,FLOAT = 2;
		SAMPLES 270			// The number of data in tsd 
		DATA ASCII			// Data Format

		Dim1
		-7.9042000e-01
		-7.651
		-7.3354000e-01
		-6.9963000e-01
		.
		.
		.
		.
		.
		0.324

		Dim2
		7.904
		-7.65
		7.33
		-3.9
		.
		.
		.
		.
		.
		3.6


		Dim3
		7.9042000e-01
		7.651
		7.3354000e-01
		6.9963000e-01
		.
		.
		.
		.
		.
		8.67


//	5. An example of “TSD folder” with their “tsd” files and “labels” is attached. 



// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//   4.Run by CMake :
// -----------------

//	In order to run this code you shoud write the below commands at terminal.

//	1. cd CMake	// "CMake" folder in this project
//	2. mkdir build
//	3. cmake ..
//	4. cmake --build .
//	5. ./SimilarityMeasure
//
//
// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//   5.Run in IDE :
// -----------------

//	Also, you can upload project place in "Workplace" directory to your IDE like Eclipse. Then run this program.
//	Be careful, boost header file should included manually.
//
//




