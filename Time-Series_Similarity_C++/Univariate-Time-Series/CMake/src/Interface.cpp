// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "Wdtw.hpp"
#include "Frechet.hpp"
#include "Hausdorff.hpp"
#include "Sspd.hpp"
#include "Erp.hpp"
#include "Lcss.hpp"
#include "Swale.hpp"
#include "Twed.hpp"
#include "Msm.hpp"
#include "DiscreteFrechet.hpp"
#include "Edr.hpp"
#include "Dtw.hpp"
#include "Cidtw.hpp"
#include "Interface.hpp"
#include "TimeSeries.hpp"
#include "Functions.hpp"
#include "MeasureSimilarity.hpp"
#include "OneNearestNeighbour.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Functions.hpp"
#include "Exception.h"

using namespace std;
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

// ----------------------------------------------------------------------------------------------
//     Description
// --------------
//
//
//
//		param[0]  ==> winsize
//		param[1]  ==> winRatio;
//		param[2]  ==> epsilon;
//		param[3]  ==> cost;
//		param[4]  ==> lambda;
//		param[5]  ==> nu;
//		param[6]  ==> eps;
//		param[7]  ==> gapC;
//		param[8]  ==> reward;
//		param[9]  ==> gap;
//		param[10] ==> weightMax;
//		param[11] ==> g;
//		param[12] ==> foldNumber;
//		param[13] ==> iterationNumber;
//		param[14] ==> numberOf

//------------------------------------------------------------------------------------------------

 void  Interface::chooseMethod(vector <string>  path,vector <double * > param,int userChoiceNumber,string userChoiceStr)
{
   
	size_t numberOfDataset =  (size_t)*param[14];

    readDataset(path[0],numberOfDataset);
    checkTimeSeriesData();
    createTimeSeriesInstances();

    for(size_t i=0; i<dataPathRepository.size(); i++)
    {
        unique_ptr <MeasureSimilarity> measureSimilarity ( buildMeasureSimilarity( dataPathRepository[i].size() ,userChoiceNumber,param) );
        this->measureSimilarity = move(measureSimilarity);

    	cout << "\n" << userChoiceStr <<" Processing Is Starting... \n";
    	this->measureSimilarity.get()->computeAll( timeSeries[i] );

        sendRepoToCompareClass(this->measureSimilarity.get()->addressRepoLen(), this->measureSimilarity.get()->addressRepoDist(),userChoiceStr);

        freeMeasureSimilarityInstance();
    }

    writeInOutput();

    if(path[1].compare("NULL") != 0)
    {
    	readLablesPath(path[1], numberOfDataset);
    	setTimeSeriesLabels(numberOfDataset);
    	unique_ptr <Classifier> classifier ( buildClassifier( (size_t)*param[15] , param , dataPathRepository.size() ) );
    	this->classifier = move(classifier);
    	doClassifier(  this->resultRepository->uniquePtrOfDistRepo().get() , userChoiceStr);
    }

}
 //------------------------------------------------------------------------------------------------

 void Interface::doClassifier(vector <  vector< vector<double> > > * DistRepo,string _methodName )
 {

 	classifier->classifying( DistRepo, _methodName, labelRespository);

 }
 //------------------------------------------------------------------------------------------------
Classifier* Interface::buildClassifier(size_t classifierNumber, vector<double *> param, size_t size)
{
	if(classifierNumber == 0)
		return new OneNearestNeighbour(param[12], param[13], size );
	else
		throw WrongClassifier("Please Correct Classifier " , "Interface.cpp");
}

