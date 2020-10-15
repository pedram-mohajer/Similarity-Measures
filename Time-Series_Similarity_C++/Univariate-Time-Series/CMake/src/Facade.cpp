// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------



#include <iostream>
#include "Facade.hpp"
#include "Exception.h"
#include "Functions.hpp"
#include "Facade.hpp"
#include "Interface.hpp"
#include "Log.hpp"



using namespace std;


// ----------------------------------------------------------------------------------------------
//     Description
// --------------
//		param[0]  ==> winsize
//		param[1]  ==> winRatio;
//		param[2]  ==> epsilon;
//		param[3]  ==> cost;
//		param[4]  ==> lambda;
//		param[5]  ==> nu;
//		param[6]  ==> eps;
//		param[7]  ==> gapC;
//		param[8]  ==> reward;
//		param[9]  ==> gap
//		param[10] ==> WeightMax
//		param[11] ==> G
//		param[12] ==> flod;
//		param[13] ==> iter;
//		param[14] ==> numberOfTsd
//		param[15] ==> Classifier
//
// ----------------------------------------------------------------------------------------------

Facade::Facade()
{


}
//----------------------------------------------------------------------------------------------------

void Facade::preProcessing(vector<string> input)
{
    setParam(input);
    createInterface();
    chooseFunction();
    doInterfaceFunction();

    freeInterface();
}
//----------------------------------------------------------------------------------------------------
void Facade::setParam(vector <string> input)
{
    
    setMethodNumber(input[0]);

    setInputPath(input[8]);
    setLablesPath(input[19]);

    setWinSize(input[1]);
    setWinRatio(input[2]);
    setEpsilon(input[3]);
    setCost(input[3]);
    setLambda( input[4]);
    setNu(input[6]);
    setEpc(input[10]);
    setGapc(input[11]);
    setReward(input[12]);
    setGap(input[13]);
    setWeightMax(input[14]);
    setG(input[15]);
    setFoldNumber(input[17]);
    setIterNumber(input[18]);
    setNumberOfTimeseries(input[7]);
    setClassiferNumber(input[20]);
}
//----------------------------------------------------------------------------------------------------
void Facade::createInterface()
{
    unique_ptr <Interface> interface(Interface::makeInterfaceInstance(param[14]) );
    this->interface = move(interface);
}
//----------------------------------------------------------------------------------------------------

