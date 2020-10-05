// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "Twed.hpp"
#include "limits"
#include <iostream>
#include <cmath>
#include "Functions.hpp"

class TimeSeries;
using namespace std;

//-------------------------------------------------------------------------------------------------


void Twed::computeAll(vector < unique_ptr <TimeSeries> > & path)
{
    double  _twedDist;
    int     _twedLen;
    
    unique_ptr <TimeSeries> timeseries ( path.back().get() );
    
    int size =  (int)path.size();

    int i,j=0;
    
    
    double tmp;
    
    for( i=0 ; i< size ; i++)
    {
        double percent;
        percent = (double) 100 * (i + 1) / size;
        cout << "Percent Done : %3.1f " <<  percent << endl;
        
        
        int n1 = (int)path[i].get()->getSize();
        
        for( j=i+1 ; j< size ;j++)
        {
            
            
            int n2 = (int)path[j].get()->getSize();
            
            tmp = fabs(n2 - n1);
            
            if (n1 > n2)
            {
                if (winSize != -1)
                    winSize = (int) tmp + n2 * winRatio;
            }
            else
            {
                if (winSize != -1)
                    winSize = (int) tmp + n1 * winRatio;
            }
            
            compute( path[i].get(), path[j].get() ,  _twedDist, _twedLen);
            twedDist[i][j] = _twedDist;
            twedLen[i][j]  = _twedLen;
            
        }
        
    }
}
//-------------------------------------------------------------------------------------------------

void Twed::compute(TimeSeries *Ts1, TimeSeries *Ts2 ,double & _twedDist,int &_twedLen )
{
    
    
    int n1 =   (int)Ts1->getSize();
    int n2 =   (int)Ts2->getSize();
    int dim1 = (int)Ts1->getDimensional();
    int dim2 = (int)Ts2->getDimensional();
    
    if (dim1 != dim2)
        throw("Two time series dimension must be the same in Twed \n");
    vector <string> timeSerieDataFirst   = Ts1->getTimeSerieData();
    vector <string>  timeSerieDataSecond = Ts2->getTimeSerieData();
    
    double *timeSerieDataFirstDouble  =  VectorToDouble(timeSerieDataFirst);
    double *timeSerieDataSecondDouble =  VectorToDouble(timeSerieDataSecond);
    
    
    
    double D[n1 + 1][n2 + 1];
    double Z[dim1];
    int i, j;
    int jS, jF;
    int lenDiff;
    double tmp, tmp1, tmpMin;
    double iNFINITY= numeric_limits <double> ::infinity();
    
    
    if (n1 - n2 > 0)
    {
         lenDiff = n1 - n2;
    }
    else
    {
         lenDiff = n2 - n1;
    }
    
    if (winSize != -1 && winSize < lenDiff)
    {
        winSize = lenDiff;
    }
    
    for ( i = 0; i < dim1; i++)
    {
        Z[i] = 0;
    }
    
    for ( i = 0; i <= n1; i++)
    {
        for ( j = 0; j <= n2; j++)
        {
            D[i][j] = 0;
            
            if (i == 0)
            {
                D[i][j] = iNFINITY;
            }
            if (j == 0)
            {
                D[i][j] = iNFINITY;
            }
        }
    }
    D[0][0] = 0;
    
    
    for (i = 1; i <= n1; i++)
    {
        if (winSize == -1)
        {
            jS = 1;
            jF = n2;
        }
        else
        {
            jS = i - winSize > 1 ? i - winSize : 1;
            jF = i + winSize < n2 ? i + winSize : n2;
        }
        for (j = jS; j <= jF; j++)
        {
            if (i > 0 && j > 0)
            {
                tmp = euclideanCalculate(timeSerieDataFirstDouble, n1, timeSerieDataSecondDouble, n2, dim1, i-1, j-1);
                tmp1 = euclideanCalculate(timeSerieDataFirstDouble, n1, timeSerieDataSecondDouble, n2, dim1, i - 2, j - 2);
                D[i][j] = D[i-1][j-1] + tmp + tmp1 + (nu * 2 * fabs(i-j));
            }
            else
            {
                tmp = euclideanCalculate(timeSerieDataFirstDouble, n1, timeSerieDataSecondDouble, n2, dim1, i-1, j-1);
                D[i][j] = D[i-1][j-1] +  tmp + (nu * fabs(i-j));
            }
            
            if (i > 0)
            {
                tmp = euclideanCalculate(timeSerieDataFirstDouble, n1, timeSerieDataFirstDouble, n1, dim1, i-1, i-2);
                tmpMin = D[i-1][j] + nu + lambda + tmp;
            }
            else
            {
                tmp = euclideanCalculate(timeSerieDataFirstDouble, n1, Z, 1, dim1, i-1, 0);
                tmpMin = D[i-1][j] + nu + lambda + tmp;
            }
            if ( tmpMin < D[i][j] )
            {
                D[i][j] = tmpMin;
            }
            
            if (j > 0)
            {
                tmp = euclideanCalculate(timeSerieDataSecondDouble, n2, timeSerieDataSecondDouble, n2, dim1, j-1, j-2);
                tmpMin = D[i][j-1] + nu + lambda + tmp;
            }
            else
            {
                tmp = euclideanCalculate(timeSerieDataSecondDouble, n2, Z, 1, dim1, j-1, 0);
                tmpMin = D[i][j-1] + nu + lambda + tmp;
            }
            if ( tmpMin < D[i][j] )
            {
                D[i][j] = tmpMin;
            }
            
        }
    }
    
    
    _twedDist = D[n1][n2];
    
    
}


//-------------------------------------------------------------------------------------------------

double Twed::getParam()
{
    return winSize;
}

//-------------------------------------------------------------------------------------------------

vector< vector<int> > * Twed::addressRepoLen()
{
    return &twedLen;
}

//-------------------------------------------------------------------------------------------------

vector< vector<double> > *  Twed::addressRepoDist()
{
    return &twedDist;
}

//-------------------------------------------------------------------------------------------------
Twed::~Twed()
{
    
}
//-------------------------------------------------------------------------------------------------

Twed::Twed(int size,double  * _winSize ,double * _winRatio ,double * _lambda,double * _nu)
{
    
    winSize  = _winSize[0];
    winRatio = _winRatio[0];
    lambda  = _lambda[0];
    nu = _nu[0];
    
    twedLen.resize(size);
    twedDist.resize(size);
    for(int i=0;i<size;i++)
    {
        twedLen[i].resize(size);
        twedDist[i].resize(size);
    }
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            twedLen[i][j] = -1;
            twedDist[i][j] = -1;
        }
    
}
//-------------------------------------------------------------------------------------------------

double Twed::euclideanCalculate(double *ts1,int n1,double *ts2,int n2,int dim, int idx1,int idx2)
{
    double euclDist = 0;
    int i;
    double tmp;
    
    
    for (i = 0; i < dim; i++)
    {
        tmp = ts1[idx1 + n1 * i] - ts2[idx2 + n2 * i];
        euclDist += tmp * tmp;
    }
    euclDist = sqrt(euclDist);
    return euclDist;
}
//-------------------------------------------------------------------------------------------------