//------------------------------------------------------------------------------------------------
MeasureSimilarity* Interface::buildMeasureSimilarity(int size ,int userChoiceNumber,vector<double *> param)
{

    if(userChoiceNumber==0)
         return new Dtw(size,param[0],param[1]);
    else if (userChoiceNumber==1)
         return new Cidtw(size,param[0],param[1]);
    else if (userChoiceNumber==2)
        return  new DiscreteFrechet(size);
    else if (userChoiceNumber==3)
        return  new Edr(size,param[0],param[1],param[2]);
    else if (userChoiceNumber==4)
        return  new Msm(size,param[0],param[1],param[3]);
    else if (userChoiceNumber==5)
        return  new Twed(size,param[0],param[1],param[5],param[6]);
    else if (userChoiceNumber==6)
        return  new Swale(size,param[0],param[1],param[6],param[7],param[8]);
    else if (userChoiceNumber==7)
        return  new Lcss(size,param[0],param[1],param[2]);
    else if (userChoiceNumber==8)
        return  new Erp(size,param[0],param[1],param[9]);
    else if (userChoiceNumber==9)
        return  new Sspd(size);
    else if (userChoiceNumber==10)
        return  new Hausdorff(size);
    else if (userChoiceNumber==11)
        return  new Frechet(size);
    else if (userChoiceNumber==12)
       return  new Wdtw(size,param[0],param[1],param[10],param[11]);

    else
    	throw WrongMeasureSimilarity("Please Correct Classifier " , "Interface.cpp");


}


//------------------------------------------------------------------------------------------------
unique_ptr <TimeSeries> Interface::buildTimeSeries( string  path)
{
    unique_ptr <TimeSeries> time(new TimeSeries(path));
    return time;
}

//------------------------------------------------------------------------------------------------
Interface::Interface(double *datasetSize)
{
	dataPathRepository.resize(datasetSize[0]);
	timeSeries.resize(datasetSize[0]);
	resultRepository = new ResultRepository(datasetSize[0]);
	labelRespository.resize(datasetSize[0]);

}

//------------------------------------------------------------------------------------------------

 Interface * Interface::interfaceInstance=0;

//------------------------------------------------------------------------------------------------


 Interface * Interface::makeInterfaceInstance(double *datasetSize)
{
    if( interfaceInstance == 0 )
        interfaceInstance = new Interface(datasetSize);
    return interfaceInstance;
}


//------------------------------------------------------------------------------------------------

void Interface::freeMeasureSimilarityInstance()
{
      measureSimilarity.release();
}
//------------------------------------------------------------------------------------------------

void Interface::sendRepoToCompareClass( vector< vector<int> > * dtwLenRepo  , vector< vector<double> > * dtwDistRepo,string _methodName)
{
    resultRepository->addToDiagramDist(*dtwDistRepo);
    resultRepository->addToDiagramLen(*dtwLenRepo);
    resultRepository->increaseNumberOfMethod();

}



//---------------------------------------------------------------------------------------------------

void Interface::readLablesPath(string lablesFilePath, size_t numberOfDataset)
{
    string temp,extensionTsd, tmp;

    labelPathRepository.clear();

    boost::filesystem::path _path(lablesFilePath);

    size_t count=0;

    for (auto i = directory_iterator(_path); i != directory_iterator();i++ )
    {

        temp = i->path().filename().string();
        extensionTsd = temp.substr(temp.size()-3,temp.size()-1);
        if(extensionTsd.compare("tsd"))
            continue;
        cout << " Label Path [ " << temp << " ] : is Add \n";
        count++;
        tmp = lablesFilePath + temp ;
        labelPathRepository.push_back( tmp );


        if( count == numberOfDataset)
            break;
    }

    bubbleSort(labelPathRepository);

}
//---------------------------------------------------------------------------------------------------
void Interface::checkTimeSeriesData()
{
	size_t size = dataPathRepository.size();

	   for( size_t i=0 ; i<size ; i++)
	   {
			for(size_t j=0 ; j<dataPathRepository[i].size() ; j++)
			{
				validateTimeSeriesData(dataPathRepository[i][j]);
				cout << dataPathRepository[i][j] << " is Validated." << endl;
			}
			cout << "\n---------------------------------------------\n";
	   }

}
//---------------------------------------------------------------------------------------------------

void Interface::createTimeSeriesInstances()
{
	size_t size = dataPathRepository.size();

	for( size_t i=0 ; i<size ; i++)
		for( size_t j=0 ; j<dataPathRepository[i].size() ; j++)
			this->timeSeries[i].push_back( buildTimeSeries( dataPathRepository[i][j]) );

}