void Facade::chooseFunction()
{
        if(methodNumber==0)
            {userChoiceInt=0; userChoiceStr="DTW";}
        else
        if(methodNumber==1)
            {userChoiceInt=1; userChoiceStr="CIDTW";}
        else
        if(methodNumber==2)
            {userChoiceInt=2; userChoiceStr="DiscreteFrechet";}
        else
        if(methodNumber==3)
            {userChoiceInt=3; userChoiceStr="Edr";}
        else
        if(methodNumber==4)
            {userChoiceInt=4; userChoiceStr="Msm";}
        else
        if (methodNumber==5)
            {userChoiceInt=5; userChoiceStr="Twed";}
        else
        if (methodNumber==6)
            {userChoiceInt=6; userChoiceStr="Swale";}
        else
        if (methodNumber==7)
            {userChoiceInt=7; userChoiceStr="Lcss";}
        else
        if (methodNumber==8)
            {userChoiceInt=8; userChoiceStr="Erp";}
	    else 
	    if (methodNumber==9)
	        {userChoiceInt=9; userChoiceStr="Sspd";}
	    else 
	    if (methodNumber==10)
	        {userChoiceInt=10; userChoiceStr="Hausdorff";}
	    else 
	    if (methodNumber==11)
	        {userChoiceInt=11; userChoiceStr="Frechet";}
	    else 
	    if (methodNumber==12)
	        {userChoiceInt=12; userChoiceStr="Wdtw";}
        else
            throw WrongInput("Your Chosen Method Is Not Existed");
}
//----------------------------------------------------------------------------------------------------
void Facade::doInterfaceFunction()
{
    interface->chooseMethod(path,param,userChoiceInt,userChoiceStr);
}
//----------------------------------------------------------------------------------------------------
void Facade::freeInterface()
{
    this->interface.release();
}
//----------------------------------------------------------------------------------------------------
void Facade::setMethodNumber(string _methodNumber)
{
    if( !isInteger(_methodNumber) )
        throw WrongInput("Method Number is not valid");
    methodNumber = stoi(_methodNumber);
}
//----------------------------------------------------------------------------------------------------
void Facade::setWinSize(string _winsize)
{
    if( !isNumber(_winsize) && _winsize.compare("NULL") )
        throw WrongInput("winSize is not Number");
    if( isNumber(_winsize) )
    {
        double *tmp = new double [1];
        tmp[0] = stod(_winsize) ;
        param.push_back(tmp);
    }
    else
       param.push_back(NULL);
}
//----------------------------------------------------------------------------------------------------
void Facade::setWinRatio(string _winRatio)
{
    if( !isNumber(_winRatio) && _winRatio.compare("NULL") )
        throw WrongInput("winRatio Number is not Vaild");
    if( isNumber(_winRatio) )
    {
        double *tmp = new double [1];
        tmp[0] = stod(_winRatio) ;
        param.push_back(tmp);
    }
    else
        param.push_back(NULL);
}
//----------------------------------------------------------------------------------------------------
void Facade::setEpsilon(string _epsilon)
{
  if( !isNumber(_epsilon)  && _epsilon.compare("NULL") )
        throw WrongInput("epsilon is not Number");
  if( isNumber(_epsilon) )
  {
      double *tmp = new double [1];
      tmp[0] = stod(_epsilon) ;
      param.push_back(tmp);
  }
  else
     param.push_back(NULL);
}
//----------------------------------------------------------------------------------------------------
void Facade::setCost(string _cost)
{
    if( !isNumber(_cost)  && _cost.compare("NULL") )
        throw WrongInput("cost is not Number");
    if( isNumber(_cost) )
    {
        double *tmp = new double [1];
        tmp[0] = stod(_cost) ;
        param.push_back(tmp);
    }
    else
        param.push_back(NULL);
}
//----------------------------------------------------------------------------------------------------
void Facade::setLambda(string _lambda)
{
    if( !isNumber(_lambda)  && _lambda.compare("NULL") )
        throw WrongInput("_lambda is not Number");
    if( isNumber(_lambda) )
    {
        double *tmp = new double [1];
        tmp[0] = stod(_lambda) ;
        param.push_back(tmp);
    }
    else
        param.push_back(NULL);
}
//----------------------------------------------------------------------------------------------------
void Facade::setNu(string _nu)
{
    if( !isNumber(_nu)  && _nu.compare("NULL") )
        throw WrongInput("_nu is not Number");
    if( isNumber(_nu) )
    {
        double *tmp = new double [1];
        tmp[0] = stod(_nu) ;
        param.push_back(tmp);
    }
    else
        param.push_back(NULL);
}
//----------------------------------------------------------------------------------------------------
void Facade::setGapc(string _gapc)
{
    if( !isNumber(_gapc)  && _gapc.compare("NULL") )
        throw WrongInput("_gapc is not Number");
    if( isNumber(_gapc) )
    {
        double *tmp = new double [1];
        tmp[0] = stod(_gapc) ;
        param.push_back(tmp);
    }
    else
        param.push_back(NULL);
}
//----------------------------------------------------------------------------------------------------
void Facade::setEpc(string _epc)
{
    if( !isNumber(_epc)  && _epc.compare("NULL") )
        throw WrongInput("_epc is not Number");
    if( isNumber(_epc) )
    {
        double *tmp = new double [1];
        tmp[0] = stod(_epc) ;
        param.push_back(tmp);
    }
    else
        param.push_back(NULL);
}
//----------------------------------------------------------------------------------------------------
void Facade::setReward(string _reward)
{
    if( !isNumber(_reward)  && _reward.compare("NULL") )
        throw WrongInput("_reward is not Number");
    if( isNumber(_reward) )
    {
        double *tmp = new double [1];
        tmp[0] = stod(_reward) ;
        param.push_back(tmp);
    }
    else
        param.push_back(NULL);
}
//----------------------------------------------------------------------------------------------------
void Facade::setGap(string _gap)
{
    if( _gap.compare("NULL")  )
    {
       int i=0,index,count=1,j=0;
       string tmp;
        while (_gap[i])
        {
            if( _gap[i] == '-' )
                ++count;
            ++i;
        }
       double *temp = new double [count];
        i=0;
       while(_gap[i])
       {
          index  = _gap.find('-');
          tmp    = _gap.substr(0,index);
           if( !isNumber(tmp) )
               throw WrongInput("gap member is not Number");
          _gap   = _gap.substr(index+1);
           temp[j] = stod(tmp);
           i++; j++;
       }
        param.push_back(temp);
    }
    else
        param.push_back(NULL);
}
//----------------------------------------------------------------------------------------------------
void Facade::setWeightMax(string _weightMax)
{
    if( !isNumber(_weightMax)  && _weightMax.compare("NULL") )
        throw WrongInput("_weightMax is not Number");
    if( isNumber(_weightMax) )
    {
        double *tmp = new double [1];
        tmp[0] = stod(_weightMax) ;
        param.push_back(tmp);
    }
    else
        param.push_back(NULL);
}
//----------------------------------------------------------------------------------------------------
void Facade::setG(string _g)
{
    if( !isNumber(_g)  && _g.compare("NULL") )
        throw WrongInput("_reward is not Number");
    if( isNumber(_g) )
    {
        double *tmp = new double [1];
        tmp[0] = stod(_g) ;
        param.push_back(tmp);
    }
    else
        param.push_back(NULL);
    
}
//----------------------------------------------------------------------------------------------------
void Facade::setFoldNumber(string _foldNumber)
{
	   if( !isNumber(_foldNumber)  && _foldNumber.compare("NULL") )
	        throw WrongInput("folds number is not Number");

	   if( isNumber(_foldNumber) )
	    {
	        double *tmp = new double [1];
	        tmp[0] = stod(_foldNumber) ;
	        param.push_back(tmp);
	    }
	    else
	        param.push_back(NULL);


}
//----------------------------------------------------------------------------------------------------
void Facade::setIterNumber(string _setIterNumber)
{
	   if( !isNumber(_setIterNumber)  && _setIterNumber.compare("NULL") )
	        throw WrongInput("iteration number is not Number");

	   if( isNumber(_setIterNumber) )
	    {
	        double *tmp = new double [1];
	        tmp[0] = stod(_setIterNumber) ;
	        param.push_back(tmp);
	    }
	    else
	        param.push_back(NULL);

}
//----------------------------------------------------------------------------------------------------
void Facade::setInputPath(string tsdFilePath)
{

    path.push_back(tsdFilePath);
}
//---------------------------------------------------------------------------------------------------
void Facade::setLablesPath(string labelFilePath)
{
    path.push_back(labelFilePath);
}
//---------------------------------------------------------------------------------------------------
void Facade::setNumberOfTimeseries(string _numberOfTimeseriesInt)
{

    if( !isInteger(_numberOfTimeseriesInt) )
        throw WrongInput("Number Of Time Series is not valid");
    if( isNumber(_numberOfTimeseriesInt) )
    {
        double *tmp = new double [1];
        tmp[0] = stod(_numberOfTimeseriesInt) ;
        param.push_back(tmp);
    }
    else
       param.push_back(NULL);
}
//----------------------------------------------------------------------------------------------------
void Facade::setClassiferNumber(string _classifierNumber)
{
    if( !isNumber(_classifierNumber) && _classifierNumber.compare("NULL") )
        throw WrongInput("classifierNumber is not Number");
    if( isNumber(_classifierNumber) )
    {
        double *tmp = new double [1];
        tmp[0] = stod(_classifierNumber) ;
        param.push_back(tmp);
    }
    else
       param.push_back(NULL);


}
//----------------------------------------------------------------------------------------------------