//---------------------------------------------------------------------------------------------------

void Interface::setTimeSeriesLabels(size_t numberOfDataset)
{
	vector <vector <string>> lables(labelPathRepository.size() );


	for( size_t i=0 ; i<labelPathRepository.size() ; i++)
	{
		validateLabelData(labelPathRepository[i] , lables[i]);
    	cout << labelPathRepository[i] << " is Validated." << endl;

	}

	if( dataPathRepository.size() !=lables.size()   )
		throw(InequalityInNumberOFLabelsAndData("Inequality In The Number Of Labels And Data" , "Interface.cpp"));


	for(size_t i=0 ; i<dataPathRepository.size() ; i++)
			if(dataPathRepository[i].size() != lables[i].size() )
				throw(InequalityInNumberOFLabelsAndData(string(string("Inequality In Number Ofs Labels And Data In ") + labelPathRepository[i]) , "Interface.cpp"));

	for(size_t j=0; j<dataPathRepository.size() ; j++)
		for(size_t i=0; i<dataPathRepository[j].size() ; i++)
		{
			timeSeries[j][i].get()->setLabel(lables[j][i]);

			labelRespository[j].push_back(  lables[j][i] )  ;
		}
}

//---------------------------------------------------------------------------------------------------
void Interface::readDataset(string DatasetPath, size_t numberOfDataset)
{
    string temp1, temp2, extensionTsd, tmp, tsdFolder, tsdPath;
    vector <string > datasetName, tsdName;

    boost::filesystem::path _path(DatasetPath);

    size_t count=0;

    for (auto j = directory_iterator(_path);  j != directory_iterator(); j++ )
    {

	temp1 = j->path().filename().string();
	tsdFolder = temp1.substr(0,3);
	if(tsdFolder.compare("TSD"))
		continue;
	count++;

	datasetName.push_back(temp1);

	if(count == numberOfDataset)
	 	break;

    }
    if(count < numberOfDataset)
		throw WrongNumberOfDataset("The number of dataset is not valid " , "Interface.cpp");

    bubbleSort(datasetName);


    for(size_t count=0; count<datasetName.size(); count++)
    {
		tsdPath = DatasetPath + datasetName[count] + "/";
		boost::filesystem::path *__path = new path(tsdPath);

		for (auto i = directory_iterator(*__path); i != directory_iterator(); i++ )
		{

			temp2 = i->path().filename().string();
			extensionTsd = temp2.substr(temp2.size()-4,temp2.size()-1);
			if(extensionTsd.compare(".tsd"))
				continue;
			tsdName.push_back(temp2);


		}

		bubbleSort(tsdName);

		cout << "\nData in " << datasetName[count] << " : \n";
	    for(size_t cnt=0; cnt<tsdName.size(); cnt++)
	    {

			cout << tsdPath+tsdName[cnt] << " is Added." << endl;
			tmp = tsdPath+tsdName[cnt];
			dataPathRepository[count].push_back(tmp) ;
	    }
	    tsdName.clear();
	    free(__path);
	    cout << "-------------------------------------\n";
   }


}
//---------------------------------------------------------------------------------------------------

void Interface::swap(string &xp, string &yp)
{
    string temp = xp;
    xp = yp;
    yp = temp;
}
//---------------------------------------------------------------------------------------------------


void Interface::bubbleSort(vector <string> &arr)
{
   size_t i, j;
   bool swapped;
   for (i = 0; i < arr.size() ; i++)
   {
     swapped = false;
     for (j = 0; j < arr.size()-i-1; j++)
     {
        if ( arr[j].compare(arr[j+1]) > 0 )
        {
           swap(arr[j], arr[j+1]);
           swapped = true;
        }
     }
     // IF no two elements were swapped by inner loop, then break
     if (swapped == false)
        break;
   }
}

//---------------------------------------------------------------------------------------------------

void Interface::writeInOutput()
{
    resultRepository->writeResultInOutput();
}
//---------------------------------------------------------------------------------------------------
Interface::~Interface()
{
	cout << "\n TimeSeries Processing Terminated \n";
}



